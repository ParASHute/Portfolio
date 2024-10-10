// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "BaseWeapon.generated.h" 

class APortfolioCharacter; // 순환 참조를 방지하기 위한 전방 선언

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

private:
	// Default Scene Root Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneRoot;
	// Skeletal Mesh Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	USkeletalMeshComponent* SkeletalMesh;
	// Box Collision Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	UBoxComponent* Box;
	
	// OwnerCharacter
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;
};
