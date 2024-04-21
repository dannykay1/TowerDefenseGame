// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTDInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class TOWERDEFENSEGAME_API ITDInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	bool CanInteract();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	FText GetDisplayText();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void Interact();
};
