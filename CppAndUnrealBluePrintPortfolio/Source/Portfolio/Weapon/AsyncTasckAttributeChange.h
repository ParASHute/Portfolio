// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyAbilitySystemComponent.h"
#include "AsyncTasckAttributeChange.generated.h"


// 파라미터 3개짜리 델리게이트 여러개
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute,
	Attribute, float, NewValue,
	float, OldValue);

// 블루프린트 노드에서 자동으로 리스너를 등록해, 어트리뷰트가 변경 됐을 때 호출하도록 함
// UBluePrintAsyncActionBase를 블루프린트에서 아무때나 호출 가능하도록 함
UCLASS(BlueprintType,meta=(ExposedAsyncProxy=AsyncTask))
class PORTFOLIO_API UAsyncTasckAttributeChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// 함수 포인터
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged; // 함수 포인터

	UFUNCTION(BlueprintCallable,meta=(BlueprintBaseOnly = ture))
	static UAsyncTasckAttributeChange* ListenForAttributeChange(
		UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable,meta=(BlueprintBaseOnly = ture))
	static UAsyncTasckAttributeChange* ListenForAttributesChange(
		UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChange(const  FOnAttributeChangeData& Data);
};
