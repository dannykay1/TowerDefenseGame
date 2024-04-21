// Copyright Danny Kay 2024


#include "TDConstructionPreviewActor.h"
#include "TDConstructionComponent.h"
#include "TowerDefenseGame/Turret/TDTurret.h"


ATDConstructionPreviewActor::ATDConstructionPreviewActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(false);
}

void ATDConstructionPreviewActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATDConstructionPreviewActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDConstructionPreviewActor::ConstructPreview(const FDataTableRowHandle InRowHandle)
{
	RowHandle = InRowHandle;
}

void ATDConstructionPreviewActor::Construct() const
{
	if (const FConstructionData* Data = RowHandle.GetRow<FConstructionData>(""))
	{
		const FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
		GetWorld()->SpawnActor(Data->TurretClass, &SpawnTransform);
	}
}
