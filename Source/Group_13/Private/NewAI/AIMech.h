// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPawn.h"
#include "GenericTeamAgentInterface.h"
#include "AIMech.generated.h"

class AAIMechProjectile;
struct FAIStimulus;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMechDeadSignature);

UCLASS(Abstract)
class GROUP_13_API AAIMech : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIMech();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other);

protected:

#pragma region Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AAIMechProjectile> _Projectile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _weakPointDmg;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _ShootDelay;
	FTimerHandle _ShootTimer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _TeamId;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _SkelMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _WeakPoint;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _DetectionRange;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _ForwardArrow;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> _AIPercepetion;
	TObjectPtr<UAISenseConfig_Sight> _AISenseSight;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<AActor> _PlayerRef;
	bool canSeePlayer = false;

	FTimerHandle RotateArrow;

#pragma endregion Components
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION()
	void ShootingOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndShootingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void WeakPointOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Rotates arrow to face player, done in blueprint
	UFUNCTION(BlueprintNativeEvent)
	void ControlArrowRotation();
	
	UFUNCTION()
	void Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus stimulus);	
	
	//health
	
	UFUNCTION(BlueprintNativeEvent)
	void Handle_HealthDamaged(float current, float max, float change);

	//If in blueprint add a destroy actor node :)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Handle_HealthDead(AController* causer);
};
