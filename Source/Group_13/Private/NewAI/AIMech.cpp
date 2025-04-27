// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMech.h"

#include "MovieSceneSequenceID.h"
#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"


// Sets default values
AAIMech::AAIMech()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_WeakPoint = CreateDefaultSubobject<USphereComponent>(TEXT("WeakPoint"));
	_WeakPoint->SetupAttachment(_Mesh);

	_DetectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionRange"));
	_DetectionRange->SetupAttachment(_Root);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AAIMech::BeginPlay()
{
	Super::BeginPlay();
	
}
