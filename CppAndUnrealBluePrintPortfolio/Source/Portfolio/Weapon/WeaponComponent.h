// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "Components/SceneComponent.h"
#include "Portfolio/Data/Structs.h"

#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="DataAsset",meta=(AllowPrivateAccess=true))
	UWeaponData* CurrentWeaponDataAsset;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="DataAsset",meta=(AllowPrivateAccess=true))
	UWeaponData* RequestWeaponDataAsset;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="WeaponPointer",meta=(AllowPrivateAccess=true))
	ABaseWeapon* CurrentWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="WeaponPointer",meta=(AllowPrivateAccess=true))
	ABaseWeapon* RequestWeapon;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	bool CanAttack;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	bool ComboAreaEnable;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	bool Combo;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	bool Drawing;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	bool JumpAttack;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	int ComboIndex;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attack",meta=(AllowPrivateAccess=true))
	ABaseProjectile* FireProjectile;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	TMap<EWeaponType,FWeaponPair> Weapons;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool Swapping;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	float GlobalTime;
	
};
