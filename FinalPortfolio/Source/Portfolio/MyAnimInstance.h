// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapon/WeaponComponent.h"
#include "PortfolioCharacter.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class PORTFOLIO_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	// 애니메이션에서는 isvalid를 통해서 컴포넌트와 클래스를 검사하는 것 보다는 이미 여기서 nullptr넣고 시작하자
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	void SetBlendSpace();
	void SetDamageCauserDirection();
	void SetHandleLocation();
	void SetAimRotation();;
	void CheckTagJumpAttack();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;
	
	// Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component",meta=(AllowPrivateAccess=true))
	UWeaponComponent* WeaponComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component",meta=(BlueprintThreadSafe, AllowPrivateAccess=true))
	UMyAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	bool JumpAttackTagCount;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	bool JumpTag;	// 쉴드중에 점프 막기위해 만든 불리안(미사용변수)
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	bool BulletTimeTag;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	float Spd;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	bool falling;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	float Direction;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	FVector Velocity;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	EWeaponType WeaponType;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	float DamageCauserDirection;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	FVector DamageCauserLocation;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	FVector HandleLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BlendSpace",meta=(AllowPrivateAccess=true))
	FRotator AimRotation;
	
	// ABP_Character
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool DrawBow;

	/*
	 애님 인스턴스는 같은 스캘래탈 매쉬를 공유하는 것끼리만 상속
	// ABP_Bow
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	bool DrawingBow;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	FVector HandleLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	FRotator AimRotation;
	*/
};
