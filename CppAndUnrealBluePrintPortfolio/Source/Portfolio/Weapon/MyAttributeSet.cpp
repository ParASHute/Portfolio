// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"

#include "Net/UnrealNetwork.h" 
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UMyAttributeSet::UMyAttributeSet()
{
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, CurrentHealth, OldHealth);
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
}

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(),0.0f,GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(),0.0f,GetMaxStamina()));
	}
}

