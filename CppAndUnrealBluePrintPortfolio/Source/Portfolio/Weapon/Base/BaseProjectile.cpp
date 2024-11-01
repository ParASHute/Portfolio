// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Default Scene Root Component
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	// Set Skeletal Mesh Component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent); // Attach RootComponent

	// Set Capsule Collision Component
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Box");
	Capsule->SetupAttachment(StaticMesh); // Attach StaticMesh
	Capsule->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // SetCollisionProfile

	// Set Projectile Movement Component
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->bRotationFollowsVelocity = true; // Follow Fire Direction
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UProjectileMovementComponent* ABaseProjectile::GetProjectileMovementComponent()
{
	return ProjectileMovement;
}

