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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChangedDelegate, int32, Ammo, int32, MaxAmmo);

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
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Ammo")
	FOnAmmoChangedDelegate OnAmmoChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 AmmoCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmoCount = 50;

	void Shoot(const FInputActionValue& InputActionValue);
	void Reload(const FInputActionValue& InputActionValue);
};
