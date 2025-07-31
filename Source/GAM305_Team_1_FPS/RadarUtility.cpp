// RadarUtility.cpp
#include "RadarUtility.h"

FVector2D URadarUtility::CalculateRadarDotPosition(
	const FVector& PlayerLocation,
	const FRotator& PlayerRotation,
	const FVector& EnemyLocation,
	float RadarRange,
	const FVector2D& RenderTargetSize
)
{
	// Get horizontal 2D difference (X, Y only)
	FVector2D Delta = FVector2D(EnemyLocation - PlayerLocation);

	// Rotate relative to player's yaw
	float YawRad = FMath::DegreesToRadians(-PlayerRotation.Yaw);
	float Cos = FMath::Cos(YawRad);
	float Sin = FMath::Sin(YawRad);
	FVector2D RotatedDelta = FVector2D(
		Delta.X * Cos - Delta.Y * Sin,
		Delta.X * Sin + Delta.Y * Cos
	);

	// Normalize to [-1, 1] space based on radar range
	FVector2D Normalized = RotatedDelta / RadarRange;

	// Clamp to radar bounds
	Normalized.X = FMath::Clamp(Normalized.X, -1.f, 1.f);
	Normalized.Y = FMath::Clamp(Normalized.Y, -1.f, 1.f);

	// Convert to 0–1 UV space and then to render target space
	FVector2D UV = (Normalized * 0.5f) + FVector2D(0.5f, 0.5f);
	FVector2D Pixel = UV * RenderTargetSize;

	return Pixel;
}
