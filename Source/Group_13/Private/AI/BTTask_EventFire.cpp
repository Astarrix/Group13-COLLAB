// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EventFire.h"

#include "Pawnable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_EventFire::UBTTask_EventFire()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_EventFire,Key_Pawn), APawn::StaticClass());
}

void UBTTask_EventFire::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Pawn.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTTask_EventFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPawnable::StaticClass()))
	{
		IPawnable::Execute_Action_Started(pawn);
		return EBTNodeResult::InProgress;
	}	
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_EventFire::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPawnable::StaticClass()))
	{
		IPawnable::Execute_Action_Cancelled(pawn);
	}	
	return Super::AbortTask(OwnerComp, NodeMemory);
}
