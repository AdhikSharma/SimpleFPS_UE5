// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* pawnKilled)
{
	Super::PawnKilled(pawnKilled);

	APlayerController* playerController = Cast<APlayerController>(pawnKilled->GetController());

	if (playerController) 
	{
		EndGame(false);
	}

	for (AShooterAIController* controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI dead"));
		if (!controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool isPlayerWinner)
{
	for (AController* controller : TActorRange<AController>(GetWorld()))
	{
		bool isWinner = controller->IsPlayerController() == isPlayerWinner;
		controller->GameHasEnded(controller->GetPawn(), isWinner);
	} 
}
