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

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
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
    //According to Stephen Ulibarri, Epic's best practices recommend always using curly braces
    //, even if the if body is a single line.  Also, makes it more explicit/descriptive
    if (Tank == nullptr)
    {
        return;
    }
    if (InFireRange() && Tank->bAlive)
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