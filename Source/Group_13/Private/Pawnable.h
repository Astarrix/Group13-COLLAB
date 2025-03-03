// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/Interface.h"
#include "Pawnable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPawnable : public UInterface
{
	GENERATED_BODY()
};

class GROUP_13_API IPawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBehaviorTree* GetBehaviourTree();
};
