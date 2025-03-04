// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTast_EventFire.h"

#include "Pawnable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTast_EventFire::UBTTast_EventFire()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTast_EventFire,Key_Pawn), APawn::StaticClass());
}

void UBTTast_EventFire::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Pawn.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTTast_EventFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	UObject* pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPawnable::StaticClass()))
	{
		//IPawnable
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTast_EventFire::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
