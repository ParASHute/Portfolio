// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

UCLASS()
class PORTFOLIO_API UMyAbilitySystemComponent : public UAbilitySystemComponent 
{
	GENERATED_BODY()
	
public:
	bool StartUpEffectApplied = false;
};