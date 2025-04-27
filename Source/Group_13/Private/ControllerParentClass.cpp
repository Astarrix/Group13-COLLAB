// Fill out your copyright notice in the Description page of Project Settings.


#include "Group_13/Public/ControllerParentClass.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AControllerParentClass::SetInputMode(EInputMode SelectedMode, UWidget* WidgetToFocus, EMouseLockMode MouseLockMode, bool HideMouseDuringCapture)
{
	CurrentInputMode = SelectedMode;
	switch (SelectedMode)
	{
	case EInputMode::Game:
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this, false);
		SetShowMouseCursor(false);
		break;
	case EInputMode::UI:
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, WidgetToFocus, MouseLockMode);
		SetShowMouseCursor(true);
		break;
	case EInputMode::GameAndUI:
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, WidgetToFocus, MouseLockMode, HideMouseDuringCapture);
		SetShowMouseCursor(true);
		break;
	}
}
