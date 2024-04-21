// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInteractionComponent.generated.h"

class ITDInteractInterface;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoundInteractable, AActor*, Interactable);

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSEGAME_API UTDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<AActor> InteractableActor;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnFoundInteractable OnFoundInteractable;

	void Interact(const FInputActionValue& InputActionValue);
};
