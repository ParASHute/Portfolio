// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameplayAbilitySpec.h"
#include "Weapon/MyAbilitySystemComponent.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APortfolioCharacter
APortfolioCharacter::APortfolioCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void APortfolioCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// 생성자 내부에서 어빌리티 컴포넌트가 제대로 할당이 됐다면
	if(AbilitySystemComponent != nullptr)
	{
		// 데이터 에셋 에디터에서 넣은 UMyAttributeSet타입 GetSet 
		AttributeSetVar = AbilitySystemComponent->GetSet<UMyAttributeSet>();
		if(AttributeSetVar != nullptr)	// 위에서 할당한 값이 제대로 할당 됐다면
		{
			

			InitializeAttribute();
			AddStartupEffects();
		}
	}
}

void APortfolioCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


//////////////////////////////////////////////////////////////////////////
// Input

void APortfolioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APortfolioCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APortfolioCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APortfolioCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APortfolioCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//////////////////////////////////////////////////////////////////////////
// Maked Function
void APortfolioCharacter::CameraLock(bool cameraHold)
{
	GetCharacterMovement()->bOrientRotationToMovement = cameraHold;
	//CameraBoom->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = cameraHold;
}

void APortfolioCharacter::CameraUnLock(bool cameraHold)
{
	GetCharacterMovement()->bOrientRotationToMovement = cameraHold;
	//CameraBoom->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = !cameraHold;
}

void APortfolioCharacter::SetCameraRelativePos(float Xpos, float Ypos, float Zpos)
{
	// CameraComponent의 컴포넌트를 가져와 유효한지 확인
	if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
	{
		// 현재 위치를 가져와서 Z축만 업데이트
		FVector NewLocation = CameraComponent->GetRelativeLocation();
		NewLocation.X = Xpos;
		NewLocation.Y = Ypos;
		NewLocation.Z = Zpos;

		// 상대 위치 업데이트
		CameraComponent->SetRelativeLocation(NewLocation);
	}
}


class UMyAbilitySystemComponent* APortfolioCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

class UWeaponComponent* APortfolioCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

void APortfolioCharacter::HoldCamera(bool CameraHold)
{
	GetCharacterMovement()->bOrientRotationToMovement =!CameraHold;
	bUseControllerRotationYaw = CameraHold;
}

FTransform APortfolioCharacter::GetBone(FName SocketName)
{
	FTransform RetuenVal = GetMesh()->GetSocketTransform(SocketName,RTS_World);
	return RetuenVal;
}

void APortfolioCharacter::InitializeAttribute()
{
	if(!IsValid(AbilitySystemComponent))
	{
		return;
	}
	/*
	// 빨간색 로그 출력부
	if(!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAbility."),*FString(__func__));
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle =
		AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);

	if(SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget
			(*SpecHandle.Data.Get(), AbilitySystemComponent);
	}
	*/
}

void APortfolioCharacter::AddStartupEffects()
{
	if(!IsValid(AbilitySystemComponent)
		|| GetLocalRole() != ROLE_Authority
		|| AbilitySystemComponent->StartUpEffectApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for(TSubclassOf<UGameplayEffect>GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec
		(GameplayEffect, 1, EffectContext);

		if(SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget
			(*SpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->StartUpEffectApplied = true;
}

void APortfolioCharacter::InitializedAbilityMulti
	(TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire,int32 AbilityLevel)
{
	if(HasAuthority())
	{
		for (TSubclassOf<UGameplayAbility> AbilityItem : AbilityToAcquire)
			InitializedAbility(AbilityItem,AbilityLevel);
	}
}

void APortfolioCharacter::InitializedAbility
	(TSubclassOf<UGameplayAbility> AbilityToGet,int32 AbilityLevel)
{
	if(HasAuthority()) // 온라인 상태에서 내가 조종하는 캐릭터를 확읺
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel));
	}
}

void APortfolioCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(AbilitySystemComponent != nullptr)
	{
		// 어빌리티 시스템에서 해당 시스템을 사용하는 엑터를 불러 오게 전달
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
		// 에디터에서 설정한 스킬(전부 : LEVEL == 1)
		InitializedAbilityMulti(InitAbilities,1);
	}
}

void APortfolioCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if(AbilitySystemComponent!=nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

void APortfolioCharacter::RemoveAbilityWithTags(FGameplayTagContainer TagContainer)
{
	TArray<FGameplayAbilitySpec*> MatchingAbilitySpecs;

	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		TagContainer, MatchingAbilitySpecs, true);

	for(FGameplayAbilitySpec* spec : MatchingAbilitySpecs)
		AbilitySystemComponent->ClearAbility(spec->Handle);
}

void APortfolioCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 Level)
{
	TArray<FGameplayAbilitySpec*> MatchingAbilitySpecs;

	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		TagContainer, MatchingAbilitySpecs, true);

	for(FGameplayAbilitySpec* spec : MatchingAbilitySpecs)
		spec->Level = Level;
}

void APortfolioCharacter::CancleAbilityWithTags(FGameplayTagContainer WithTag, FGameplayTagContainer WithoutTags)
{
	AbilitySystemComponent->CancelAbilities(&WithTag, &WithoutTags);
}

void APortfolioCharacter::AddLoosGamePlayTag(FGameplayTag TagToAdd)
{
	AbilitySystemComponent->AddLooseGameplayTag(TagToAdd);
	AbilitySystemComponent->SetTagMapCount(TagToAdd, 1);
}

void APortfolioCharacter::RemoveLoosGamePlayTag(FGameplayTag TagToRemove)
{
	AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
}