// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "Components/ArrowComponent.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
		
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeapon::Fire()
{
	// TODO: make hitscan function
	UWorld* const world = GetWorld();
	if(world == nullptr){return;}
	
	FHitResult hit(ForceInit);
	FVector start = _firePoint->GetComponentLocation();
	FVector end = start + _firePoint->GetForwardVector() * 1000;
	TArray<AActor*> ActorsToIgnore;
	
}
	


