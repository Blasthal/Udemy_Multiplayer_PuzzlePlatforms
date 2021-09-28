// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()


public:
	AMovingPlatform();


public:
	virtual void Tick(float DeltaSeconds) override;


private:
	// ˆÚ“®‘¬“x
	UPROPERTY(EditAnywhere)
	FVector MoveVector = FVector::ForwardVector * 100.0f;
};
