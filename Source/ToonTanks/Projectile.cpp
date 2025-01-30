// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//ProjectileMesh->SetupAttachment(RootComponent);
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = 
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 1300.f;

	SmokeTrailParticlesComponent =
		CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoketrail Particles Component"));
	SmokeTrailParticlesComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
		this
		, LaunchSound
		, GetActorLocation());	
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, FVector NormalImpulse
		, const FHitResult& Hit
)
{
	//Only works when "Simulate Physics" is disabled, because that enables the use of Hit Events -- bhd
	//UE_LOG(LogTemp, Warning, TEXT("OnHit"));

	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	//Verify that the OtherActor is not null and that the other actor is not ourselves.
	//We also check to verify we're not damaging our owner
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass
			);

		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
			this
			, HitParticles
			, GetActorLocation()
			, GetActorRotation()
			);
		}
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
		this
		, HitSound
		, GetActorLocation());	
	}
	
	Destroy();	
}