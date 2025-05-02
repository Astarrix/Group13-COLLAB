// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AAIMech;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, newHealth, float, maxHealth, float,
                                               change);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, causer);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GROUP_13_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AAIMech> _MechRef;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float _CurrentHealth;
	
	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnDamaged;
	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnDead;

	UFUNCTION()
	void CritDmg(AActor* DamagedActor, float Damage, float damageMultiplier , const class UDamageType* DamageType, class AController* instigator, AActor* DamageCauser);

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _MaxHealth;
	

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType*  DamageType, class AController* Instigator, AActor* DamageCauser);
};
