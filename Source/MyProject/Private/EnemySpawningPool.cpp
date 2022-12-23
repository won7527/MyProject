// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningPool.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemySpawningPool::AEnemySpawningPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootscene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(rootscene);

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawningPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawningPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 경과된 시간을 누적시킨다.
	currentTime += DeltaTime;

	// 만일 누적된 시간이 spawnCool에 지정한 시간보다 크거나 같다면
	if (currentTime >= spawnCool)
	{
		// BP_Enemy를 생성한다.
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
		currentTime = 0;

	}

}

