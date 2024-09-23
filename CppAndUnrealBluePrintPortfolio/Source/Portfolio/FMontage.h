#pragma once

#include "CoreMinimal.h"
#include "FMontage.generated.h"

USTRUCT(BlueprintType)
struct FAttack
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
struct FMontageStruct	// 몽타주
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate;
};
