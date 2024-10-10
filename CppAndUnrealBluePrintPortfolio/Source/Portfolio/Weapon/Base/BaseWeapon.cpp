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
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// OwnerCharacter에 GetOwner를 넣고
	OwnerCharacter = Cast<APortfolioCharacter>(GetOwner());
	
	// OwnerCharacter
	if (!OwnerCharacter)	// Onwer에 GetOner설정이 된다면
	{
		OwnerCharacter = Cast<APortfolioCharacter>(GetOwner());
    	
		if (!OwnerCharacter)	// 성공시 메시지
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner founded."));
		}
	}
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::EndAttack()
{
}

USkeletalMeshComponent* ABaseWeapon::GetMesh()
{
	return SkeletalMesh;
}

