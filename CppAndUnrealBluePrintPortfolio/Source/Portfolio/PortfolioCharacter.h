// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "Weapon/WeaponComponent.h"
#include "Weapon/MyAbilitySystemComponent.h"
#include "Weapon/MyAttributeSet.h"

#include "PortfolioCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class UMyAbilitySystemComponent;
class UMyAttributeSet;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APortfolioCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	UWeaponComponent* WeaponComponent;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	class UMyAbilitySystemComponent* AbilitySystemComponent;

	virtual class UMyAbilitySystemComponent* GetAbilitySystemComponent() const;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	const class UMyAttributeSet* AttributeSetVar;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<class UGameplayAbility>> InitAbilities;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

public:
	virtual void InitializeAttribute();
	virtual void AddStartupEffects();

	UFUNCTION(BlueprintCallable,Category="GAS")
	void InitializedAbilityMulti
	(TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire,int32 AbilityLevel);
	
	UFUNCTION(BlueprintCallable,Category="GAS")
	void InitializedAbility(TSubclassOf<UGameplayAbility> AbilityToGet,
		int32 AbilityLevel);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable,Category="GAS")
	void RemoveAbilityWithTags(FGameplayTagContainer TagContainer);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void ChangeAbilityLevelWithTags (FGameplayTagContainer TagContainer,int32 Level);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void CancleAbilityWithTags(FGameplayTagContainer WithTag,
		FGameplayTagContainer WithoutTags);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void AddLoosGamePlayTag(FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void RemoveLoosGamePlayTag(FGameplayTag TagToRemove);
	
public:
	APortfolioCharacter();

	UFUNCTION()
	virtual void OnHealthChangeNative(float Health, int32 StatckCount);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void OnHealthChanged(float Health, int32 StatckCount);

	UFUNCTION(BlueprintCallable,Category="GAS")
	void HealthValues(float& Health, float& MaxHealth);

	UFUNCTION(BlueprintCallable,Category="GAS")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable,Category="GAS")
	float GetMaxHealth() const;

	
protected:

	virtual void Death();

	UFUNCTION(BlueprintCallable,Category="GAS")
	void FinishDeath();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void SetRagDoll();
	UFUNCTION(BlueprintCallable)
	void CameraLock(bool cameraHold);
	UFUNCTION(BlueprintCallable)
	void CameraUnLock(bool cameraHold);
	UFUNCTION(BlueprintCallable)
	void SetCameraRelativeYpos(float Ypos);
	UFUNCTION(BlueprintCallable)
	void DestroyCharacter();
};

