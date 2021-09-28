// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Engine.h"


AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}


void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// サーバーでの処理を複製する
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}


void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// サーバーでの処理のみ
	if (HasAuthority())
	{
		const FVector GlobalMoveDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		const FVector GlobalMoveVector = GlobalMoveDirection * MoveSpeed;
		const FVector GlobalMovedLocation = GlobalMoveVector * DeltaSeconds + GetActorLocation();

		const FVector GlobalTargetDirectionFromMoved = (GlobalTargetLocation - GlobalMovedLocation).GetSafeNormal();

		// 目標地点へ移動中
		const bool bIsMoveForwardToTarget = (0.0f < FVector::DotProduct(GlobalMoveDirection, GlobalTargetDirectionFromMoved));
		if (bIsMoveForwardToTarget)
		{
			SetActorLocation(GlobalMovedLocation);
		}
		// 目標地点を通り過ぎた
		else
		{
			SetActorLocation(GlobalTargetLocation);

			const FVector Temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Temp;
		}


		// デバッグ表示
		DrawDebugString(GetWorld(), GetActorLocation(), *(GetActorLocation().ToString()), nullptr, FColor::White, 0.0f);
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::White, *(GetActorLocation().ToString()));
	}
}
