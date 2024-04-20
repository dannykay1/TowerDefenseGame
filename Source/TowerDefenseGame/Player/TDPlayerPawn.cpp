// Copyright Danny Kay 2024


#include "TDPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"


ATDPlayerPawn::ATDPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));
}

void ATDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATDPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATDPlayerPawn::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATDPlayerPawn::Look);
	}
}

void ATDPlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector MoveDirection = Value.Get<FVector>();

	AddMovementInput(GetActorForwardVector(), MoveDirection.X);
	AddMovementInput(GetActorRightVector(), MoveDirection.Y);
	AddMovementInput(GetActorUpVector(), MoveDirection.Z);
}

void ATDPlayerPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}