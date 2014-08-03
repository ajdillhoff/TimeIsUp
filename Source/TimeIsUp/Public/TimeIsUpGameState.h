

#pragma once

#include "GameFramework/GameState.h"
#include "TimeIsUpGameState.generated.h"

/**
 * 
 */
UCLASS()
class TIMEISUP_API ATimeIsUpGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

	/* Number of players */
	UPROPERTY(Transient, Replicated)
	int32 NumPlayers;

	/* Scores per round */
	UPROPERTY(Transient, Replicated)
	TArray<int32> PlayerScores;

	/* Time left in current round */
	UPROPERTY(Transient, Replicated)
	int32 RemainingTime;
	
};
