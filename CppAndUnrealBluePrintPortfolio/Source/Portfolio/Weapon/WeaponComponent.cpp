// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include <map>

#include "BlueprintEditor.h"
#include "K2Node_SpawnActorFromClass.h"
#include "ShaderPrintParameters.h"
#include "VisualizeTexture.h"
#include "CookOnTheSide/CookOnTheFlyServer.h"
#include "Portfolio/PortfolioCharacter.h"
#include "UniversalObjectLocators/UniversalObjectLocatorUtils.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Set OwnerPlayer
	OwnerCharacter = Cast<APortfolioCharacter>(GetOwner());

	// 무기 스폰
	SpawnWeapons();
	
	// AttachWeapons
	for(auto& temp : Weapons)
	{
		if(IsValid(temp.Value.DataAsset) && IsValid(temp.Value.WeaponPointer))
		{
			AttachWeapon
			(temp.Value.WeaponPointer, temp.Value.DataAsset->GetHolsterSocketName());
		}
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// Notify
bool UWeaponComponent::GetDrawing() const
{
	return Drawing;
}

EWeaponType UWeaponComponent::GetWeaponType() const
{
	if(IsValid(CurrentWeaponDataAsset))
		return CurrentWeaponDataAsset->GetWeaponType();

	else
		return EWeaponType::None;
}

ABaseWeapon* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

FWeaponNotify UWeaponComponent::GetRequest() const
{
	FWeaponNotify Request;
	Request.RequestWeapon = RequestWeapon;
	Request.SocketName = RequestWeaponDataAsset->GetHandleSocketName();
	return Request;
}

FWeaponNotify UWeaponComponent::GetCurrent() const
{
	FWeaponNotify Current;
	Current.RequestWeapon = CurrentWeapon;
	Current.SocketName = CurrentWeaponDataAsset->GetHolsterSocketName();
	return Current;
}

void UWeaponComponent::SetEndEquip()
{
	CurrentWeapon = RequestWeapon;
	CurrentWeaponDataAsset = RequestWeaponDataAsset;
	RequestWeapon = nullptr;
	RequestWeaponDataAsset = nullptr;
	Swapping = false;
	CanAttack = true;
}

void UWeaponComponent::SetEndUnequip()
{
	CurrentWeapon = nullptr;
	CurrentWeaponDataAsset = nullptr;
	Swapping = false;
	CanAttack = true;
}

void UWeaponComponent::EndAttack()
{
	CanAttack = true;
	CurrentWeapon->EndAttack();
	if(IsValid(FireProjectile))
	{
		FVector velocity;
		velocity = FireProjectile->GetProjectileMovementComponent()->Velocity;
		if(velocity.IsNearlyZero(0.0001))
		{
			FireProjectile->K2_DestroyActor();
		}
	}
}

void UWeaponComponent::ComboDetectsStart()
{
	ComboAreaEnable = true;
}

void UWeaponComponent::ComboDetectsEnd()
{
	ComboAreaEnable = false;
}

void UWeaponComponent::PlayNextCombo()
{
	if(Combo)
	{
		ComboAreaEnable = false;
		UAnimMontage* montage = RequestWeaponDataAsset->GetAttackMontage(ComboIndex).Montage;
		float playRate = RequestWeaponDataAsset->GetAttackMontage(ComboIndex).PlayRate;
		
		if(IsValid(montage))
		{
			OwnerCharacter->PlayAnimMontage(montage, playRate);
		}
	}
}

void UWeaponComponent::SpawnWeapons()
{
	TMap<EWeaponType,FWeaponPair> Temp;

	for(auto& temp : Weapons)
	{
		if(IsValid(temp.Value.DataAsset->GetWeaponClass()))
		{
			ABaseWeapon* SpawnedWeapon = SpawnWeapon(temp.Value.DataAsset);
			Temp.Add(temp.Key,{temp.Value.DataAsset, SpawnedWeapon});
		}
	}
	// Temp에 있는 값을 넣기 전에, 혹시 몰라서 Weapons에 있는 데이터들을 지움
	Weapons.Empty();
	// Temp에 있는 값(혹은 값들)을 Weapons에 넣음
	Weapons = Temp;
}

ABaseWeapon* UWeaponComponent::SpawnWeapon(UWeaponData* inWeaponData)
{
	ABaseWeapon* OutWeapon = nullptr;
	
	FVector Location(0.0f, 0.0f, 0.0f);  
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;
	
	/*
	// MakeTransFrom
	FVector Scale(1.0f, 1.0f, 1.0f);
	FTransform SpawnTransform;
	// FQuat는 쿼터니언(4원수)로 만들어주는 용도
	SpawnTransform.SetRotation(FQuat(Rotation));
	SpawnTransform.SetLocation(Location);
	SpawnTransform.SetScale3D(Scale);
	*/
	
	if(IsValid(inWeaponData))
	{
		// SpawnActor from Class
		OutWeapon = GetWorld()->SpawnActor<ABaseWeapon>(inWeaponData->GetWeaponClass(),Location,Rotation,SpawnParams);
	}
	

	return OutWeapon;
}

void UWeaponComponent::AttachWeapon(ABaseWeapon* inWeaponPointer, FName inSocketName)
{
	/*
		AttachToComponent의 사용 방법
		target->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, FName);
	 */ 
	inWeaponPointer->AttachToComponent
	(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, inSocketName);
}

void UWeaponComponent::SelectWeapon(EWeaponType inWeaponslot)
{
	if(Swapping == false)
	{
		if(IsValid(CurrentWeapon))
		{
			if(Weapons.Find(inWeaponslot))
			{
				if(CurrentWeapon == Weapons.Find(inWeaponslot)->WeaponPointer)
				{
					UnEquipCurrentWeapon();
				}
				else
				{
					AttachWeapon(CurrentWeapon, CurrentWeaponDataAsset->GetHolsterSocketName());
					if(Weapons.Find(inWeaponslot))
					{
						EquipWeapon(Weapons.Find(inWeaponslot)->DataAsset
							, Weapons.Find(inWeaponslot)->WeaponPointer);
					}
				}
			}
		}
		else
		{
			if(Weapons.Find(inWeaponslot))
			{
				EquipWeapon(Weapons.Find(inWeaponslot)->DataAsset
					, Weapons.Find(inWeaponslot)->WeaponPointer);
			}
			
		}
	}
}

void UWeaponComponent::UnEquipCurrentWeapon()
{
	if(IsValid(CurrentWeaponDataAsset->GetUnequipMontage().Montage))
	{
		OwnerCharacter->PlayAnimMontage
		(CurrentWeaponDataAsset->GetUnequipMontage().Montage,
			CurrentWeaponDataAsset->GetUnequipMontage().PlayRate);
		Swapping = false;
	}
}

void UWeaponComponent::EquipWeapon(UWeaponData* inWeaponDataAsset,ABaseWeapon* inWeaponPtr)
{
	if(IsValid(inWeaponDataAsset->GetEquipMontage().Montage))
	{
		RequestWeapon = inWeaponPtr;
		RequestWeaponDataAsset = inWeaponDataAsset;
		OwnerCharacter->PlayAnimMontage
		(inWeaponDataAsset->GetEquipMontage().Montage,
			inWeaponDataAsset->GetEquipMontage().PlayRate);
		Swapping = false;
	}
}
