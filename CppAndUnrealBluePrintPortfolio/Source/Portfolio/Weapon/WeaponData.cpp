// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponData.h"

#include "GameFramework/SpringArmComponent.h"

UWeaponData::UWeaponData()
{
}

FName UWeaponData::GetHandleSocketName() const
{
	return HandleSocketName;
}

FName UWeaponData::GetHolsterSocketName() const
{
	return HolsterSocketName;
}

FAttack UWeaponData::GetAttackMontage(int Index)
{
	return AttackMontages[Index];
}

FMontage UWeaponData::GetUnequipMontage() const
{
	return UnequipMontage;
}

FMontage UWeaponData::GetEquipMontage() const
{
	return EquipMontage;
}

TSubclassOf<ABaseWeapon> UWeaponData::GetWeaponClass() 
{
	return WeaponClass;
}

ABaseWeapon* UWeaponData::GetWeapon() const
{
	return NewObject<ABaseWeapon>(WeaponClass);
}

EWeaponType UWeaponData::GetWeaponType() const
{
	return WeaponType;
}

TArray<FMontage> UWeaponData::GetHitMontages() const
{
	return HitMontages;
}

float UWeaponData::GetWeaponDamage()
{
	return WeaponDamage;
}

