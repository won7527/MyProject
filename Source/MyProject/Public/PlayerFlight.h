// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#Include "InputActionValue.h"
#include "PlayerFlight.generated.h"

UCLASS()
class MYPROJECT_API APlayerFlight : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerFlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	float moveSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* ia_horizontal;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* ia_vertical;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* ia_fire;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputMappingContext* imc_myMapping;

private:
	//UFUNCTION(BlueprintCallable)
	//void Horizontal(float value);

	UFUNCTION(BlueprintCallable)
	void Horizontal(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void Vertical(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
	void FireBullet();

	//UFUNCTION(BlueprintCallable)
	//void Vertical(float value);
	//UFUNCTION(BlueprintCallable)
	//void FireBullet();

	float h;
	float v;
	FVector direction;

};
