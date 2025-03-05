// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetDistanceToTarget.generated.h"

UCLASS()
class GROUP_13_API UBTService_GetDistanceToTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_GetDistanceToTarget();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Pawn;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_TargetPos;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Distance;
};
