// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorAICharacter.h"

#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"


// Sets default values
AFloorAICharacter::AFloorAICharacter()
{
	_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AFloorAICharacter::Action_Started_Implementation()
{
	//IPawnable::Action_Started_Implementation();
}

void AFloorAICharacter::Action_Cancelled_Implementation()
{
	//IPawnable::Action_Cancelled_Implementation();
}
 
FGenericTeamId AFloorAICharacter::GetGenericTeamId() const
{
	return _TeamId;
}

void AFloorAICharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor != nullptr && OtherActor != this)
	{
		//TODO: check if player
	}
	
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AFloorAICharacter::Handle_HealthDead(AController* causer)
{
	UE_LOG(LogTemp,Display,TEXT("dead"));
	Destroy();
}

void AFloorAICharacter::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp,Display,TEXT("dmg"));
}

UBehaviorTree* AFloorAICharacter::GetBehaviourTree_Implementation()
{
	return _BehaviourTree;
}

void AFloorAICharacter::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDamaged.AddUniqueDynamic(this, &AFloorAICharacter::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AFloorAICharacter::Handle_HealthDead);
}

