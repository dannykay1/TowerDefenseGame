// Copyright Danny Kay 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDEnemyCharacter.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ATDEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATDEnemyCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth;

	int32 Health;

	UFUNCTION()
	void OnTakePointDamageCallback(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
};
