// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	float Health = 0.f;

	//Another multicast delegate so the documentation doesn't do a great job at describing what parameters are required here
	//since the "function signatures for these are only created at compile time through macros." as described in this post:
	//	https://community.gamedev.tv/t/onanydamagetaken-arguments/199646
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor
		, float Damage
		, const UDamageType* DamageType
		, class AController* InstigatedBy //forward declaring this so need the "class" keyword
		, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
