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
	
	StartLocation = GetActorLocation();
	// UE_LOG(LogTemp, Warning, TEXT("X : %f -- Y : %f -- Z : %f"), currentLocation.X, currentLocation.Y, currentLocation.Z);
}

// Called every frame
void AMovingObstcle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveObstacle(DeltaTime);
}

void AMovingObstcle::MoveObstacle(float DeltaTime)
{
	if (ShouldObstacleMove())
	{
		FVector MoveDirection = ObstacleVelocity.GetSafeNormal(); // GetSafeNormal() 함수를 이용하여 안전한 방향 벡터를 구하고 이를 변수에 할당함.
		StartLocation = StartLocation + MoveDirection * DeltaTime;
		SetActorLocation(StartLocation);
		ObstacleVelocity = -ObstacleVelocity; // Velocity 값을 음수로 만들면 해당 방향은 기존과 반대가 됨
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (ObstacleVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

bool AMovingObstcle::ShouldObstacleMove() const
{
	return FVector::Dist(StartLocation,GetActorLocation()) > MaxDistance;
}

void AMovingObstcle::RotateObstacle(float DeltaTime)
{
	AddActorLocalRotation(AngularVelocity * DeltaTime);
}
