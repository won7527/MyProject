// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"

#pragma warning (disabe: 4458) //c4456 경고끄기
// Sets default values
ACodeTest::ACodeTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeTest::BeginPlay()
{
	Super::BeginPlay();

	//result = StringAppender(f_name, l_name);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *result);
	//
	//int32 checker = 3;
	//// 만일 checker에 들어있는 값이 짝수라면
	//if (checker % 2 == 0)
	//{
	//	// "even" 이라고 출력한다.
	//	UE_LOG(LogTemp, Warning, TEXT("even"))
	//}
	//// 그렇지 않고 checker에 들어있는 값이 홀수라면
	//else
	//{
	//	// "odd" 라고 출력한다
	//	UE_LOG(LogTemp, Warning, TEXT("odd"))
	//}
	// 
	/* 7단의 값 출력
	for (int32 i = 1; i < 10; i++)
	{
		int32 mult = 7 * i;
		UE_LOG(LogTemp, Warning, TEXT("7 * %d = %d\n"), i, mult);
	}*/
}


// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ACodeTest::StringAppender(FString f, FString l)
{
	return f + l;
}
// 코드를 추가한다.