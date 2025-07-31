// RadarUtility.h
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RadarUtility.generated.h"

UCLASS()
class GAM305_TEAM_1_FPS_API URadarUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Returns 2D position of enemy on radar from player location/rotation
	UFUNCTION(BlueprintPure, Category = "Radar")
	static FVector2D CalculateRadarDotPosition(
		const FVector& PlayerLocation,
		const FRotator& PlayerRotation,
		const FVector& EnemyLocation,
		float RadarRange,
		const FVector2D& RenderTargetSize
	);
};
