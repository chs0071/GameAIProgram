#pragma once

namespace GameAI
{
	class FVector2d : public ::FVector2d
	{
	public:
		FVector2d();
		FVector2d(const UE::Math::TVector<double>& InValue);
		FVector2d(const UE::Math::TVector2<double>& InValue);
		FVector2d(const FRotator& InValue);
		
		FVector2d& operator=(const UE::Math::TVector<double>& InValue);
		FVector2d& operator=(const UE::Math::TVector2<double>& InValue);

		operator FVector() const;
		operator FRotator() const;
		
		void Truncate(double InMax);
		FVector2d Perp() const;

		static void WrapAround(GameAI::FVector2d& InTargetPos, double InMaxX, double InMaxY);
	};
}
