// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDBlueprintFunctionLibrary.generated.h"

class ATDPlayerPawn;
class ATDPlayerController;
class UEnhancedInputComponent;

UCLASS()
class TOWERDEFENSEGAME_API UTDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UEnhancedInputComponent* GetEnhancedInputComponent(const UObject* WorldObject);

	static ATDPlayerController* GetTDPlayerController(const UObject* WorldObject);
	static ATDPlayerPawn* GetTDPlayerPawn(const UObject* WorldObject);
	
	static bool PlayerLineTrace(const UObject* ContextObject, float TraceDistance, FHitResult& WorldObject);
};
