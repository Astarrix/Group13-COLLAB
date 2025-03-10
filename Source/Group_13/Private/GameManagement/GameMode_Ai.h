// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameMode_Ai.generated.h"

/**
 * 
 */
UCLASS()
class GROUP_13_API AGameMode_Ai : public AGameMode
{
	GENERATED_BODY()

public:
	AGameMode_Ai();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void Logout(AController* Exiting) override;

protected:
	TArray<TObjectPtr<AActor>> _Actors;

	UPROPERTY(VisibleAnywhere ,BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _Controllers;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _GamePawn;


	virtual void BeginPlay() override;
};
