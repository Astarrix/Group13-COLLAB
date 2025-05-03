// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{	
}

void UHealthComponent::CritDmg(AActor* DamagedActor, float Damage, float damageMultiplier,
	const UDamageType* DamageType, AController* instigator, AActor* DamageCauser)
{
	//called in mech to do crit attack
	float newDamage = Damage * damageMultiplier;
	DamageTaken(DamagedActor,newDamage, DamageType,instigator,DamageCauser);
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp,Warning,TEXT("damage %f"), Damage);
	const float change = FMath::Min(_CurrentHealth, Damage);
	_CurrentHealth -= change;
	OnDamaged.Broadcast(_CurrentHealth,_MaxHealth,change);
	if(_CurrentHealth <= 0.0f)
	{
		OnDead.Broadcast(Instigator);
	}
}



