// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameFramework/PlayerController.h"
#include "Group_13/InputModeEnum.h"
#include "ControllerParentClass.generated.h"

/**
 * 
 */
UCLASS()
class GROUP_13_API AControllerParentClass : public APlayerController
{
	GENERATED_BODY()
	EInputMode CurrentInputMode = EInputMode::Game;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EInputMode GetInputMode() {return CurrentInputMode;}
	UFUNCTION(BlueprintCallable)
	void SetInputMode(EInputMode SelectedMode, UWidget* WidgetToFocus = nullptr, EMouseLockMode MouseLockMode = EMouseLockMode::DoNotLock, bool HideMouseDuringCapture = false);
};
