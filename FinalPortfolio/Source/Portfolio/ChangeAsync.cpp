// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeAsync.h"

UChangeAsync* UChangeAsync::ListenForAttribute(UAbilitySystemComponent* ASC, FGameplayAttribute GPA)
{
   //Static 함수호출시 UAsyncTaskAttributeChanged 클래스 생성뒤 실행
   UChangeAsync* WaitforAttributeChangedTask = NewObject<UChangeAsync>();

   //블루프린트에서 넣은 해당 정보 기입
   WaitforAttributeChangedTask->ASC = ASC;
   WaitforAttributeChangedTask->AttributeListenFor = GPA;

   //파라미터가 잘못되면
   if (!IsValid(ASC) || !GPA.IsValid())
   {
      //생성한 오브젝트를 다시 지운다, 언리얼꺼라 알아서 나중에 지워짐
      WaitforAttributeChangedTask->RemoveFromRoot();
      return nullptr;
   }
   ASC->GetGameplayAttributeValueChangeDelegate(GPA).AddUObject(WaitforAttributeChangedTask, &UChangeAsync::ListenChange);

   return WaitforAttributeChangedTask;
}

UChangeAsync* UChangeAsync::ListenForAttributes(UAbilitySystemComponent* ASC, TArray<FGameplayAttribute> GPAS)
{
   //Static 함수호출시 UAsyncTaskAttributeChanged 클래스 생성뒤 실행
   UChangeAsync* WaitforAttributeChangedTask = NewObject<UChangeAsync>();

   //블루프린트에서 넣은 해당 정보 기입
   WaitforAttributeChangedTask->ASC = ASC;
   WaitforAttributeChangedTask->AttributesListenFor = GPAS;

   //파라미터가 잘못되면
   if (!IsValid(ASC) || GPAS.Num() < 1)
   {
      //생성한 오브젝트를 다시 지운다, 언리얼꺼라 알아서 나중에 지워짐
      WaitforAttributeChangedTask->RemoveFromRoot();
      return nullptr;
   }

   //여러개 한번에 등록
   for (FGameplayAttribute Attribute : GPAS)
   {
      ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitforAttributeChangedTask, &UChangeAsync::ListenChange);
   }

   return WaitforAttributeChangedTask;
}

void UChangeAsync::EndTask()
{
   if (IsValid(ASC))
   {
      ASC->GetGameplayAttributeValueChangeDelegate(AttributeListenFor).RemoveAll(this);

      //여러개
      for (FGameplayAttribute Attribute : AttributesListenFor)
      {
         ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
      }
   }

   //테스크 삭제
   SetReadyToDestroy();
   MarkAsGarbage();
}

void UChangeAsync::ListenChange(const FOnAttributeChangeData& Data)
{
   //Health,새로운 HP,이전 HP
   ChangeStatuse.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
