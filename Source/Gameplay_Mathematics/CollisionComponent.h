// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "CollisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAY_MATHEMATICS_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ColliderSize;

	UPROPERTY()
	TArray<TObjectPtr<UCollisionComponent>> CollidingObjects;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool CollidingFromLeft(FVector OtherPosition, FVector OtherSize);
	bool CollidingFromRight(FVector OtherPosition, FVector OtherSize);
	bool CollidingFromFront(FVector OtherPosition, FVector OtherSize);
	bool CollidingFromBack(FVector OtherPosition, FVector OtherSize);
	bool CollidingFromTop(FVector OtherPosition, FVector OtherSize);
	bool CollidingFromBottom(FVector OtherPosition, FVector OtherSize);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSize(FVector Size);
	FVector GetSize();

	FVector GetPosition();
	void SetOldPosition();
	FVector OldPosition;

	void Collided(TObjectPtr<UCollisionComponent> Other);
	void StoppedColliding(TObjectPtr<UCollisionComponent> Other);

	bool GetIsColliding();

	FVector GetCollisionDirection();

	FVector ClampToCollision(FVector Vector);

	bool CollidingFromTop();
};
