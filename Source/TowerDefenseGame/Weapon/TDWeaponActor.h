// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Engine/StaticMeshActor.h"
#include "TDWeaponActor.generated.h"

class UArrowComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(ShowCategories=("Input"))
class TOWERDEFENSEGAME_API ATDWeaponActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATDWeaponActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> MuzzleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;

	int32 AmmoCount = 0;
	int32 MaxAmmoCount = 50;

	void Shoot(const FInputActionValue& InputActionValue);
	void Reload(const FInputActionValue& InputActionValue);
};
