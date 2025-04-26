// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "AIProjectile.h"
#include "Slowable.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "HealthComp/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAIPawn::AAIPawn()
{
	//components
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	_Mesh->SetupAttachment(RootComponent);

	_StoppingDistance = CreateDefaultSubobject<USphereComponent>(TEXT("Stopping Distance"));
	_StoppingDistance->SetupAttachment(RootComponent);

	_ShootingDistance = CreateDefaultSubobject<USphereComponent>(TEXT("Shooting Range"));
	_ShootingDistance->SetupAttachment(RootComponent);
	_ShootingDistance->SetCollisionProfileName("Shooting Sphere Collision");
	_ShootingDistance->OnComponentBeginOverlap.AddUniqueDynamic(this,&AAIPawn::ShootingOverlap);
	//-_ShootingDistance->OnComponent

	//_SightRange = CreateDefaultSubobject<USphereComponent>(TEXT("Sight Range"));
	//_SightRange->SetupAttachment(RootComponent);

	_DecalLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Point Down"));
	_DecalLocation->SetupAttachment(RootComponent);

	_ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Faces Forward, Don't Rotate"));
	_ForwardArrow->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
}

void AAIPawn::BugSpawned_Implementation()
{
	//controlled in blueprint?
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	_Health->OnDamaged.AddUniqueDynamic(this,&AAIPawn::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AAIPawn::Handle_HealthDead);

	GetWorld()->GetTimerManager().SetTimer(DecalSpawnTimer, this, &AAIPawn::DropDecal, DecalDelay,true);
}

void AAIPawn::Shoot()
{
	//todo: debug this and test, remember that sight range is irrelevant shooting distance can do both :)

	//sets the params for the spawned projectile
	UWorld* const world = GetWorld();
	if(world == nullptr || _ProjectileClass == nullptr){ return;}


	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();

	//this code is taken (and tweaked) from the LineTraceWeapon that Josh? made, checks if the player is in front of the ai
	float TraceDistance = 500.0f;
	FVector Start = _ForwardArrow->GetComponentLocation();
	FVector ForwardVector = _ForwardArrow->GetForwardVector();
	FVector End = Start +(ForwardVector * TraceDistance);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add( this); // adds self because setting the trace to ignore itself does nothing apparently
		
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	//if(world->LineTraceSingleByChannel(HitResult, ForwardVector, End, ECC_Visibility, QueryParams))
	if(UKismetSystemLibrary::LineTraceSingle(world,Start,End,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResult,true, FLinearColor::Red,
		FLinearColor::Green, 5))
	{
		
		//UE_LOG(LogTemp,Warning, TEXT("shoot %s "), *HitResult.GetActor()->GetName());
		
		if(UKismetSystemLibrary::DoesImplementInterface(HitResult.GetActor(),USlowable::StaticClass()))
		{
			world->SpawnActor(_ProjectileClass, &_ForwardArrow->GetComponentTransform(), spawnParams);
		}				
	}
}

void AAIPawn::DropDecal()
{
	//spawns a blueprint attached decal based on timer
	UWorld* const world = GetWorld();
	if(world == nullptr || _BloodSplatter == nullptr){ return;}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	world->SpawnActor(_BloodSplatter, &_DecalLocation->GetComponentTransform(), spawnParams);
}

void AAIPawn::ShootingOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp,Display,TEXT(" shoot overlap "));	
	if(Other != nullptr && Other != this && OtherComp != nullptr)
	{
		//v  checks to see if what was overlapped was the player or now via player only interface :)
		if(UKismetSystemLibrary::DoesImplementInterface(Other,USlowable::StaticClass()))
		{
			UWorld* const world = GetWorld();
			world->GetTimerManager().SetTimer(ShootTimer,this, &AAIPawn::Shoot,_ShootDelay,true);
			//do a line trace to see if anything is blocking ais view of player, if not start shoot timer			
		}
	}
}

void AAIPawn::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp,Display,TEXT("dmg"));

}

void AAIPawn::Handle_HealthDead(AController* causer)
{
	OnPawnDead.Broadcast();
	Destroy();
}


