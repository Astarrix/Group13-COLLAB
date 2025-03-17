// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Pawnable.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"


class UHealthComponent;
class USphereComponent;
class UBehaviorTree;

UCLASS(Abstract)
class GROUP_13_API ABaseAICharacter : public ACharacter, public IPawnable, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	
	ABaseAICharacter();

	virtual void Action_Started_Implementation() override;
	virtual void Action_Cancelled_Implementation() override;

	virtual UBehaviorTree* GetBehaviourTree_Implementation() override; 

	virtual void BeginPlay() override;

protected:

#pragma region components
	
	UPROPERTY(EditAnywhere)
	FGenericTeamId _TeamId;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviourTree;

#pragma endregion 
	
	virtual FGenericTeamId GetGenericTeamId() const override; //sets the team id so its not recognised as an enemy by other ai

	UFUNCTION()
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);
};
