// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputInterface.h"
#include "GameFramework/Pawn.h"
#include "CollisionSubsystem.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "CollisionComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEPLAY_MATHEMATICS_API APlayerCharacter : public APawn,
	public IPlayerInputInterface
{
	GENERATED_BODY()

	float CurrentLookRotation;
	FVector MoveVector;

	float JumpValue;
	bool Jumping;

	TObjectPtr<UCollisionSubsystem> Subsystem;

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCurveFloat> JumpCurve;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCollisionComponent> CollisionComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed = 100.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GravityScale = 1000.f;

	void Look(const FVector2D Vector);
	virtual void Look_Implementation(const FVector2D Vector) override;

	void Move(const FVector2D Vector);
	virtual void Move_Implementation(const FVector2D Vector) override;

	void Jump(const float Value);
	virtual void Jump_Implementation(const float Value) override;

	void StartJump();
	virtual void StartJump_Implementation() override;

	void StopJump();
	virtual void StopJump_Implementation() override;

	FVector GetSize();
	FVector GetPosition();
	//void Collided();

};
