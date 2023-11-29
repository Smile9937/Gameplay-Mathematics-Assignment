// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ground.h"
#include "LevelSpawner.generated.h"

UCLASS()
class GAMEPLAY_MATHEMATICS_API ALevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Ground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GroundSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NoiseScale;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SpawnLevel();
};
