// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	HudScreen = CreateWidget(this, HUDClass);

	if (HudScreen)
	{
		HudScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus,bIsWinner);
	
	HudScreen->RemoveFromViewport();

	if (bIsWinner) 
	{
		UUserWidget* winScreen = CreateWidget(this, WinScreenClass);

		if (winScreen)
		{
			winScreen->AddToViewport();
		}
	}
	else 
	{
		UUserWidget* loseScreen = CreateWidget(this, LoseScreenClass);

		if (loseScreen)
		{
			loseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);

}


