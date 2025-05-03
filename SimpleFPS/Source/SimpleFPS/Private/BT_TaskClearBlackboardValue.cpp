// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_TaskClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_TaskClearBlackboardValue::UBT_TaskClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBT_TaskClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
