// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary.h"

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
