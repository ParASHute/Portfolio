// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MontageStruct.generated.h"

USTRUCT(BlueprintType)
struct  FAttack	// 공격용 몽타주(데미지를 가지고 있음)
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate;
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
	float PlayRate;
};