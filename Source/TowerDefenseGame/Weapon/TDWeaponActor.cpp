// Copyright Danny Kay 2024


#include "TDWeaponActor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefenseGame/Util/TDBlueprintFunctionLibrary.h"

#pragma optimize("", off)

ATDWeaponActor::ATDWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	GetStaticMeshComponent()->SetComponentTickEnabled(false);

	MuzzleComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->SetComponentTickEnabled(false);
	MuzzleComponent->SetupAttachment(GetRootComponent());
	MuzzleComponent->SetRelativeLocation(FVector::ForwardVector * 100.f);

	AmmoCount = MaxAmmoCount;
}

void ATDWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(this))
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATDWeaponActor::Shoot);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ATDWeaponActor::Reload);
	}
}

void ATDWeaponActor::Shoot(const FInputActionValue& InputActionValue)
{
	if (AmmoCount > 0)
	{
		AmmoCount -= 1;
		OnAmmoChanged.Broadcast(AmmoCount, MaxAmmoCount);
	}
}

void ATDWeaponActor::Reload(const FInputActionValue& InputActionValue)
{
	AmmoCount = MaxAmmoCount;
	OnAmmoChanged.Broadcast(AmmoCount, MaxAmmoCount);
}

#pragma optimize("", on)
