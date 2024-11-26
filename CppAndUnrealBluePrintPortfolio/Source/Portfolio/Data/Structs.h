// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"

class ABaseWeapon;
class UWeaponData;
class APortfolioCharacter;

USTRUCT(BlueprintType)
struct FWeaponPair
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* DataAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ABaseWeapon* WeaponPointer;
};

USTRUCT(BlueprintType)
struct FWeaponNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseWeapon* RequestWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
};

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APortfolioCharacter* CharacterPointer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
};


// MontageStructs
USTRUCT(BlueprintType)
struct  FAttack	// 공격용 몽타주(데미지를 가지고 있음)
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
};

USTRUCT(BlueprintType)
struct FMontage	// 일반 몽타주(데미지 미포함)
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate = 1.0f;
};