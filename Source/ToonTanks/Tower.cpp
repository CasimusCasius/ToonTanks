// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tank && CheckInRangeTo(Tank))
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
   
    
    
}

void ATower::CheckFireCondition()
{
    if (Tank && CheckInRangeTo(Tank))
    {
        Fire();
    }
}
bool ATower::CheckInRangeTo(AActor* Target) 
{
    if (!Target)return false;
    
    FVector TargetPos = Target->GetActorLocation();
    if (FireRange >= FVector::Dist(GetActorLocation(), TargetPos))
    {
        
        return true;
    }
    else
    {
        
        return false;
    }

}