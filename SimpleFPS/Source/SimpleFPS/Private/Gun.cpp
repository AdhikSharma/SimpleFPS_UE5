// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void AGun::PullTrigger()
{
	//Spawn Particle
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult hitResult;
	FVector shotDirection;

	bool success = GunTrace(hitResult,shotDirection);

	if (success)
	{
		//DrawDebugPoint(GetWorld(), hitResult.Location,20,FColor::Red,true);

		if (ImpactFlash) 
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, hitResult.Location, shotDirection.Rotation(), true);
		}

		if (ImpactSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, hitResult.Location);
		}

		AActor* hitActor = hitResult.GetActor();
		
		if (hitActor)
		{
			FPointDamageEvent DamageEvent(DamageAmount, hitResult, shotDirection, nullptr);
			hitActor->TakeDamage(DamageAmount, DamageEvent, GetOwnerController(), this);
		}
		
	}

	//DrawDebugCamera(GetWorld(), location, rotation,90,2, FColor::Red,true);
	//DrawDebugPoint(GetWorld(),location,20,FColor::Red,true);


}

bool AGun::GunTrace(FHitResult& hitResult, FVector& shotDirection)
{
	AController* ownerController = GetOwnerController();
	if (ownerController == nullptr) return false;

	FVector location;
	FRotator rotation;

	ownerController->GetPlayerViewPoint(location, rotation);
	shotDirection = -rotation.Vector();

	FVector end = location + rotation.Vector() * MaxRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(hitResult, location, end, ECollisionChannel::ECC_GameTraceChannel1, params);
}

AController* AGun::GetOwnerController() const
{
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (Owner == nullptr)
	{
		return nullptr;
	}

	return ownerPawn->GetController();
	
}



