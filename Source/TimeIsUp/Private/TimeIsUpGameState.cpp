

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpGameState.h"


ATimeIsUpGameState::ATimeIsUpGameState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	NumPlayers = 0;
	RemainingTime = 0;
}

void ATimeIsUpGameState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATimeIsUpGameState, NumPlayers);
	DOREPLIFETIME(ATimeIsUpGameState, RemainingTime);
	DOREPLIFETIME(ATimeIsUpGameState, PlayerScores);
}