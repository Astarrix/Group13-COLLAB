// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"


// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	
	
}

void ABaseAICharacter::Action_Started_Implementation()
{
	//IPawnable::Action_Started_Implementation();
}

void ABaseAICharacter::Action_Cancelled_Implementation()
{
	//IPawnable::Action_Cancelled_Implementation();
}

FGenericTeamId ABaseAICharacter::GetGenericTeamId() const
{
	return _TeamId;
}

UBehaviorTree* ABaseAICharacter::GetBehaviourTree_Implementation()
{
	return _BehaviourTree;
}

void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

