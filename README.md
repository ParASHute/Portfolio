# [BluePrint Portfolio](https://youtu.be/kCPOy8IhQ5k)

### Too long, Check README.md('24.08.07)
        :
    기본무기 장착을 위한 소켓 생성
    기본무기 스폰 및 장착 기본무기 장착  
    몽타주 생성 및 적용 기본무기 장착  
    몽타주를 이동중에도 자연스럽게 하기 위한 Animation BluePrint 수정  
 
    보조무기(활)장착을 위한 소켓 생성  
    보조무기(활) BP_Bow 생성  
    보조무기 데이터 애셋 DA_Bow생성  

    투사체들을 제어하기 위한 BP_BaseProjectile 생성  
    투사체(화살) BP_Arrow 생성  
    투사체 스폰을 관리하기 위한 소켓 생성  

	
## Finish BluePrint Portfolio('24.09.17) 
        :
    스테이트에 어택 넣고 점프에서 스태이트 아이들일때 점프 가능하게 하기
    -> 공격 중에 점프하는 것 방지

    공격중일때 안끊긴다
    ->PlayNecCombo에서 ComboEnable을 Branch로 검사해야되는데, 
    ComboAreaEnable을 검사하고 있어서 같은 공격을 계속(수정완)

    게임 타임이용한 블릿타임 만들기

    활쏘고 나서 점프 안됨
    ->애니메이션에서의 문제(수정완)

    점프 공격(블릿타임)이 안됨 델리게이트 이용해야 하나?
    -> 점프를 하고나서 블릿타임을 콜하지 않아서 생긴일(수정완)

    스테이트에 jumpAttack을 넣어주고, 이거 조건으로 블릿타임 수정하는게 맞을듯 하다

    왜인지 어태치 애로우가 재대로 작동을 안함(중간에 붙고 거기서 끝)
    ->BP_Link의 메시 콜리전과 BP_Arrow의 콜리전이 충돌해서 벌어지는 일(수정완)

    어태치 애로우가 재대로 작동을 안함
    -> 위 문제에서 BP_Arrow의 콜리전을 잘못 수정해서 생긴 일(수정완)

    공격중간에 무기 바꾸면 다신 공격 못함
    -> 공격중에 바꾸면 CanAttack이 바뀌지 않아서 생긴일(수정완)
        -> EndEqiup부분의 마지막에 CanAttack을 true로 바꿔주기

    에임 오프셋 적용

    블레이드 점프 공격 만들기

## 포트폴리오를 마치며</br>
    :
        1. 미완성 상태에서 블루프린트 포트폴리오를 마친 이유
           :
            포트폴리오에서 아직 부족한 부분이 많다. '젤다의 전설 : 야생의 숨결'을 모작하는 단계에서 아직 부족한 부분이 많다.
            하지만, 지금 공부하고 있는 부분이 Cpp로 진도가 나감에 따라 
            블루프린트에서의 작업을 마무리 하고 Cpp로 부족한 부분과 기능을 완성할 예정이다.

        2. 부족한 기능들
           :
            사당(거점)을 이용한 순간이동
            방패를 이용한 막기, 러시타임, 패링
            점프 공격시 주변 충격파 생성
            여러가지 행동 패턴을 가진 다양한 종류의 몬스터들

        3. 수정해야 될 기능들
           :
            점프공격
                -> 아직까지 부족한 기능과, 모션관련
            각 애니메이션의 속도와 이동속도의 차이로 생긴 밀림 현상

        4. 마무리
           :
            대학교에서 VR과 AR을 위한 유니티를 배웠고, 
            DX를 학원에서 배우며 간단하게 케릭터를 움직이고 공격하는 간단한 조작을 만들었다.
            언리얼을 배우기전 학교에서 배운 간단한 게임을 만드는 기능들 조금 더 알아보기 위해서 
            언리얼을 배우기 전 유니티를 간단하게 복습하며 공부 했었고, 
            그렇게 배운 것을 통해 간단한 닷지 게임과 유니티에서 사용하는 간단한 이론들을 공부했다.
            언리얼을 배우면서 유니티와 다른점들과, 조금 더 많은 기능들을 이용해서 게임을 만드는 점들을 배웠다.
            언리얼을 배우면서 여태까지 했던 게임들에서의 여러 기능들을 어떤 식으로 구현 했는지에 대해 고민을 했고, 
            그중 최근 제일 재미있게 즐겼던 야숨이라 부르는 '젤다의 전설 : 야생의 숨결'을 모작해 보기로 했다.
            프로젝트를 진행하면서 생각보다 많은 기능이 있었고 이를 다 구현 하기에는 아직까지 실력이 부족하다는 것도 알았다.
            프로젝트를 진행해 나가면서 진도는 어느덧 블루프린트를 지나, 
            Cpp로 넘어갔고 이를 활용해 부족한 기능들을 체워 넣기로 결정해 아직 많은 부분들이 비어 있는 상태에서 
            블루프린트포트폴리오를 마감하기로 했다.
            이를 마감 후 약간의 하루 정도의 쉬는 시간과 
            이틀 정도의 Cpp프로젝트로 지금 구현된 기능들을 이식하는 작업, 
            그리고 마무리와 동시에 Cpp의 작업을 시작할 예정이다.


# [CppAndUnrealBluePrintPortfolio](https://youtu.be/2Ql3Z-8IVAU)

## Transplantation Process
    :
        weapon이 NotValid가 됨 
        -> DA를 WeaponData를 상속받는 블프가 아니라 기타의 데이터 에셋에서

        WeaponData Cpp클래스를 참조해서 만들어야 했음
        -> 위방식을 사용한다면 “TSubclass<>”을 사용하지 않아도 됨

        cpp 내 weaponComponemt 수정시 BP에서의 문제가 생김
        -> 일단은 HotLode의 문제일수 있음, 

        Bow 관련 소켓, 장착 몽타주.  bow관련 노티파이들

        가능하면 ABP 셍성 후 적용(Character우선)
        -> MyAnimInstance를 상속 받은 ABP가 생성되지 않음

        UnequipMontage가 IsNotValid라는 에러 메세지 출력
        -> “GetCurrent”의 “SocketName”이 “HolsterSocketName” 이 아닌 “HandleSocketName”으로
	
        “UnEquipCurrentWeapon”내에서 체크하는 IsValid를 확인 해야 하는
        변수가 “CurrentWeaponDataAsset”이 아니라 RequestWeaponDataAsset”이기 때문에 생긴 문제 
        방패는 장착이 아니라 노티파이 해서 사용해서 그냥 크기 키우기

        Create a Playable Character
            :
                방패 장착 완료
                -> 몽타주를  따로 제어
                -> 플레이가 끝났는지 알려주는 것이 없기 때문에 앞의 몽타주가 실행되지 않은 상태로 방패 몽타주 실행
                -> Sword쪽에 몽타주를 합쳐서 실행

                활 만들기 
                -> 활땡기는 부분은 에니메이션에서 제어 
                -> 어빌리티에서 Drawing을 바꾸고 테그 붙이는 방식으로 
                -> TagCount가 0|1의 값이 나오기때문에 이걸 Drawing으로 
                -> 어빌리티 태그가 안 븥음….
                ->Wait Gameplay Event로 기다리다  BP_LInk의 Completed에서 
                SendGameplayEvent to Actor를 이용해  ShootArrow발생 시키기 에니메이션은 실행됨
                    BUG)화살 발사
                    -> 트레이스 오버랩 위치로 안날아감
                    -> 발사부분의 포워드 벡터가 오너캐릭터… 
                    프로젝타일(메쉬)걸로 바꿔서 해결
            화살 발사를 통해 Bluprintonly에서 만든 기능구현 끝

## Additional Player  Features After Moving To CppAndUnrealBluePrintPortfolio
    :
	Character Mesh)
	젤다의 전설에서 사용하던 링크 모자 장착
	마스터 소드와 검집 에셋 사용
	피격시 색 붉게 변환

        Hud)
	AsyncTask 생성
	태그를 이용한 Run(달리기), Burrow(숨기)부여
	스태미너바 감소 구현 완료
	체력은 적 만들기 시작하면 확인

        Bow)
	카매라 락, 카메라 이동 구현
	레이케스트 2개 쏴서 거기로 날아 가도록 구현

        SwordJumpAtt)
	에님 인스턴스에 추가
	태그 붙임
	태그확인을 에니메이션 조건 안에서 하면 오류뜸 
	-> CPP에서 계속 확인해서 작동하도록 수정

        BowjumpAttack(BulletTime)
	테그로 붙여줘서 글로벌 타임 느리개 하기
	-> jump가 사라지면 원래대로 돌아오게끔
	점프공격 에임 오프셋 만들기
	-> 따로 에니메이션을 사용하지 않고, 블렌드 시켜서 사용

        Animation)
	렌드에님에 애딕티브 해서 떨어져도 걸음

        JustRush)
	키입력 2개 입력 받아야함
	-> 캐릭터가 이동 방향을 바로 처다보기 때문에 백 한개만
	조건을 찝었는대도 불구하고 점프
	-> triggered가 아닌 started로 변경해서 사용

                BUG)Animation
                    :
                        타겟락 상태에서 왼쪽으로 돌때 너무 크게 돌아서 상대를 보지 않음
                        -> 오른쪽 뒤, 왼쪽 앞(딱 이렇게 두개만)
                        : 오른쪽 뒤는 왼쪽을 바라보며, 왼쪽은 정면을 보지 않고 왼쪽을 보며
                        -> 걍 몽타주 실행 없이 사용

                BUG)점프 어택(블릿 타임)
                    :
                        -> 높이가 안정해 져 있기 떄문에, 높이에 맞춰서 구현 되게 끔
                        -> 채공 시간으로 해결
                        -> 이러면 공격하고 나서 후타를 못침
                        -> 체공 높이 구하는 쪽으로 

                BUG)‘Death’처리
                    :
                        -> AnyDamage에서 체크하는건 몽타주 실행이 안됨
                        -> 데미지를 어플리 해야 생기는데 Tick에서 콜리전을 꺼버리기 때문에 추가타를 넣을수 없음
                        -> Tick에서 체크 하는건 콜리전 끄는거 말곤 의미 없음
                        -> 위에서 기술했듯 콜리전을 꺼버리면 AnyDamage가 안되고 콜리전을 유지하면 원하는 타수 만큼의 딜이 들어가지 않음
                        -> 틱에서 ‘Do Once’를 사용해 테그 엑티브, 콜리전 끄기, 몽타주 플레이 순 실헹
                        -> 몽타주에서 디스트로이 액터 노티파이 실행
                        -> Link같은 경우엔 무기가 오너를 못찾아서 에러가 오지게 뜸
                        -> Link의 경우엔 무기나 이런것들 다 삭제까지 해야됨
                        -> 활쏘는 보코블린은 죽는 몽타주 실행중 활을 한번더 쏘는 타이밍이 있음
                        -> 화살 쏘는 부분을 Bool 값으로 제어해 죽었을때 추가 화살 발사를 막음

                BUG)공격중에 점프하는 것
                    :
                        점프 시키는걸 테그에서 함수로 불러서 IA에 트라이엑티베이트 시키기

## Monster
    :
	각 상황에 맞춰져 있는 몬스터 생성
	{ 1(나무 가지만), 2(활), 3(나무가지 + 방패), Boss }
	-> Boss의 경우 무기 부착까지 해둠

	비헤이비어트리, 블랙보드 생성
	베이스 보코블린생성
	몬스터 별 데이터테이블과 GE_SetStatus 생성

	BaseWeapon)
	Box콜리전 대신 트레이스로 교체
	-> 여러마리를 동시에 걸림 (한마리한태도 여러번)
	-> 싱글로 바꾸고 하나하나 태그를 줄 예정
	->  콜리전의 오브젝트 타입을 바꿔서 1번만 맞게 적용시킴
	-> 어플리 데미지와 이벤트 에님데미지를 이용함
	-> 커서 문제 해결(HitMontage)
	-> 맞춰서 몽타주 실행(at BaseChar)

	Death,Hit) 
	커서를 이용해서 피격 몽타주 실행
	동일한 커서를 이용해 사망 몽타주 실행
	-> 다시 일어나지 않기 위해 딜레이 이후 디스트로이 엑터 실행

	Monster Animation)
		몬스터의 메시에 맞는  ABP, BS생성 
		-> 일단 idle상태로 만들어둠
		-> 활의 경우 플레이어의 점프를 가정한 AO 추가 생성

	        Target Lock
                    : 
                        페링과 저스트 회피를 위한 타겟 리턴이 필요
                        -> 타겟 락 우선 구현
                        페리, 저스트러시 완료
                        -> 센드 이팩트로 리시브시 엑티베이트 어빌리티 사용
                        타겟락시 이동용 BlendSpace 만들기
                        -> 전후좌우 이동 구현
                        -> Manny의 스켈레탈은 링크만 사용하기 때문에 
                        이벤트 그레프 안에서 변수 구현
                        -> 카메라 Lock에 대한 변수도 받아와 AimBow 상태에서 
                        좌우 이동 구현
		-> 패링, 저스트 러시 구현 완료

	몬스터 여러가지 모션 구현)
		-> 피격, 스턴

	활쏘는 보코블린)
		-> 보코블린의 에니메이션은 재생 성공
		-> 활에서 오너 케스트가 안됨
		-> play Montage를 이용해 보코블린에서 재생 시킬 생각
		-> 방법은 아래 메모참조
		-> 방법이 다 안되서 결국 PlayAnimation으로 변경
		->  Link와 동일한 방법으로 스폰및 발사

## 포트폴리오를 마치며</br>
    :
	Cpp와 BluePrint를 이용해 전투 시스탬 구현까지 마무리 했기 때문에 AI를 비롯한 추가 기능은 최종본에서 구현
	FinalPortfolio에서 구현 해야 될 분이 아직 남아있음

	1. BehaviorTree
 	:
		Ai컨트롤러등 구현해 둘것은 구현 완료
		페트롤을 하다가 일정 거리 안에 플레이어가 진입하여 적 1명이 플레이어
		발견시 모든 적에게 Target을 줘서 한번에 Aggro끌기
		일정 거리 안에 있을 땐 공격 후 백스탭
	2. 파쿠르
        :
            벽에 스태미너를 사용해서 클라이밍 

	3. 모으기 공격
        :
            일정 스테미너 소비 부터 가능
            일정 스테미너 소비량 비례 공격력 상승

	3. 페러세일
        :
            스테미너 소비량 비례 천천히 낙하
            페러세일링이 아닌 상태에서는 높이가 높으면 비례해 체력 소비

	4. 멥 생성
	:
             화염 데미지랑 얼음데미지 받는 지형으로 설정해 생성
	     맵마다 텔래포트 가능하게 끔

	5. 활, 화살
        :
             화살 선택 기능 만들기
        
	6. 사운드
        :
             젤다 사운드 녹화해 적용가능한 부분들은 전부
