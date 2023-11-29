// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionSubsystem.h"

TStatId UCollisionSubsystem::GetStatId() const
{
	return GetStatID();
}


void UCollisionSubsystem::RegisterCollider(TObjectPtr<UCollisionComponent> Collider)
{
	if (!Colliders.Contains(Collider))
	{
		Colliders.Add(Collider);
	}
}

void UCollisionSubsystem::UnregisterCollider(TObjectPtr<UCollisionComponent> Collider)
{
	if (Colliders.Contains(Collider))
	{
		Colliders.Remove(Collider);
	}
}

bool UCollisionSubsystem::CheckCollision(TObjectPtr<UCollisionComponent> Collider)
{
	bool Colliding = false;
	for (const TObjectPtr<UCollisionComponent> OtherCollider : Colliders)
	{
		if (Collider == OtherCollider)
			continue;

		FVector ColliderASize = Collider->GetSize();
		FVector ColliderAPosition = Collider->GetPosition();

		FVector ColliderBSize = OtherCollider->GetSize();
		FVector ColliderBPosition = OtherCollider->GetPosition();

		if (ColliderAPosition.X + ColliderASize.X >= ColliderBPosition.X - ColliderBSize.X &&
			ColliderAPosition.X - ColliderASize.X < ColliderBPosition.X + ColliderBSize.X &&
			ColliderAPosition.Y + ColliderASize.Y >= ColliderBPosition.Y - ColliderBSize.Y &&
			ColliderAPosition.Y - ColliderASize.Y < ColliderBPosition.Y + ColliderBSize.Y &&
			ColliderAPosition.Z + ColliderASize.Z >= ColliderBPosition.Z - ColliderBSize.Z &&
			ColliderAPosition.Z - ColliderASize.Z < ColliderBPosition.Z + ColliderBSize.Z)
		{
			Collider->Collided(OtherCollider);
			Colliding = true;
		}
		else
		{
			Collider->StoppedColliding(OtherCollider);
		}
	}

	return Colliding;
}

void UCollisionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}