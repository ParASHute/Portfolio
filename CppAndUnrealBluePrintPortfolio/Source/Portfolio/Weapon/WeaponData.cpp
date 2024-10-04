// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponData.h"

#include "GameFramework/SpringArmComponent.h"

UWeaponData::UWeaponData()
{
}

FName UWeaponData::GetHandleSocketName()
{
	return HandleSocketName;
}

FName UWeaponData::GetHolsterSocketName()
{
	return HolsterSocketName;
}

FAttack UWeaponData::GetAttackMontage(int Index)
{
	return AttackMontages[Index];
}

FMontage UWeaponData::GetUnequipMontage()
{
	return UnequipMontage;
}

FMontage UWeaponData::GetEquipMontage()
{
	return EquipMontage;
}

TSubclassOf<ABaseWeapon> UWeaponData::GetWeapon()
{
	return WeaponClass;
}
