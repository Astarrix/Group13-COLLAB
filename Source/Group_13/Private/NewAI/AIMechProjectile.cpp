// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMechProjectile.h"

#include "Slowable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAIMechProjectile::AAIMechProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("AI Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AAIMechProjectile::Handle_Hit);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Collider);
	
	_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	_Movement->UpdatedComponent = _Collider;
	_Movement->bRotationFollowsVelocity = true;
	_Movement->bShouldBounce = false;
}

void AAIMechProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		//UE_LOG(LogTemp,Display,TEXT("hit "));	
		if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, USlowable::StaticClass()))
		{
			//UE_LOG(LogTemp,Display,TEXT("hit player"));	
			ISlowable::Execute_EndPlayerClimbing(OtherActor);
		}
	}
	Destroy();
}

