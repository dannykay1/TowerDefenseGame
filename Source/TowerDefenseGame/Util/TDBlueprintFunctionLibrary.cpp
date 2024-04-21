// Copyright Danny Kay 2024


#include "TDBlueprintFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

UEnhancedInputComponent* UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(const UObject* ContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(ContextObject, 0))
	{
		return Cast<UEnhancedInputComponent>(PC->InputComponent);
	}

	return nullptr;
}
