// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "PortfolioCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	WeaponComponent = nullptr;
	OwnerCharacter = nullptr;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	OwnerCharacter = Cast<APortfolioCharacter>(TryGetPawnOwner());
	WeaponComponent = OwnerCharacter->GetWeaponComponent();
	if(IsValid(OwnerCharacter))
	{
		if(IsValid(WeaponComponent))
		{
			SetBlendSpace();
			SetDamageCauserDirection();
			SetHandleLoation();
			SetAimRotation();			
		}
		else
			WeaponComponent = OwnerCharacter->GetWeaponComponent();
	}
	else
		OwnerCharacter = Cast<APortfolioCharacter>(TryGetPawnOwner());

	APortfolioCharacter* Character = Cast<APortfolioCharacter>(GetOwningActor()->GetOwner());
	if(IsValid(Character))
	{
		DrawingBow = Character->GetWeaponComponent()->GetDrawing();
	}
}

void UMyAnimInstance::SetBlendSpace()
{
}

void UMyAnimInstance::SetDamageCauserDirection()
{
}

void UMyAnimInstance::SetHandleLoation()
{
}

void UMyAnimInstance::SetAimRotation()
{
}
