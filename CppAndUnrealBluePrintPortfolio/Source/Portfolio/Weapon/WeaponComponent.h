// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "Components/ActorComponent.h"	// 씬 컴포넌트로 잘못 생성시 헤더파일과 부모클래스를 바꾸면 된다.
#include "Portfolio/Data/Structs.h"

#include "WeaponComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UWeaponComponent : public UActorComponent
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
	virtual void TickComponent
	(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Getter
	bool GetDrawing();

	// Notities
	UFUNCTION(BlueprintPure, Category = "Notify")
	FWeaponNotify GetRequest();
	UFUNCTION(BlueprintPure, Category = "Notify")
	FWeaponNotify GetCurrent();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void SetEndEquip();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void  SetEndUnequip();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void ComboDetectsStart();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void ComboDetectsEnd();
	UFUNCTION(BlueprintCallable, Category = "Notify")
	void PlayNextCombo();

	// Function Called in Notify
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void SpawnWeapons();
	UFUNCTION(BlueprintCallable, Category = "Equip")
	ABaseWeapon* SpawnWeapon(UWeaponData* inWeaponData);
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void AttachWeapon(ABaseWeapon* inWeaponPointer, FName inSocketName);
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void SelectWeapon(EWeaponType inWeaponslot);
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void UnEquipCurrentWeapon();
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void EquipWeapon(UWeaponData* inWeaponDataAsset,ABaseWeapon* inWeaponPtr);

	
	
private:
	// TSubclassOf<UWeaponData>으로 하지 않으면 블루 프린트에서 안들어가짐
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="DataAsset",meta=(AllowPrivateAccess=true))
	UWeaponData* CurrentWeaponDataAsset;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="DataAsset",meta=(AllowPrivateAccess=true))
	UWeaponData* RequestWeaponDataAsset;

	// CurrentWeaponDataAsset와 RequestWeaponDataAsset의 함수 호출등의 이유로 필요한 변수
	//UWeaponData* CurrenDataAsset;
	//UWeaponData* RequestDataAsset;
	//ABaseWeapon* test;

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
