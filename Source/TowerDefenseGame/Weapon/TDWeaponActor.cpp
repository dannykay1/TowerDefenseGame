// Copyright Danny Kay 2024


#include "TDWeaponActor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
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

		FHitResult HitResult;
		if (UTDBlueprintFunctionLibrary::PlayerLineTrace(this, 50000.f, HitResult))
		{
			APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
			UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), 10.f, HitResult.Normal, HitResult, Player->GetController(), Player, nullptr);
		}
	}
}

void ATDWeaponActor::Reload(const FInputActionValue& InputActionValue)
{
	AmmoCount = MaxAmmoCount;
	OnAmmoChanged.Broadcast(AmmoCount, MaxAmmoCount);
}

#pragma optimize("", on)
