// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Ai.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AGameMode_Ai::AGameMode_Ai()
{
}

AActor* AGameMode_Ai::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (_Actors.Num()==0)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			_Actors.Add(Actor);
		}		
	}
	if (_Actors.Num()>0)
	{
		return _Actors[FMath::RandRange(0, _Actors.Num() - 1)];
	}
	
	return nullptr;
}

void AGameMode_Ai::Logout(AController* Exiting)
{
	_Controllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AGameMode_Ai::BeginPlay()
{
	Super::BeginPlay();
}

	
