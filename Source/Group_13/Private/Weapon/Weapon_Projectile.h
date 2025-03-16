// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Weapon_Projectile.generated.h"

class AProjectile;

UCLASS(Abstract)
class GROUP_13_API AWeapon_Projectile : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> _ProjectileClass;
};
