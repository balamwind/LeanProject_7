// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

struct FInputActionValue;
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECT7_API ACPlayer : public APawn
{
	GENERATED_BODY()
	
public:
	ACPlayer(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void AddGravity(const float DeltaTime);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	//===Details===
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 700;

	UPROPERTY(EditAnywhere)
	float GravityScale = 0.05f;

	UPROPERTY(EditAnywhere)
	float JumpPower = 5;

private:
	const FVector Gravity = FVector(0.0f, 0.0f, -980.0f);

	FVector velocity;
};
