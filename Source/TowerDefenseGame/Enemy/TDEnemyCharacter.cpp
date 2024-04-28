// Copyright Danny Kay 2024


#include "TDEnemyCharacter.h"

#pragma optimize("", off)

ATDEnemyCharacter::ATDEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = StartingHealth = 100;
}

void ATDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = StartingHealth;
	OnTakePointDamage.AddDynamic(this, &ATDEnemyCharacter::OnTakePointDamageCallback);
}

void ATDEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDEnemyCharacter::OnTakePointDamageCallback(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	Health -= FMath::RoundToInt32(Damage);
	if (Health <= 0)
	{
		Destroy();
	}
}

#pragma optimize("", on)