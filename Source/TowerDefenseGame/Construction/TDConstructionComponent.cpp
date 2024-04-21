// Copyright Danny Kay 2024


#include "TDConstructionComponent.h"
#include "EnhancedInputComponent.h"
#include "TDConstructionPreviewActor.h"
#include "TowerDefenseGame/Player/TDPlayerController.h"
#include "TowerDefenseGame/Util/TDBlueprintFunctionLibrary.h"

UTDConstructionComponent::UTDConstructionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDConstructionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputComponent* EnhancedInputComponent = UTDBlueprintFunctionLibrary::GetEnhancedInputComponent(this))
	{
		EnhancedInputComponent->BindAction(ConfirmConstructionAction, ETriggerEvent::Started, this, &UTDConstructionComponent::ConfirmConstruction);
		EnhancedInputComponent->BindAction(CancelConstructionAction, ETriggerEvent::Started, this, &UTDConstructionComponent::CancelConstruction);
		EnhancedInputComponent->BindAction(ActionBarSlot1Action, ETriggerEvent::Started, this, &UTDConstructionComponent::ActivateSlot1);
		EnhancedInputComponent->BindAction(ActionBarSlot2Action, ETriggerEvent::Started, this, &UTDConstructionComponent::ActivateSlot2);
		EnhancedInputComponent->BindAction(ActionBarSlot3Action, ETriggerEvent::Started, this, &UTDConstructionComponent::ActivateSlot3);
	}
}

void UTDConstructionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PreviewActor)
	{
		FHitResult HitResult;
		if (UTDBlueprintFunctionLibrary::PlayerLineTrace(this, 50000.f, HitResult))
		{
			PreviewActor->SetActorLocationAndRotation(HitResult.ImpactPoint, GetOwner()->GetActorRotation());
		}
	}
}

void UTDConstructionComponent::ConfirmConstruction(const FInputActionValue& InputActionValue)
{
	if (PreviewActor)
	{
		PreviewActor->Construct();

		PreviewActor->Destroy();

		if (ATDPlayerController* PlayerController = UTDBlueprintFunctionLibrary::GetTDPlayerController(this))
		{
			PlayerController->ExitConstructionMode();
		}
	}
}

void UTDConstructionComponent::CancelConstruction(const FInputActionValue& InputActionValue)
{
	if (PreviewActor)
	{
		PreviewActor->Destroy();

		if (ATDPlayerController* PlayerController = UTDBlueprintFunctionLibrary::GetTDPlayerController(this))
		{
			PlayerController->ExitConstructionMode();
		}
	}
}

void UTDConstructionComponent::ActivateSlot1(const FInputActionValue& InputActionValue)
{
	ActivateSlot(0);
}

void UTDConstructionComponent::ActivateSlot2(const FInputActionValue& InputActionValue)
{
	ActivateSlot(1);
}

void UTDConstructionComponent::ActivateSlot3(const FInputActionValue& InputActionValue)
{
	ActivateSlot(2);
}

void UTDConstructionComponent::ActivateSlot(const int32 SlotNumber)
{
	if (ConstructionDataTable == nullptr)
	{
		return;
	}

	const TArray<FName> RowNames = ConstructionDataTable->GetRowNames();
	if (!RowNames.IsValidIndex(SlotNumber))
	{
		return;
	}

	if (PreviewActor)
	{
		PreviewActor->Destroy();
	}

	PreviewActor = GetWorld()->SpawnActor<ATDConstructionPreviewActor>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());

	if (PreviewActor)
	{
		FDataTableRowHandle RowHandle;
		RowHandle.DataTable = ConstructionDataTable;
		RowHandle.RowName = RowNames[SlotNumber];
		PreviewActor->ConstructPreview(RowHandle);

		if (ATDPlayerController* PlayerController = UTDBlueprintFunctionLibrary::GetTDPlayerController(this))
		{
			PlayerController->EnterConstructionMode();
		}
	}
}
