// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetDistanceToTargetActor.h"

UBTService_GetDistanceToTargetActor::UBTService_GetDistanceToTargetActor()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;

	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, Key_Pawn), APawn::StaticClass());
	Key_TargetActor.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, Key_TargetActor), AActor::StaticClass());
	Key_Distance.AddFloatFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor,Key_Distance));
}

void UBTService_GetDistanceToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Pawn.ResolveSelectedKey(*BBAsset);
		Key_TargetActor.ResolveSelectedKey(*BBAsset);
		Key_Distance.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_GetDistanceToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
