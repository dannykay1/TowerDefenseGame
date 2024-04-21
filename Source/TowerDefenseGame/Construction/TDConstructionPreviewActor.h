// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDConstructionPreviewActor.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class TOWERDEFENSEGAME_API ATDConstructionPreviewActor : public AActor
{
	GENERATED_BODY()

public:
	ATDConstructionPreviewActor();
	virtual void Tick(float DeltaTime) override;

	void ConstructPreview(const FDataTableRowHandle InRowHandle);
	void Construct() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Construction")
	FDataTableRowHandle RowHandle;
};
