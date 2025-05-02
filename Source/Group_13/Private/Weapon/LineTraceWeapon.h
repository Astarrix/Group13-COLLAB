#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "LineTraceWeapon.generated.h"

UCLASS()
class GROUP_13_API ALineTraceWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Override Fire() and expose it to Blueprints.
	virtual void Fire() override;

	// Custom function to perform a line trace.
	UFUNCTION(BlueprintCallable)
	void LineTraceFire();
};