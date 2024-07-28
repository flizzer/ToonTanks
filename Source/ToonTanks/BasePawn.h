// Fill out your copyright notice in the Description page of Project Settings.

//this is basically an "include" guard so that this header file is only included once in a particular file -- bhd
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	/*forward declaring this type to avoid the inclusion of the header file for it here in the .h file pursuant to best practices.  
	Only a pointer is needed here.  However, we do need to include it in the BasePawn.cpp file because we need the implementation details
	in order to use it. -- bhd
	*/
	UPROPERTY()
	class UCapsuleComponent* CapsuleComp; 

	UPROPERTY()
	UStaticMeshComponent* BaseMesh; 

	UPROPERTY()
	UStaticMeshComponent* TurretMesh;

	UPROPERTY()
	USceneComponent* ProjectileSpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
