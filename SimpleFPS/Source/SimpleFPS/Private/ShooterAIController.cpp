// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	
	////if line of sight -> move to. setfocus
	////else clear focus stop movement
	
	if (playerPawn == nullptr) return;

	bool sucess = LineOfSightTo(playerPawn);

	if (sucess) 
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), playerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), playerPawn->GetActorLocation());
	}else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}

}
