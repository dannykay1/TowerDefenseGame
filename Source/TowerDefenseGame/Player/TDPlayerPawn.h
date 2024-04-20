// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "TDPlayerPawn.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class TOWERDEFENSEGAME_API ATDPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ATDPlayerPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
