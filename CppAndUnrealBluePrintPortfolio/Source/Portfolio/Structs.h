#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "Structs.generated.h" // 스트럭트를 사용하기 위해서 스트럭트용 헤더 파일 인클루드부 제일 후반부에 선언해줘야 함

USTRUCT(BlueprintType)
struct FWeaponPair	// 무기정보
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* DataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseWeapon* WeaponPointer;
};

/*
USTRUCT(BlueprintType)
struct FStatus
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHp;
	
};
*/