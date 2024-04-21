// Copyright Danny Kay 2024


#include "TDPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenseGame/Weapon/TDWeaponActor.h"


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

	if (WeaponClass)
	{
		const FTransform SpawnTransform;
		
		WeaponActor = GetWorld()->SpawnActorDeferred<ATDWeaponActor>(WeaponClass, SpawnTransform, this, this);
		WeaponActor = Cast<ATDWeaponActor>(UGameplayStatics::FinishSpawningActor(WeaponActor, SpawnTransform));
		
		WeaponActor->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		WeaponActor->SetActorRelativeLocation(FVector(-20.f, 20.f, -20.f));
		WeaponActor->SetActorRelativeRotation(FRotator::ZeroRotator);
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
