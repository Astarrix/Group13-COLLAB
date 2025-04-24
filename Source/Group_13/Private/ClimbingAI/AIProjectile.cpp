// Fill out your copyright notice in the Description page of Project Settings.


#include "AIProjectile.h"


// Sets default values
AAIProjectile::AAIProjectile()
{


}

void AAIProjectile::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		
	}
    
	Destroy();
}
