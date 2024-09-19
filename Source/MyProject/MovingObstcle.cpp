// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstcle.h"

// Sets default values
AMovingObstcle::AMovingObstcle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingObstcle::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("X : %f -- Y : %f -- Z : %f"), currentLocation.X, currentLocation.Y, currentLocation.Z);
}

// Called every frame
void AMovingObstcle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation(); // 현재 위치 저장
	currentLocation.Z = currentLocation.Z + 1; // currentLocation의 Z값을 1씩 증가
	SetActorLocation(currentLocation); 
}
