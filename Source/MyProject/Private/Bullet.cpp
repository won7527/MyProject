// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹 ���� ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collison"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));

	// �޽� ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ���� �������� ��� �̵��ϰ� �ʹ�.
	// direction = FVector(1, 0, 0);
	direction = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);

}

