// Copyright Danny Kay 2024


#include "TDTurret.h"


ATDTurret::ATDTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDTurret::BeginPlay()
{
	Super::BeginPlay();
}

void ATDTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
