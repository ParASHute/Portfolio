// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None	UMETA(DisplayName = "None"),

	Sword	UMETA(DisplayName = "Sword"),
	Bow		UMETA(DisplayName = "Bow"),
	Shield	UMETA(DisplayName = "Shield"),
	Monster	UMETA(DisplayName = "Monster"),
	
	Max		UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EState : uint8
{
	None		UMETA(DisplayName = "None"),
	Idle		UMETA(DisplayName = "Idle"),
	Attack		UMETA(DisplayName = "Attack"),
	JumpAttack	UMETA(DisplayName = "JumpAttack"),
	Hit			UMETA(DisplayName = "Hit"),
	Death		UMETA(DisplayName = "Death"),
	Avoid		UMETA(DisplayName = "Avoid"),
};