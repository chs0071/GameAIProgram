#pragma once
#include "Vector2d.h"

namespace GameAI
{
	class FVector2d;

	class Matrix : public UE::Math::TMatrix<double>
	{
	public:
		Matrix();
		
		void Rotate(const FVector2d& InForwardVec, const FVector2d& InSideVec);
		void Translate(const FVector2d& InPos);
		FVector2d TransFromVector2D(const FVector2d& InPos);

		static FVector2d PointToWorldSpace(const FVector2d& InPoint,
		                                   const FVector2d& InObjectHeading,
		                                   const FVector2d& InObjectSide,
		                                   const FVector2d& InObjectPosition);

		static FVector2D PointToLocalSpace(const FVector2d& InPoint,
										   const FVector2d& InObjectHeading,
										   const FVector2d& InObjectSide,
										   const FVector2d& InObjectPosition);

		static FVector2D VectorToWorldSpace(const FVector2d& InPoint,
											const FVector2d& InObjectHeading,
											const FVector2d& InObjectSide);
	};
}
