// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UProjectileMovementComponent* GetProjectileMovementComponent();

private:
	// Default Scene Root Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneRoot;
	// Skeletal Mesh Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMesh;
	// Box Collision Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true))
	UCapsuleComponent* Capsule;
	// Projectile Movement Component
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components",meta=(AllowPrivateAccess=true))
	UProjectileMovementComponent* ProjectileMovement;
};
