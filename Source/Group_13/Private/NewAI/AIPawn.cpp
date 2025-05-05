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
	_ShootingDistance->OnComponentEndOverlap.AddUniqueDynamic(this, &AAIPawn::EndShootingOverlap);

	//_SightRange = CreateDefaultSubobject<USphereComponent>(TEXT("Sight Range"));
	//_SightRange->SetupAttachment(RootComponent);

	_DecalLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Point Down"));
	_DecalLocation->SetupAttachment(_Mesh);

	_ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Faces Forward, Don't Rotate"));
	_ForwardArrow->SetupAttachment(_Mesh);

	_FacePlayerArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Rotates Towards Player In Play"));
	_FacePlayerArrow->SetupAttachment(_Root);
	
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
	//sets the params for the spawned projectile
	UWorld* const world = GetWorld();
	if(world == nullptr || _ProjectileClass == nullptr){ return;}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();

	//this code is taken (and tweaked) from the LineTraceWeapon that Steve made, checks if the player is in front of the ai
	float TraceDistance = _ShootingDistance->GetScaledSphereRadius(); //1000.00f
	FVector Start = _FacePlayerArrow->GetComponentLocation(); //_ForwardArrow
	FVector ForwardVector = _FacePlayerArrow->GetForwardVector();
	FVector End = Start +(ForwardVector * TraceDistance);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add( this); // adds self because setting the trace to ignore itself does nothing apparently
		
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);	
	
	if(UKismetSystemLibrary::LineTraceSingle(world,Start,End,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResult,true, FLinearColor::Red,
		FLinearColor::Green, 5))
	{		
		//UE_LOG(LogTemp,Warning, TEXT("shoot %s "), *HitResult.GetActor()->GetName());
		
		//if player is infront then shoots
		if(UKismetSystemLibrary::DoesImplementInterface(HitResult.GetActor(),USlowable::StaticClass()))
		{				
			world->SpawnActor(_ProjectileClass, &_FacePlayerArrow->GetComponentTransform(), spawnParams);
		}				
	}
}

void AAIPawn::DropDecal()
{
	//spawns a blueprint attached decal based on timer
	UWorld* const world = GetWorld();
	if(world == nullptr || _GoopSplatter == nullptr){ return;}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	world->SpawnActor(_GoopSplatter, &_DecalLocation->GetComponentTransform(), spawnParams);
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
			
			FTimerDelegate RotationDelegate = FTimerDelegate::CreateUObject(this, &AAIPawn::ControlRotation,Other);
			
			//v is basically a tick to update mesh rotation
			world->GetTimerManager().SetTimer(RotatePawn,RotationDelegate,0.01f,true);
			world->GetTimerManager().SetTimer(ShootTimer,this, &AAIPawn::Shoot,_ShootDelay,true);						
		}
	}
}

void AAIPawn::EndShootingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UWorld* const world = GetWorld();
	//world->GetTimerManager().PauseTimer()
	world->GetTimerManager().PauseTimer(RotatePawn);
	//world->GetTimerManager().PauseTimer(ShootTimer);
}

void AAIPawn::PawnDead()
{
	OnPawnDead.Broadcast();
	//UE_LOG(LogTemp, Warning, TEXT("dead c++"));
	
	UWorld* const world = GetWorld();
	if(world == nullptr || _DeadGoopSplatter == nullptr){ return;}
	
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	world->SpawnActor(_DeadGoopSplatter, &_DecalLocation->GetComponentTransform(), spawnParams);

	Destroy();
}

void AAIPawn::ControlRotation_Implementation(AActor* Player)
{	//this barely works :( its rotation is being reset through the controller and that needs to be kept for wall climbing
	//FHitResult outHit;
	//_Mesh->SetWorldRotation(PlayerRotation,true, &outHit, ETeleportType::None);

	//_FacePlayerArrow->SetWorldRotation(Player->GetActorRotation());


	//dont remove this function this is now done in blueprint :)
}

void AAIPawn::Handle_HealthDead_Implementation(AController* causer)
{
	
}

void AAIPawn::Handle_HealthDamaged_Implementation(float current, float max, float change)
{
	
}


