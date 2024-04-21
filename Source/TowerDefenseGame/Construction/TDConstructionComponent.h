// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDConstructionComponent.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSEGAME_API UTDConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDConstructionComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConfirmConstructionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CancelConstructionAction;
	
	void ConfirmConstruction(const FInputActionValue& InputActionValue);
	void CancelConstruction(const FInputActionValue& InputActionValue);
};
