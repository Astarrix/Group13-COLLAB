// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"


// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	
	
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

