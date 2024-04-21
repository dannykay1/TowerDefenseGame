// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDConstructionComponent.generated.h"

class ATDConstructionPreviewActor;
class UInputAction;
struct FInputActionValue;
class UStaticMesh;
class AActor;

USTRUCT(BlueprintType)
struct FConstructionData : public FTableRowBase
{
	GENERATED_BODY()

	FConstructionData()
	{
		DisplayName = FText();
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> PreviewMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ActorToSpawn;
};

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSEGAME_API UTDConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDConstructionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConfirmConstructionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CancelConstructionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ActionBarSlot1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ActionBarSlot2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ActionBarSlot3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Construction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> ConstructionDataTable;

	UPROPERTY(BlueprintReadOnly, Category = "Construction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ATDConstructionPreviewActor> PreviewActor;

	void ConfirmConstruction(const FInputActionValue& InputActionValue);
	void CancelConstruction(const FInputActionValue& InputActionValue);
	void ActivateSlot1(const FInputActionValue& InputActionValue);
	void ActivateSlot2(const FInputActionValue& InputActionValue);
	void ActivateSlot3(const FInputActionValue& InputActionValue);

	void ActivateSlot(const int32 SlotNumber);
};
