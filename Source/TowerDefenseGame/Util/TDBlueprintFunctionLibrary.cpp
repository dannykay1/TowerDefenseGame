// Copyright Danny Kay 2024


#include "TDBlueprintFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"

void UTDBlueprintFunctionLibrary::AddMappingContext(const APlayerController* PlayerController, const UInputMappingContext* InputMappingContext)
{
	if (PlayerController == nullptr || InputMappingContext == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
