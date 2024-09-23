#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8	// 무기 타입
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Bow  UMETA(DisplayName = "Bow"),
};

UENUM(BlueprintType)
enum class EState :uint8	// 상태
{
	None UMETA(DisplayName = "None"),
	Idle UMETA(DisplayName = "Idle"),
	Attack UMETA(DisplayName = "Attack"),
	JumpAttack UMETA(DisplayName = "JumpAttack"),
	Death UMETA(DisplayName = "Death"),
	Hitted UMETA(DisplayName = "Hitted"),
	Avoid  UMETA(DisplayName = "Avoid"),
};

/*
UENUM(BlueprintType)
enum class EWeaponSlot : uint8	// 무기의 슬롯
{
	None UMETA(DisplayName = "None"),
	Sword UMETA(DisplayName = "Sword"),
	Bow  UMETA(DisplayName = "Bow"),
};
*/