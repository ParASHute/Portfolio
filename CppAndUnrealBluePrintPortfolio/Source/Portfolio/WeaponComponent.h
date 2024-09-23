#pragma once // Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "Structs.h"
#include "WeaponData.h"
#include "Components/ActorComponent.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 프라이빗으로 선언된 변수를 블루프린트에서 사용 가능하게 해주는 UPROPERTY선언 방법//meta=(AllowPrivateAccess=true)가 있어야됨
	// 현제 장착중인 무기의 데이터 에셋
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataAssets", meta=(AllowPrivateAccess=true))
	UWeaponData* CurrentDataAsset;
	// 요청한 무기의 데이터 에셋
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataAssets", meta=(AllowPrivateAccess=true))
	UWeaponData* RequestDataAsset;

	// 현제 장착죽인 무기의 포인터
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponPointer", meta=(AllowPrivateAccess=true))
	ABaseWeapon* CurrentWeapon;
	// 요청한 무기의 포인터
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponPointer", meta=(AllowPrivateAccess=true))
	ABaseWeapon* RequestWeapon;

	// 공격 가능 상테인지 확인하는 불값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	bool CanAttak;
	// 콤보시 몇번 몽타주를 재생할지 결정할 실수값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	int AttackIndex;
	// 노티파이에서 콤보 공격 활성화 구간 체크를 위한 불값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	bool ComboAreaEnable;
	// 콤보 공격중인지 확인 할 불값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	bool Combo;
	// 활을 댕겼는지 놓았는지 확인 할 불값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	bool Drawing;
	// 점프어택인지 아닌지 확인 할 불값
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	bool JumpAttack;
	// 발사할 투사체
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack", meta=(AllowPrivateAccess=true))
	ABaseProjectile* FireProjectile;

	// 이 컴포넌트를 가지고 있는 캐릭터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	APortfolioCharacter* OwnerCharacter;	// 베이스 캐릭터를 APortfolioCharacter로 설정
	// 무기의 슬롯이름과 무기를 매치 시켜둔 데이터 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TMap<EWeaponType ,FWeaponPair> Weapons;
	// 무기를 교체중인지 확인 할 불값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool Swapping;
	// 블릿타임을 위한 글로벌 타임
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float GlobalTime;
};
