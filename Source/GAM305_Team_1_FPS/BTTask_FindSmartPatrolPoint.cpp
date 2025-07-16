#include "BTTask_FindSmartPatrolPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_FindSmartPatrolPoint::UBTTask_FindSmartPatrolPoint()
{
	NodeName = "Find Smart Patrol Point";
	bCreateNodeInstance = true;

	// Allow vector/object keys to be picked
	PatrolPointKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindSmartPatrolPoint, PatrolPointKey));
	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindSmartPatrolPoint, TargetActorKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_FindSmartPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn)
		return EBTNodeResult::Failed;

	FVector Origin = AIPawn->GetActorLocation();
	FVector SearchCenter = Origin;

	// If player target exists, bias patrol point away from them
	UObject* TargetObj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName);
	if (AActor* TargetActor = Cast<AActor>(TargetObj))
	{
		FVector ToTarget = TargetActor->GetActorLocation() - Origin;
		if (!ToTarget.IsNearlyZero())
		{
			FVector BiasDir = -ToTarget.GetSafeNormal();
			SearchCenter = Origin + BiasDir * BiasAwayFromTargetDistance;
		}
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn);
	if (!NavSys)
		return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	bool bFound = NavSys->GetRandomReachablePointInRadius(SearchCenter, SearchRadius, NavLocation);
	if (!bFound)
		return EBTNodeResult::Failed;

	// Set found patrol point in blackboard
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPointKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
