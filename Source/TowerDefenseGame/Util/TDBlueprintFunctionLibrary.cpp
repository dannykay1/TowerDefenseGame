// Copyright Danny Kay 2024


#include "TDBlueprintFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenseGame/Player/TDPlayerController.h"
#include "TowerDefenseGame/Player/TDPlayerPawn.h"
#include "TowerDefenseGame/Weapon/TDWeaponActor.h"

UEnhancedInputComponent* UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(const UObject* WorldObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldObject, 0))
	{
		return Cast<UEnhancedInputComponent>(PC->InputComponent);
	}

	return nullptr;
}

ATDPlayerController* UTDBlueprintFunctionLibrary::GetTDPlayerController(const UObject* WorldObject)
{
	return Cast<ATDPlayerController>(UGameplayStatics::GetPlayerController(WorldObject, 0));
}

ATDPlayerPawn* UTDBlueprintFunctionLibrary::GetTDPlayerPawn(const UObject* WorldObject)
{
	return Cast<ATDPlayerPawn>(UGameplayStatics::GetPlayerPawn(WorldObject, 0));
}

bool UTDBlueprintFunctionLibrary::PlayerLineTrace(const UObject* WorldObject, float TraceDistance, FHitResult& HitResult)
{
	if (const ATDPlayerPawn* PlayerPawn = GetTDPlayerPawn(WorldObject))
	{
		if (const UCameraComponent* CameraComponent = PlayerPawn->CameraComponent)
		{
			const FVector TraceStart = CameraComponent->GetComponentLocation();
			const FVector TraceEnd = TraceStart + CameraComponent->GetForwardVector() * TraceDistance;

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(PlayerPawn);
			QueryParams.AddIgnoredActor(PlayerPawn->WeaponActor);
			
			const bool Success = PlayerPawn->GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Camera, QueryParams);

			return Success && HitResult.GetActor() != nullptr;
		}
	}

	return false;
}
