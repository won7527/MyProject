// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeTest.generated.h"


UCLASS()
class MYPROJECT_API ACodeTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACodeTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString f_name = "a";
	FString l_name = "b";
	FString result;

	// 문자열 두개를 받아서 문자열 한개로 합쳐서 반환하는 함수를 만들고 싶다. 
	UFUNCTION(BlueprintCallable)
		FString StringAppender(FString f, FString s);

	UPROPERTY(EditAnywhere, Category = CodeVariable)
		TArray<int32> ages;

	UPROPERTY(EditAnywhere, Category = CodeVariable)
		TMap<FString, float> distances;


};
