// Fill out your copyright notice in the Description page of Project Settings.


#include "AIProjectile.h"

#include "Slowable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAIProjectile::AAIProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	_Movement->UpdatedComponent = _Collider;
	_Movement->bRotationFollowsVelocity = true;
	_Movement->bShouldBounce = false;

	_Collider->OnComponentHit.AddUniqueDynamic(this, &AAIProjectile::Handle_Hit);
}

void AAIProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, USlowable::StaticClass()))
		{
			ISlowable::Execute_SlowTarget(OtherActor, _SlownessPerc);
		}
	}
    
	Destroy();
}
