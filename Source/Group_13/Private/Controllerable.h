// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Controllerable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UControllerable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GROUP_13_API IControllerable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SpawnPawn();
};
