// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIClimbController.generated.h"

class UBehaviorTreeComponent;

UCLASS(Abstract)
class GROUP_13_API AAIClimbController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIClimbController();

protected:
	APawn* PossessPawn;
	FVector AiLocation;
	bool test;

	FVector MoveDesination;
	FVector LocalMove;
	TArray<FVector> CurrentPath;
	bool LocalPathFound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpiderNavigation> _SpiderNav;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<ASpiderNavigation> _SpiderNavRef;

	//UBlackboardComponent* _Blackboard;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBehaviorTreeComponent* GetBehaviourTree;
	
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void Move(FVector Destination);

	UFUNCTION()
	void UpdateRotation();

	UFUNCTION()
	void UpdateLocalMove();
};
