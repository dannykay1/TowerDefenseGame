// Copyright Danny Kay 2024


#include "TDWeaponActor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefenseGame/Player/TDPlayerPawn.h"


ATDWeaponActor::ATDWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MuzzleComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->SetupAttachment(GetRootComponent());
	MuzzleComponent->SetRelativeLocation(FVector::ForwardVector * 100.f);

	AmmoCount = MaxAmmoCount;
}

void ATDWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATDWeaponActor::Shoot);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ATDWeaponActor::Reload);
		}
	}
}

void ATDWeaponActor::Shoot(const FInputActionValue& InputActionValue)
{
	if (AmmoCount > 0)
	{
		AmmoCount -= 1;
	}
}

void ATDWeaponActor::Reload(const FInputActionValue& InputActionValue)
{
	AmmoCount = MaxAmmoCount;
}
