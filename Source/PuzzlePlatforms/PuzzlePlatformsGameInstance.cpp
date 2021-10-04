// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructed"));
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init"));
}
