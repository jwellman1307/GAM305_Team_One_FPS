#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindSmartPatrolPoint.generated.h"

UCLASS()
class GAM305_TEAM_1_FPS_API UBTTask_FindSmartPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindSmartPatrolPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector PatrolPointKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	float SearchRadius = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	float BiasAwayFromTargetDistance = 500.0f;
};
