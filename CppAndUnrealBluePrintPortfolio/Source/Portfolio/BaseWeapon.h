#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "PortfolioCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

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

private:
	// DefaultSceneRoot 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneRoot;
	// Mesh 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta=(AllowPrivateAccess=true))
	USkeletalMeshComponent* Mesh;
	// Box Collision 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta=(AllowPrivateAccess=true))
	UBoxComponent* Box;

	// 오너캐릭터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;

};
