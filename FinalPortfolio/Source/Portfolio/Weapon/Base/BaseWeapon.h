// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Portfolio/Data/Structs.h"
#include "GameFramework/Actor.h"

#include "BaseWeapon.generated.h" 

// 순환 참조를 방지하기 위한 전방 선언
class APortfolioCharacter;

UCLASS()
class PORTFOLIO_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndAttack();
	USkeletalMeshComponent* GetMesh();

	UFUNCTION(BlueprintCallable, Category = "Trace")
	AActor* Trace(/*FString TagName*/);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> SetObjectTypes(ECollisionChannel ChannelName);

private:
	// Default Scene Root Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneRoot;
	// Skeletal Mesh Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	USkeletalMeshComponent* SkeletalMesh;
	
	// OwnerCharacter
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;

	//TraceChenel
	ECollisionChannel PlayerToUseChannel = ECollisionChannel::ECC_GameTraceChannel1;
	ECollisionChannel MonsterToUseChannel = ECollisionChannel::ECC_GameTraceChannel2;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TArray<AActor*> Temp;
};
