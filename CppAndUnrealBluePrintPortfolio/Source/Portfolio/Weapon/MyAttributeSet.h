// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MyAbilitySystemComponent.h"

#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttrChangeDelegate, float, Attr, int32, StackCount);

UCLASS()
class PORTFOLIO_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMyAttributeSet(); // 생성자

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(BlueprintReadOnly,Category="Attributes",ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly,Category="Attributes",ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth);

	FAttrChangeDelegate HealthChangeDelegate;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
