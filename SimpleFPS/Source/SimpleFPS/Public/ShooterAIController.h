// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFPS_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float deltaTime) override;
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 300.f;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* AIBehavior;

	AActor* playerPawn;
	
};
