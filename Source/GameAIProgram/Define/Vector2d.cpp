#include "Vector2d.h"

namespace GameAI
{
	FVector2d::FVector2d()
	{
	}

	FVector2d::FVector2d(const UE::Math::TVector<double>& InValue)
	{
		*this = InValue; 
	}

	FVector2d::FVector2d(const UE::Math::TVector2<double>& InValue)
	{
		*this = InValue; 
	}

	FVector2d& FVector2d::operator=(const UE::Math::TVector<double>& InValue)
	{
		X = InValue.X;
		Y = InValue.Y;
		return *this;
	}

	FVector2d& FVector2d::operator=(const UE::Math::TVector2<double>& InValue)
	{
		X = InValue.X;
		Y = InValue.Y;
		return *this;
	}

	FVector2d::operator UE::Math::TVector<double>() const
	{
		return FVector(X, Y, 0.0f);
	}

	void FVector2d::Truncate(double InMax)
	{
		if (Length() > InMax)
		{
			this->Normalize();
			*this *= InMax;
		}
	}

	FVector2d FVector2d::Perp() const
	{
		FVector2d Result;
		Result.X = -Y;
		Result.Y = X;
		return Result;
	}

	void FVector2d::WrapAround(GameAI::FVector2d& InTargetPos, double InMaxX, double InMaxY)
	{
		if (InTargetPos.X > InMaxX)
			InTargetPos.X = 0;
		if (InTargetPos.X < 0)
			InTargetPos.X = InMaxX;
		
		if (InTargetPos.Y > InMaxY)
			InTargetPos.Y = 0;
		if (InTargetPos.Y < 0)
			InTargetPos.Y = InMaxY;
	}
}
