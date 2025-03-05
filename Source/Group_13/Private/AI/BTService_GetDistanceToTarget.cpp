// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetDistanceToTarget.h"

UBTService_GetDistanceToTarget::UBTService_GetDistanceToTarget()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
}

void UBTService_GetDistanceToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

void UBTService_GetDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
