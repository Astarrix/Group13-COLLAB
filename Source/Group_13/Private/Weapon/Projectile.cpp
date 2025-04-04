// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Collider);
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile::Handle_Hit);

	_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	_ProjectileMovement->UpdatedComponent = _Collider;
	_ProjectileMovement->bRotationFollowsVelocity = true;
	_ProjectileMovement->bShouldBounce = true;
}

void AProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
		if(OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
    	{
    		UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());
    
    		if(OtherComp->IsSimulatingPhysics())
    		{
    			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
    		}
    	}
    
    	Destroy();
}

