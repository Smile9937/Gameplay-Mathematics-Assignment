// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "CollisionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAY_MATHEMATICS_API UCollisionSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UCollisionComponent>> Colliders;


public:
	virtual void Tick(float DeltaTime) override;

	void RegisterCollider(TObjectPtr<UCollisionComponent> Collider);
	void UnregisterCollider(TObjectPtr<UCollisionComponent> Collider);

	bool CheckCollision(TObjectPtr<UCollisionComponent> Collider);

	virtual TStatId GetStatId() const override;
};
