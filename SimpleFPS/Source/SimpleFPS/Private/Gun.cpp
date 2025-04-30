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
	//UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	//Spawn Particle
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));

	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (Owner==nullptr) 
	{
		return;
	}

	AController* ownerController = ownerPawn->GetController();
	if (ownerController == nullptr)
	{
		return;
	}

	FVector location;
	FRotator rotation;

	ownerController->GetPlayerViewPoint(location,rotation);

	FVector end = location + rotation.Vector() * MaxRange;

	

	FHitResult hitResult;

	bool sucess = GetWorld()->LineTraceSingleByChannel(hitResult, location,end,ECollisionChannel::ECC_GameTraceChannel1,FCollisionQueryParams::DefaultQueryParam);

	if (sucess) 
	{
		//DrawDebugPoint(GetWorld(), hitResult.Location,20,FColor::Red,true);

		if (ImpactFlash) 
		{
			FVector shotDirection = -rotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, hitResult.Location, rotation, true);
			FPointDamageEvent DamageEvent(DamageAmount, hitResult, shotDirection,nullptr);
			AActor* hitActor = hitResult.GetActor();
			if (hitActor) 
			{
				hitActor->TakeDamage(DamageAmount, DamageEvent, ownerController, this);
			}
			
		}
		
	}

	//DrawDebugCamera(GetWorld(), location, rotation,90,2, FColor::Red,true);
	//DrawDebugPoint(GetWorld(),location,20,FColor::Red,true);


}



