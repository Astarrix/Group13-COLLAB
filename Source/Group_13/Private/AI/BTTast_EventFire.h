// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTast_EventFire.generated.h"

UCLASS()
class GROUP_13_API UBTTast_EventFire : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTast_EventFire();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category= "Blackboard")
	FBlackboardKeySelector Key_Pawn;
};
