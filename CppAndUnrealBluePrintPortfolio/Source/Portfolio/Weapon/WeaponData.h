// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Portfolio/Weapon/Base/BaseProjectile.h"
#include "Portfolio/Weapon/Base/BaseWeapon.h"
#include "Portfolio/Data/Enums.h"
#include "Portfolio/Data/MontageStruct.h"

#include "WeaponData.generated.h"

UCLASS()
class PORTFOLIO_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UWeaponData();

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Socket",meta=(AllowPrivateAccess=true))
	FName HandleSocketName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Socket",meta=(AllowPrivateAccess=true))
	FName HolsterSocketName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Montages",meta=(AllowPrivateAccess=true))
	FMontage EquipMontage;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Montages",meta=(AllowPrivateAccess=true))
	FMontage UnequipMontage;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Montages",meta=(AllowPrivateAccess=true))
	TArray<FMontage> HitMontages;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Montages",meta=(AllowPrivateAccess=true))
	TArray<FMontage> DeathMontage;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Montages",meta=(AllowPrivateAccess=true))
	TArray<FAttack> AttackMontages;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile",meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseProjectile> ProjectileClass; // Class Reference Type
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile",meta=(AllowPrivateAccess=true))
	float ProjectileSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile",meta=(AllowPrivateAccess=true))
	bool LockCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile",meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseWeapon> WeaponClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile",meta=(AllowPrivateAccess=true))
	EWeaponType WeaponType;
};
