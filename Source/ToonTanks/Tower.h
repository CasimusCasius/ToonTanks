// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireRange = 300.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireRate = 2.f;

	void CheckFireCondition();
	bool CheckInRangeTo(AActor* Target);

};
