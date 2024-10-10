// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "PortfolioCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UMyAnimInstance::UMyAnimInstance()
{
	WeaponComponent = nullptr;
	OwnerCharacter = nullptr;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	OwnerCharacter = Cast<APortfolioCharacter>(TryGetPawnOwner());
	
	if(IsValid(OwnerCharacter))
	{
		WeaponComponent = OwnerCharacter->GetWeaponComponent();
		if(IsValid(WeaponComponent))
		{
			SetBlendSpace();
			SetDamageCauserDirection();
			SetAimRotation();

			//SetHandleLoation();
		}
		else
		{
			WeaponComponent = OwnerCharacter->GetWeaponComponent();
			if(IsValid(WeaponComponent))
				UE_LOG(LogTemp,Warning,TEXT("No WeaponComponent"));
		}
			
	}
	else
	{
		OwnerCharacter = Cast<APortfolioCharacter>(TryGetPawnOwner());
		if(IsValid(OwnerCharacter))
			UE_LOG(LogTemp,Warning,TEXT("OwnerCharacter"));
	}
/*
	Bow = Cast<APortfolioCharacter>(GetOwningActor()->GetOwner());
	if(!Bow)
	{
		DrawingBow = Bow->GetWeaponComponent()->GetDrawing();
		if(!Bow)
		{
			UE_LOG(LogTemp,Warning,TEXT("No Bow"));
		}
	}
	*/
}

void UMyAnimInstance::SetBlendSpace()
{
	Velocity = OwnerCharacter->GetVelocity();
	Spd = UKismetMathLibrary::VSizeXY(OwnerCharacter->GetVelocity());
	falling = OwnerCharacter->GetCharacterMovement()->IsFalling();
	Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(),
		{0,OwnerCharacter->GetControlRotation().Yaw,0});
	WeaponType = WeaponComponent->GetWeaponType();
}

void UMyAnimInstance::SetDamageCauserDirection()
{
}

void UMyAnimInstance::SetHandleLoation()
{
	if(IsValid(WeaponComponent))
		DrawBow = WeaponComponent->GetDrawing();
	if(IsValid(WeaponComponent->GetCurrentWeapon()))
	{
		HandleLocation = WeaponComponent->GetCurrentWeapon()->GetMesh()->GetSocketLocation("handleSocket");
	}
}

void UMyAnimInstance::SetAimRotation()
{
	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator
		(OwnerCharacter->GetActorRotation(), OwnerCharacter->GetControlRotation());
	
	AimRotation.Pitch = DeltaRotator.Pitch * -1;
	AimRotation.Yaw = DeltaRotator.Yaw;
	AimRotation.Roll = DeltaRotator.Roll;
}
