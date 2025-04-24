// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

int UFunctionLibrary::LeftBitShift(int data, int pos)
{
	int shifted = (data << pos);
	return shifted;
}

int UFunctionLibrary::RightBitShift(int data, int pos)
{
	int shifted = (data >> pos);
	return shifted;
}

void UFunctionLibrary::GetActorAxis(AActor* actor, FVector& Position, FVector& Forward, FVector& Right, FVector& Up)
{
	Position = actor->GetActorLocation();
	Forward = actor->GetActorForwardVector();
	Right = actor->GetActorRightVector();
	Up = actor->GetActorUpVector();
}

