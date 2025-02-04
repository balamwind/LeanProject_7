// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CDrone.generated.h"

struct FInputActionValue;

UCLASS()
class PROJECT7_API ACDrone : public APawn
{
	GENERATED_BODY()

public:
	ACDrone();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class USphereComponent> Sphere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> Camera;

	//===Details===
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UInputMappingContext> InputMapping;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	UPROPERTY(EditAnywhere)
	float RotateSpeed;
	
};
