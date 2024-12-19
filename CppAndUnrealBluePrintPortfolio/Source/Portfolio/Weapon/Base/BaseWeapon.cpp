// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

// #include "AssetSelection.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Portfolio/PortfolioCharacter.h"	// Cpp 내 APortfolioCharacter의 불확실성 해결을 위한 헤더 선언

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Default Scene Root Component
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	// Set Skeletal Mesh Component
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(RootComponent); // Attach RootComponen
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// OwnerCharacter에 GetOwner를 넣고
	OwnerCharacter = Cast<APortfolioCharacter>(GetOwner());
	
	// OwnerCharacter
	if (!OwnerCharacter)	// Onwer에 GetOner설정이 안된다면
	{
		OwnerCharacter = Cast<APortfolioCharacter>(GetOwner());
    	
		if (!OwnerCharacter)	// 실패시 메시지
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner Not founded."));
		}
	}
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::EndAttack()
{
}

USkeletalMeshComponent* ABaseWeapon::GetMesh()
{
	return SkeletalMesh;
}

AActor* ABaseWeapon::Trace(/*FString TagName*/)
{
	const FVector StartLoc = SkeletalMesh->GetSocketLocation("StartSocket");
	const FVector EndLoc = SkeletalMesh->GetSocketLocation("EndSocket");
	const FVector BoxSize = {10, 10, 10};
	
	//충돌 검사할 오브젝트 타입
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = SetObjectTypes(ECollisionChannel::ECC_GameTraceChannel1);
	
	//충돌 결과
	FHitResult HitResults;
	
	// 무시할 객체
	TArray<AActor*> ActorsTolgnore;
	ActorsTolgnore.Add(Cast<AActor>(OwnerCharacter));
	
	bool Check = UKismetSystemLibrary::BoxTraceSingleForObjects
	(GetWorld(), StartLoc, EndLoc, BoxSize, GetActorRotation(), ObjectTypes,
	 false, ActorsTolgnore, EDrawDebugTrace::None, HitResults, true);
	//EDrawDebugTrace::ForDuration == 보여줌
	//EDrawDebugTrace::None == 안보여줌
	
	/*
	if (Check)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(TagName)));
		APortfolioCharacter* Temp = Cast<APortfolioCharacter>(HitResults.GetActor());
		Temp->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
	}
	*/
	return HitResults.GetActor();
}

TArray<TEnumAsByte<EObjectTypeQuery>> ABaseWeapon::SetObjectTypes(ECollisionChannel ChannelName)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add (UEngineTypes::ConvertToObjectType(ChannelName));
	return ObjectTypes;
}


