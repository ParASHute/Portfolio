// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasckAttributeChange.h"

#include "Animation/AnimAttributes.h"

UAsyncTasckAttributeChange* UAsyncTasckAttributeChange::ListenForAttributeChange(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UAsyncTasckAttributeChange* WaitforAttributeChangeTask = NewObject<UAsyncTasckAttributeChange>();

	WaitforAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitforAttributeChangeTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitforAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	(Attribute).AddUObject(WaitforAttributeChangeTask, &UAsyncTasckAttributeChange::AttributeChange);

	return WaitforAttributeChangeTask;
}

UAsyncTasckAttributeChange* UAsyncTasckAttributeChange::ListenForAttributesChange(
	UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UAsyncTasckAttributeChange* WaitforAttributeChangeTask = NewObject<UAsyncTasckAttributeChange>();

	WaitforAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitforAttributeChangeTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitforAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}

	for(FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
		(Attribute).AddUObject(WaitforAttributeChangeTask, &UAsyncTasckAttributeChange::AttributeChange);
	}

	return WaitforAttributeChangeTask;
}

void UAsyncTasckAttributeChange::EndTask()
{
	if(IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);

		SetReadyToDestroy();
		MarkAsGarbage();
	}
}

void UAsyncTasckAttributeChange::AttributeChange(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute,Data.NewValue,Data.OldValue);
}
