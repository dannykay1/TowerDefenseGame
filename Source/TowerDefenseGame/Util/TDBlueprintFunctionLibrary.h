// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDBlueprintFunctionLibrary.generated.h"

class UEnhancedInputComponent;

UCLASS()
class TOWERDEFENSEGAME_API UTDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UEnhancedInputComponent* GetEnhancedInputComponent(const UObject* ContextObject);
};
