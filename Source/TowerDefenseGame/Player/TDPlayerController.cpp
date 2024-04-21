// Copyright Danny Kay 2024


#include "TDPlayerController.h"

#include "EnhancedInputSubsystems.h"

ATDPlayerController::ATDPlayerController()
{
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(CombatMappingContext, 0);
	}
}

void ATDPlayerController::ToggleConstructionMode() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem->HasMappingContext(ConstructionMappingContext))
		{
			Subsystem->RemoveMappingContext(ConstructionMappingContext);
		}
		else
		{
			Subsystem->AddMappingContext(ConstructionMappingContext, 1);
		}
	}
}
