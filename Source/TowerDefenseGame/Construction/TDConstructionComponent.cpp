// Copyright Danny Kay 2024


#include "TDConstructionComponent.h"
#include "EnhancedInputComponent.h"
#include "TowerDefenseGame/Util/TDBlueprintFunctionLibrary.h"

UTDConstructionComponent::UTDConstructionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDConstructionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(this))
	{
		EnhancedInputComponent->BindAction(ConfirmConstructionAction, ETriggerEvent::Triggered, this, &UTDConstructionComponent::ConfirmConstruction);
		EnhancedInputComponent->BindAction(CancelConstructionAction, ETriggerEvent::Started, this, &UTDConstructionComponent::CancelConstruction);
	}
}

void UTDConstructionComponent::ConfirmConstruction(const FInputActionValue& InputActionValue)
{
}

void UTDConstructionComponent::CancelConstruction(const FInputActionValue& InputActionValue)
{
}
