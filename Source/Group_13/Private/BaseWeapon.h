// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UArrowComponent;

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	int _magSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	float _ReloadSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	float _ProjectileSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStats")
	float _Damage;	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS()
class GROUP_13_API ABaseWeapon : public AActor
{
	GENERATED_BODY()	

public:	
	ABaseWeapon();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "WeaponStats")
	TObjectPtr<UStaticMeshComponent> _gunMesh;
	
	UPROPERTY(VisibleDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _firePoint;
	
	//to use later with game managers
	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;

protected:	
		
	virtual void BeginPlay() override;

	//created functions
	UFUNCTION()
	void Fire(); //this is hitscan	
};
