// Fill out your copyright notice in the Description page of Project Settings.


#include "CDrone.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACDrone::ACDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ACDrone::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(InputMapping, 0);
	}
}

// Called every frame
void ACDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator target = FRotator::ZeroRotator;
	// target.Yaw = GetActorRotation().Yaw;
	
	//정상 각도가 되기 위해 계속 값을 조정함
	FRotator rotate = FMath::RInterpTo(GetActorRotation(), target, GetWorld()->DeltaTimeSeconds, 5);
	SetActorRotation(rotate);
}

// Called to bind functionality to input
void ACDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACDrone::Move);
		enhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACDrone::Rotate);
	}
}

void ACDrone::Move(const FInputActionValue& Value)
{
	FVector input = Value.Get<FVector>();
	FRotator yaw = FRotator(0, GetControlRotation().Yaw, 0);
	FVector moveVec = yaw.RotateVector(input);
	float delta = GetWorld()->DeltaTimeSeconds;

	AddActorWorldOffset(moveVec * MoveSpeed * delta);
	AddActorLocalRotation(FRotator(-moveVec.X * RotateSpeed * delta, 0, moveVec.Y * RotateSpeed * delta));
}

void ACDrone::Rotate(const FInputActionValue& Value)
{
	FVector2D rotateVec = Value.Get<FVector2D>();

	AddControllerPitchInput(-rotateVec.Y);
	AddControllerYawInput(rotateVec.X);
}