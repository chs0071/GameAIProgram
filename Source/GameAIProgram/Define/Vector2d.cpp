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

	FVector2d::FVector2d(const FRotator& InValue)
	{
		*this = InValue.Vector();
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

	FVector2d::operator UE::Math::TRotator<double>() const
	{
		const FVector& ThisVector = *this;
		return ThisVector.Rotation();
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
		Result.X = Y;
		Result.Y = -X;
		return Result;
	}

	void FVector2d::WrapAround(GameAI::FVector2d& InTargetPos, double InMaxX, double InMaxY)
	{
		if (InTargetPos.X > InMaxX)
			InTargetPos.X = -InMaxX;
		if (InTargetPos.X < -InMaxX)
			InTargetPos.X = InMaxX;
		
		if (InTargetPos.Y > InMaxY)
			InTargetPos.Y = -InMaxY;
		if (InTargetPos.Y < -InMaxY)
			InTargetPos.Y = InMaxY;
	}

	UE::Math::TQuat<double> FVector2d::ToQuat(const FVector2d& InVector2d)
	{
		const UE::Math::TRotator<double>& ThisRotator = InVector2d;
		return FQuat::MakeFromRotator(ThisRotator);
	}
}
