// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

//DEBUG
//Actually is included by default so technically don't need it -- bhd
//#include "DrawDebugHelpers.h"

ATank::ATank() 
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm Component"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    Camera->SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //note the use of the "address of" operator here to pass the function in -- bhd
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //check if PlayerControllerRef is a valid pointer; returns true if not a NULL pointer -- bhd
    if (PlayerControllerRef)
    {
        //HitResult being passed by reference and populated kind of like an "out" param in C#
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );

        RotateTurret(HitResult.ImpactPoint);

        //DEBUG
        DrawDebugSphere(
            GetWorld(),
            HitResult.ImpactPoint //+ FVector(0.f, 0.f, 200.f)
            ,25.f
            ,12
            ,FColor::Red
            ,false
            ,-1.f
        );
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;

    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //X = Value * DeltaTime * Speed
    DeltaLocation.X = Value * Speed * DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Yaw = Value * DeltaTime * TurnRate;

    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
    AddActorLocalRotation(DeltaRotation, true);
}
