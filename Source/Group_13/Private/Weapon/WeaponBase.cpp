// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/ArrowComponent.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.0f;
	
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}

void AWeaponBase::StartFire()
{
	Fire();
	if(_FireDelay != 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this,&AWeaponBase::Fire, _FireDelay, true);
	}
}

void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}

void AWeaponBase::Fire()
{
	OnFire.Broadcast();
}


