#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS(Abstract)
class GROUP_13_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	// Blueprint event for when the weapon fires
	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;

	// Functions to start and stop firing
	UFUNCTION(BlueprintCallable)
	void StartFire();
	UFUNCTION(BlueprintCallable)
	void StopFire();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	UStaticMesh* GetStaticMesh() const;

protected:
	// The root scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<USceneComponent> _Root;

	// The static mesh component that holds the UStaticMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<UStaticMeshComponent> _Mesh;

	// The arrow component for the muzzle
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<UArrowComponent> _Muzzle;

	// The delay between weapon fires
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	float _FireDelay;
	FTimerHandle _FireDelayTimer;

	// The function that handles the actual firing logic
	UFUNCTION()
	virtual void Fire();
};
