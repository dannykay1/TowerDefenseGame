// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDTurret.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class TOWERDEFENSEGAME_API ATDTurret : public AActor
{
	GENERATED_BODY()

public:
	ATDTurret();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
