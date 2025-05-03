// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AIBT not null!!"));
		RunBehaviorTree(AIBehavior);

		playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* controlledCharacter = Cast<AShooterCharacter>(GetPawn());

	if (controlledCharacter)
	{
		return controlledCharacter->IsDead();
	}

	return true;
}
