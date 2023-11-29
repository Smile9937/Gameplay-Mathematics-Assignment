// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"

// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	SetOldPosition();
	// ...
	
}


// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollisionComponent::SetSize(FVector Size)
{
	ColliderSize = Size;
}

FVector UCollisionComponent::GetSize()
{
	return ColliderSize;
}

FVector UCollisionComponent::GetPosition()
{
	return GetOwner()->GetActorLocation();
}

void UCollisionComponent::SetOldPosition()
{
	OldPosition = GetPosition();
}

void UCollisionComponent::Collided(TObjectPtr<UCollisionComponent> Other)
{
	if (!CollidingObjects.Contains(Other))
	{
		CollidingObjects.Add(Other);
	}
}

void UCollisionComponent::StoppedColliding(TObjectPtr<UCollisionComponent> Other)
{
	if (CollidingObjects.Contains(Other))
	{
		CollidingObjects.Remove(Other);
	}
}

bool UCollisionComponent::GetIsColliding()
{
	return CollidingObjects.Num() > 0;
}

FVector UCollisionComponent::GetCollisionDirection()
{
	FVector Direction;

	for (const auto Collider : CollidingObjects)
	{
		Direction += Collider->GetPosition() - GetPosition();
	}

	Direction.Normalize();

	return Direction;
}

FVector UCollisionComponent::ClampToCollision(FVector Vector)
{
	FVector Position = GetPosition();
	FVector Size = GetSize();

	bool CollidingX = false;
	bool CollidingY = false;
	bool CollidingZ = false;

	for (const TObjectPtr<UCollisionComponent> Collider : CollidingObjects)
	{
		const FVector OtherColliderPosition = Collider->GetPosition();
		const FVector OtherColliderSize = Collider->GetSize();

		if (CollidingFromFront(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.X < 0) { Vector.X = 0; }
			CollidingX = true;
		}

		if(CollidingFromBack(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.X > 0) { Vector.X = 0; }
			CollidingX = true;
		}

		if (CollidingFromRight(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.Y < 0) { Vector.Y = 0; }
			CollidingY = true;
		}

		if (CollidingFromLeft(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.Y > 0) { Vector.Y = 0; }
			CollidingY = true;
		}

		if (CollidingFromTop(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.Z < 0) { Vector.Z = 0; }
			CollidingZ = true;
		}

		if (CollidingFromBottom(OtherColliderPosition, OtherColliderSize))
		{
			if (Vector.Z > 0) { Vector.Z = 0; }
			CollidingZ = true;
		}
	}

	if(!CollidingX)
		OldPosition.X = GetPosition().X;
	if(!CollidingY)
		OldPosition.Y = GetPosition().Y;
	if(!CollidingZ)
		OldPosition.Z = GetPosition().Z;

	return Vector;
}

bool UCollisionComponent::CollidingFromTop()
{
	FVector Position = GetPosition();
	FVector Size = GetSize();

	bool TopCollision = false;

	for (const TObjectPtr<UCollisionComponent> Collider : CollidingObjects)
	{
		const FVector OtherColliderPosition = Collider->GetPosition();
		const FVector OtherColliderSize = Collider->GetSize();

		if (CollidingFromTop(OtherColliderPosition, OtherColliderSize))
		{
			TopCollision = true;
		}
	}

	return TopCollision;
}


bool UCollisionComponent::CollidingFromBack(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.X + ColliderSize.X < OtherPosition.X - OtherSize.X &&
		GetPosition().X + ColliderSize.X >= OtherPosition.X - OtherSize.X;
}

bool UCollisionComponent::CollidingFromFront(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.X - ColliderSize.X > OtherPosition.X + OtherSize.X &&
		GetPosition().X - ColliderSize.X <= OtherPosition.X + OtherSize.X;
}

bool UCollisionComponent::CollidingFromLeft(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.Y + ColliderSize.Y < OtherPosition.Y - OtherSize.Y &&
		GetPosition().Y + ColliderSize.Y >= OtherPosition.Y - OtherSize.Y;
}

bool UCollisionComponent::CollidingFromRight(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.Y - ColliderSize.Y > OtherPosition.Y + OtherSize.Y &&
		GetPosition().Y - ColliderSize.Y <= OtherPosition.Y + OtherSize.Y;
}

bool UCollisionComponent::CollidingFromBottom(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.Z + ColliderSize.Z < OtherPosition.Z - OtherSize.Z &&
		GetPosition().Z + ColliderSize.Z >= OtherPosition.Z - OtherSize.Z;
}

bool UCollisionComponent::CollidingFromTop(FVector OtherPosition, FVector OtherSize)
{
	return OldPosition.Z - ColliderSize.Z > OtherPosition.Z + OtherSize.Z &&
		GetPosition().Z - ColliderSize.Z <= OtherPosition.Z + OtherSize.Z;
}
