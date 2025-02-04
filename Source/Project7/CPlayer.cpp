// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ACPlayer::ACPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (auto* EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()))
			EnhancedInputSystem->AddMappingContext(InputMapping, 0);
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayer::Move);
		enhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayer::Rotate);
		enhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACPlayer::Jump);
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddGravity(DeltaTime);
}


void ACPlayer::Move(const FInputActionValue& Value)
{
	FVector input = Value.Get<FVector>();
	FRotator yaw = FRotator(0, Camera->GetComponentRotation().Yaw, 0);
	FVector moveVec = yaw.RotateVector(FVector(input.X, input.Y, 0));

	if (velocity != FVector::ZeroVector)
		moveVec *= 0.3f;

	AddActorWorldOffset(moveVec * MoveSpeed * GetWorld()->DeltaTimeSeconds);
}

void ACPlayer::Rotate(const FInputActionValue& Value)
{
	FVector2D rotateVec = Value.Get<FVector2D>();

	AddActorLocalRotation(FRotator(0, rotateVec.X, 0));
	SpringArm->AddLocalRotation(FRotator(rotateVec.Y, 0, 0));
}

void ACPlayer::Jump(const FInputActionValue& Value)
{
	bool input = Value.Get<bool>();
	if (input)
		velocity.Z = JumpPower;
}


void ACPlayer::AddGravity(float DeltaTime)
{
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this); // 자신을 무시

	AddActorLocalOffset(velocity, true);

	FHitResult hit;
	GetWorld()->SweepSingleByChannel(hit, GetActorLocation(), GetActorLocation(), FQuat::Identity,
	                                 ECC_Visibility, Capsule->GetCollisionShape(), collisionParams);

	velocity += Gravity * GravityScale * DeltaTime;
	if (hit.GetActor() != nullptr)
	{
		velocity = FVector::ZeroVector;
		SetActorLocation(hit.ImpactPoint + FVector(0, 0, Capsule->GetScaledCapsuleHalfHeight()));
	}
}
