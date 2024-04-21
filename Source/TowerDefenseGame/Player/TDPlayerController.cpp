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

void ATDPlayerController::EnterConstructionMode()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!Subsystem->HasMappingContext(ConstructionMappingContext))
		{
			Subsystem->AddMappingContext(ConstructionMappingContext, 1);
		}
	}
}

void ATDPlayerController::ExitConstructionMode()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem->HasMappingContext(ConstructionMappingContext))
		{
			Subsystem->RemoveMappingContext(ConstructionMappingContext);
		}
	}
}
