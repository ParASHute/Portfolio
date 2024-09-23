#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "BaseWeapon.h"
#include "Enums.h"
#include "FMontage.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * 
 */

UCLASS()
class PORTFOLIO_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UWeaponData();

private:
	// 무기가 장착될 핸들 소켓 이름
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Socket", meta=(AllowPrivateAccess=true))
	FName HandleSocketName;
	// 무기가 고정될 핸들 소켓 이름
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Socket", meta=(AllowPrivateAccess=true))
	FName HolsterSocketName;
	
	// 무기 장착 몽타주
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Montage", meta=(AllowPrivateAccess=true))
	FMontageStruct EquipMontage;
	// 무기 헤제 몽타주
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Montage", meta=(AllowPrivateAccess=true))
	FMontageStruct UnequipMontage;
	// 공격 몽타주
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Montage", meta=(AllowPrivateAccess=true))
	TArray<FMontageStruct> AttackMontage;
	// 피격 몽타주
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Montage", meta=(AllowPrivateAccess=true))
	TArray<FMontageStruct> HitMontage;
	// 사망 몽타주
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Montage", meta=(AllowPrivateAccess=true))
	TArray<FMontageStruct> DeathMontage;

	// 발사체 (클래스레퍼런스)
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Projectile", meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseProjectile> ProjectileClass;	// 클래스 레퍼런스
	// 발사체 속도
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Projectile", meta=(AllowPrivateAccess=true))
	float ProjectileSpd;
	// 카메라 고정 
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Projectile", meta=(AllowPrivateAccess=true))
	bool CameraLock;

	// 무기(클래스 레퍼런스)
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<ABaseWeapon> WeaponClass;
	// 무기 타입
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(AllowPrivateAccess=true))
	EWeaponType Weapontype;
	
};
