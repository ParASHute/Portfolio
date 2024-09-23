#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class PORTFOLIO_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// DefaultSceneRoot 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneRoot;
	// Mesh 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta=(AllowPrivateAccess=true))
	USkeletalMeshComponent* Mesh;
	// Box Collision 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta=(AllowPrivateAccess=true))
	UCapsuleComponent* Capsule;
	// 씬텀포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta=(AllowPrivateAccess=true))
	USceneComponent* StartLocation;
	// 프로젝타일 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta=(AllowPrivateAccess=true))
	UProjectileMovementComponent* ProjectileMovement;

};
