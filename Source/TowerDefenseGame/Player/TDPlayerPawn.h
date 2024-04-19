﻿// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDPlayerPawn.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ATDPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
