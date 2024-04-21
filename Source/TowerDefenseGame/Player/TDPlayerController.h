// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class TOWERDEFENSEGAME_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDPlayerController();

	void EnterConstructionMode();
	void ExitConstructionMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> CombatMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> ConstructionMappingContext;
};
