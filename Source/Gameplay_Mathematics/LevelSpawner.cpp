// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnLevel();
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawner::SpawnLevel()
{
	for (int X = 0; X < Size.X; X++)
	{
		for (int Y = 0; Y < Size.Y; Y++)
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X + NoiseScale + 0.1f, Y + NoiseScale + 0.1f)) * ZScale;
			FVector SpawnPosition = GetActorLocation() + FVector(X * GroundSize.X, Y * GroundSize.Y, Z * GroundSize.Z);
			GetWorld()->SpawnActor<AActor>(Ground, SpawnPosition, GetActorRotation());
		}
	}
}

