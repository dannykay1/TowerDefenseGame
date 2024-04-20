// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDBlueprintFunctionLibrary.generated.h"

class APlayerController;
class UInputMappingContext;

UCLASS()
class TOWERDEFENSEGAME_API UTDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void AddMappingContext(const APlayerController* PlayerController, const UInputMappingContext* InputMappingContext);
};
