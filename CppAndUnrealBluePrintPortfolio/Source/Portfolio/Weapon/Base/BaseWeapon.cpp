// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "Portfolio/PortfolioCharacter.h"	// Cpp 내 APortfolioCharacter의 불확실성 해결을 위한 헤더 선언

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Default Scene Root Component
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;

	// Set Skeletal Mesh Component
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(RootComponent); // Attach RootComponent

	// Set Box Collision Component
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(SkeletalMesh); // Attach StaticMesh
	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // SetCollisionProfile

	// Set OwnerCharacter
    if (AActor* Owner = GetOwner())	// Onwer에 GetOner설정이 된다면
	{
		OwnerCharacter = Cast<APortfolioCharacter>(Owner); // OwnerCharacter에 Owner를 넣고

		if (OwnerCharacter)	// 성공시 메시지
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is APortfolioCharacter: %s"), *OwnerCharacter->GetName());
		}
		else // 실패시 메시지
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is not APortfolioCharacter."));
		}
	}
	else // Onwer에 GetOner설정이 실패시
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

void ABaseWeapon::EndAttack()
{
}

