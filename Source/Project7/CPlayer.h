// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class PROJECT7_API ACPlayer : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ACPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void AddGravity(float DeltaTime);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCapsuleComponent> Capsule;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Mesh;
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
	float MoveSpeed = 700;
	UPROPERTY(EditAnywhere)
	float GravityScale = 0.05f;
	UPROPERTY(EditAnywhere)
	float JumpScale = 5;

private:
	const FVector Gravity = FVector(0.0f, 0.0f, -980.0f);

	FVector GravityAccel;
	bool bJump;
};
