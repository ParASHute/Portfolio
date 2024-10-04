// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portfolio/Weapon/Base/BaseWeapon.h"
#include "Portfolio/Weapon/WeaponData.h"
#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FWeaponPair	// 순환 참조 방지를 위한 스트럭트 분리
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWeaponData> DataAsset;
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