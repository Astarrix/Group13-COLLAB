// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"

#include "Components/SphereComponent.h"


// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
	_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));	
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

void ABaseAICharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor != nullptr && OtherActor != this)
	{
		//TODO: check if player
	}
	
	Super::NotifyActorBeginOverlap(OtherActor);
}

UBehaviorTree* ABaseAICharacter::GetBehaviourTree_Implementation()
{
	return _BehaviourTree;
}

void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

