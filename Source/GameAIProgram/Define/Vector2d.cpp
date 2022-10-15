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
}
