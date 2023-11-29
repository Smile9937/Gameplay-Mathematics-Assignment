// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAY_MATHEMATICS_API IPlayerInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FVector2D Vector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FVector2D Vector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Jump(const float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartJump();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopJump();
};
