#include "WeaponBase.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

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
	if (_FireDelay != 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeaponBase::Fire, _FireDelay, true);
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

// This function returns the UStaticMesh held by the Mesh component so it can be used in Blueprints.
UStaticMesh* AWeaponBase::GetStaticMesh() const
{
	return _Mesh ? _Mesh->GetStaticMesh() : nullptr;
}
