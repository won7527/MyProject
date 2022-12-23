// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌 박스 컴포넌트를 생성한다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	// 생성된 충돌 박스 컴포넌트를 루트 컴포넌트로 설정한다.
	SetRootComponent(BoxComp);

	// 박스 콜리전의 크기를 가로 세로 높이 모두 50센티미터로 설정한다.
	BoxComp->SetBoxExtent(FVector(50.0f));

	// 박스 콜리전의 충돌 처리 프리셋을 'PlayerPreset'으로 설정한다.
	BoxComp->SetCollisionProfileName(TEXT("PlayerPreset"));

	// 메시 컴포넌트를 생성한다.
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	// 메시 컴포넌트를 루트 컴포넌트의 하위 개체로 등록한다.
	meshComp->SetupAttachment(RootComponent);

	// 메시 컴포넌트의 static mesh 항목에 큐브 파일을 할당한다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// 만일 큐브 파일을 로드하는데 성공했다면
	if (cubeMesh.Succeeded())
	{
		// 로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다.
		meshComp->SetStaticMesh(cubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 컨트롤러를 캐스팅한다.
	APlayerController* playerCon = Cast<APlayerController>(GetController());

	if (playerCon != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
			if (subsys != nullptr)
			{
				subsys->AddMappingContext(imc_myMapping, 0);
			}
	}

	
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 사용자가 입력한 방향대로 이동하고 싶다.
	// 벡터의 정규화
	direction.Normalize();

	// P = P0 + vt
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(dir);

}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* enhancedInputComponent= Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);


	// Horizontal Axis 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);
	// Vertical Axis 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);
	// FIre Action 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);
}

// 좌우 입력이 있을 때 실행될 함수
/*void APlayerFlight::Horizontal(float value)
{
	h = value;
	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}*/

void APlayerFlight::Horizontal(const FInputActionValue& value)
{
	h = value.Get<float>();
	direction.Y = h;
}

void APlayerFlight::Vertical(const FInputActionValue& value)
{
	v = value.Get<float>();
	direction.Z = v;
}
// 상하 입력이 있을 때 실행될 함수
/*id APlayerFlight::Vertical(float value)
{
	v = value;
	//UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
	direction.Z = v;
}*/

// 마우스 왼쪽 버튼을 눌렀을 때 실행될 함수
void APlayerFlight::FireBullet()
{
	// 총알을 생성한다.
	// 총알 블루프린트 변수
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;
	FRotator spawnRotation = FRotator(90.0f, 0, 0);
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);
}
