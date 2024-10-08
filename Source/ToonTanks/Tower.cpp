// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }

}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    //using the "." operator because GetWorldTimerManager() returns an object, not a pointer -- bhd
    GetWorldTimerManager().SetTimer(
        FirerateTimerHandle
        , this
        , &ATower::CheckFireCondition
        , FireRate
        , true
    );
}

void ATower::CheckFireCondition()
{
    if (InFireRange())
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        FVector TankLocation = Tank->GetActorLocation();
        float DistanceToTank = FVector::Dist(GetActorLocation(), TankLocation);
        
        //Check to see if the tank is in range
        if (DistanceToTank <= FireRange) 
        {
            return true;
        }
    }
    return false;
}