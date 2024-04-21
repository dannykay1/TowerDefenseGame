// Copyright Danny Kay 2024


#include "TDConstructionPreviewActor.h"
#include "TDConstructionComponent.h"


ATDConstructionPreviewActor::ATDConstructionPreviewActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetMobility(EComponentMobility::Movable);
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

	if (const FConstructionData* Data = RowHandle.GetRow<FConstructionData>(""))
	{
		GetStaticMeshComponent()->SetStaticMesh(Data->PreviewMesh);
	}
}

void ATDConstructionPreviewActor::Construct() const
{
	if (const FConstructionData* Data = RowHandle.GetRow<FConstructionData>(""))
	{
		const FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
		GetWorld()->SpawnActor(Data->ActorToSpawn, &SpawnTransform);
	}
}
