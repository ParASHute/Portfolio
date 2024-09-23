// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "PortfolioCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// DefaultSceneRoot 생성
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// Skeletal Mesh 생성 및 DefaultSceneRoot에 자식으로 설정
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(DefaultSceneRoot);  // DefaultSceneRoot에 자식으로 설정

	// Box Collision 생성 및 Mesh에 자식으로 설정
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	Box->SetupAttachment(Mesh);  // Mesh에 자식으로 설정

	// Box Collision의 콜리전 설정
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		OwnerCharacter = Cast<APortfolioCharacter>(OwnerActor);

		if (OwnerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is APortfolioCharacter: %s"), *OwnerCharacter->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is not APortfolioCharacter."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Owner found."));
	}
	
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

