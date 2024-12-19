// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
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

	// 웨폰 컴포넌트 추가
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UWeaponComponent* WeaponComponent;

	// 어빌리티 시스템 컴포넌트 추가
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	class UMyAbilitySystemComponent* AbilitySystemComponent;

	// 캐릭터 관련 정보
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	const class UMyAttributeSet* AttributeSetVar;

	// 스킬관련 게임 어빌리티(에디터에서 게임 플레이가 아닐때만 세팅가능)
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<class UGameplayAbility>> InitAbilities;

public:
	// 어빌리티 시스템 컴포넌트 게터
	virtual class UMyAbilitySystemComponent* GetAbilitySystemComponent() const;

	// 웨폰 컴포넌트 게터
	virtual class UWeaponComponent* GetWeaponComponent() const;

	void HoldCamera(bool CameraHold);

	UFUNCTION(BlueprintCallable)
	FTransform GetBone(FName SocketName);
	
protected:
	/*
	// 초기 캐릭터 능력치 세팅(비긴플레이에서 세팅, 추후 컨트롤러로 보내서 HUD세팅까지 할 예정)
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	*/
	
	// 기본 체력, 마력 회복
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GAS",meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

public:
	virtual void InitializeAttribute();
	virtual void AddStartupEffects();
// 스킬 관련 함수들

	// 스킬 어려개 넣기
	UFUNCTION(BlueprintCallable,Category="GAS")
	void InitializedAbilityMulti
	(TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire,int32 AbilityLevel);

	// 스킬 하나만 넣는 것
	UFUNCTION(BlueprintCallable,Category="GAS")
	void InitializedAbility(TSubclassOf<UGameplayAbility> AbilityToGet,
		int32 AbilityLevel);

	// 플레이어가 해당 캐릭터를 조종 시작했을 때
	virtual void PossessedBy(AController* NewController) override;
	// 캐릭터 스텟 변경
	virtual void OnRep_PlayerState() override;
	
// 테그 추가, 삭제 관련	
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
	
protected:
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
	void CameraLock(bool cameraHold);
	UFUNCTION(BlueprintCallable)
	void CameraUnLock(bool cameraHold);
	UFUNCTION(BlueprintCallable)
	void SetCameraRelativePos(float Xpos, float Ypos, float Zpos);
};

