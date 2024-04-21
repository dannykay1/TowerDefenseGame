// Copyright Danny Kay 2024


#include "TDInteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "TDInteractInterface.h"
#include "TowerDefenseGame/Util/TDBlueprintFunctionLibrary.h"

#pragma optimize("", off)

UTDInteractionComponent::UTDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	InteractableActor = nullptr;
}

void UTDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(this))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UTDInteractionComponent::Interact);
	}
}

void UTDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* PotentialActor = nullptr;

	FHitResult HitResult;
	if (UTDBlueprintFunctionLibrary::PlayerLineTrace(this, 20000.f, HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->Implements<UTDInteractInterface>())
		{
			ITDInteractInterface* Interface = Cast<ITDInteractInterface>(HitActor);
			if (Interface->Execute_CanInteract(HitActor))
			{
				PotentialActor = HitActor;
			}
		}
	}

	InteractableActor = PotentialActor;
	OnFoundInteractable.Broadcast(InteractableActor);
}

void UTDInteractionComponent::Interact(const FInputActionValue& InputActionValue)
{
	if (InteractableActor && InteractableActor->Implements<UTDInteractInterface>())
	{
		ITDInteractInterface* Interface = Cast<ITDInteractInterface>(InteractableActor);
		Interface->Execute_Interact(InteractableActor);
	}
}

#pragma optimize("", on)
