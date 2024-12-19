// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Weapon/AsyncTasckAttributeChange.h"
#include "ChangeAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(FChangeValue, FGameplayAttribute, Attribute, float, NewVal, float, OldVal);

UCLASS(BlueprintType,meta=(ExposedAsyncProxy = AsyncTask))
class PORTFOLIO_API UChangeAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FChangeValue ChangeStatuse;	// 함수 포인터

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UChangeAsync* ListenForAttribute(UAbilitySystemComponent* ASC, FGameplayAttribute GPA);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UChangeAsync* ListenForAttributes(UAbilitySystemComponent* ASC, TArray<FGameplayAttribute> GPAS);

	UFUNCTION(BlueprintCallable)
	void EndTask();
	
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeListenFor;
	TArray<FGameplayAttribute> AttributesListenFor;

	void ListenChange(const FOnAttributeChangeData& Data);


};
