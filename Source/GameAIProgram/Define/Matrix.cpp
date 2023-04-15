#include "Matrix.h"
#include "Define/Vector2d.h"

namespace GameAI
{
	Matrix::Matrix()
	{
		memcpy(&M, &Identity, sizeof(M));
	}

	void Matrix::Rotate(const FVector2d& InForwardVec, const FVector2d& InSideVec)
	{
		const auto& RotatedMatrix = FRotationMatrix::MakeFromXY(InForwardVec, InSideVec);
		FMatrix* Matrix = StaticCast<FMatrix*>(this);
		*Matrix *= RotatedMatrix;
	}

	void Matrix::Translate(const FVector2d& InPos)
	{
		const auto& TranslatedMatrix = FTranslationMatrix::Make(InPos);
		FMatrix* Matrix = StaticCast<FMatrix*>(this);
		*Matrix *= TranslatedMatrix;
	}

	FVector2d Matrix::TransFromVector2D(const FVector2d& InPos)
	{
		FVector2d Result;
		const double TempX = M[0][0] * InPos.X + M[1][0] * InPos.Y + M[3][0];
		const double TempY = M[0][1] * InPos.X + M[1][1] * InPos.Y + M[3][1];
		
		Result.X = TempX;
		Result.Y = TempY;
		return Result;
	}

	FVector2d Matrix::PointToWorldSpace(const FVector2d& InPoint, const FVector2d& InObjectHeading,
		const FVector2d& InObjectSide, const FVector2d& InObjectPosition)
	{
		GameAI::Matrix LocalMatrix;
		LocalMatrix.Rotate(InObjectHeading, InObjectSide);
		LocalMatrix.Translate(InObjectPosition);
		return LocalMatrix.TransFromVector2D(InPoint);
	}

	FVector2D Matrix::PointToLocalSpace(const FVector2d& InPoint, const FVector2d& InObjectHeading,
		const FVector2d& InObjectSide, const FVector2d& InObjectPosition)
	{
		GameAI::Matrix LocalMatrix;
		LocalMatrix.Rotate(InObjectHeading, InObjectSide);

		FVector2d LocalTranslatePosition;
		LocalTranslatePosition.X = -InObjectPosition.Dot(InObjectHeading);
		LocalTranslatePosition.Y = -InObjectPosition.Dot(InObjectSide);

		LocalMatrix.Translate(LocalTranslatePosition);
		
		return LocalMatrix.TransFromVector2D(InPoint); 
	}

	FVector2D Matrix::VectorToWorldSpace(const FVector2d& InPoint, const FVector2d& InObjectHeading, const FVector2d& InObjectSide)
	{
		GameAI::Matrix LocalMatrix;
		LocalMatrix.Rotate(InObjectHeading, InObjectSide);

		return LocalMatrix.TransFromVector2D(InPoint);
	}
}
