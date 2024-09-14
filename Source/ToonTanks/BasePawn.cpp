// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h" //Don't really need this though since already included in the inheritance chain further up -- bhd
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//CapsuleComp->SetupAttachment(RootComponent);
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation()
			, LookAtRotation
			, UGameplayStatics::GetWorldDeltaSeconds(this)
			, 25.f
		)
	);
}

void ABasePawn::Fire()
{
    //DEBUG
    // DrawDebugSphere(
    //     GetWorld()
    //     , ProjectileSpawnPoint->GetComponentLocation()
    //     //, GetComponentLocation(this->ProjectileSpawnPoint)
    //     , 25.f
    //     , 12
    //     , FColor::Red
    //     , false
    //     , 3.0f
    // );

	GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass
		, ProjectileSpawnPoint->GetComponentLocation() 
		, ProjectileSpawnPoint->GetComponentRotation()
	);
}