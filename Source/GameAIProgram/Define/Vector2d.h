#pragma once

namespace GameAI
{
	class FVector2d : public ::FVector2d
	{
	public:
		FVector2d();
		FVector2d(const UE::Math::TVector<double>& InValue);
		FVector2d(const UE::Math::TVector2<double>& InValue);
		
		FVector2d& operator=(const UE::Math::TVector<double>& InValue);
		FVector2d& operator=(const UE::Math::TVector2<double>& InValue);

		void Truncate(double InMax);
		FVector2d Perp() const;
	};
}
