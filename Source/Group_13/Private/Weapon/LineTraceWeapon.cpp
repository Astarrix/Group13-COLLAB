#include "Weapon/LineTraceWeapon.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

void ALineTraceWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire function called"));
	
	LineTraceFire();
}

void ALineTraceWeapon::LineTraceFire()
{
	Super::Fire();
	
	if (!GetWorld()) return;
    
	// Get the starting location from the muzzle (or the actor's location if no muzzle exists)
	FVector Start = _Muzzle ? _Muzzle->GetComponentLocation() : GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	float TraceDistance = 1000.0f;
	FVector End = Start + (ForwardVector * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
    
	// Perform the line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			UGameplayStatics::ApplyDamage(HitActor, 5.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}

	// Draw debug line
	FColor LineColor = HitResult.bBlockingHit ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 5.0f, 0, 2.0f);
}