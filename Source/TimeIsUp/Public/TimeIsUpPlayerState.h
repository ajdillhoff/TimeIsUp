

#pragma once

#include "GameFramework/PlayerState.h"
#include "TimeIsUpPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TIMEISUP_API ATimeIsUpPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	/* clear player score */
	virtual void Reset() override;

	/* Set the player ID when updating */
	void SetPlayerNum(int32 NewPlayerNumber);

	/* Player got a ring */
	void ScoreRing();

	/* Get current player number */
	int32 GetPlayerNum() const;

	/* Get current score */
	int32 GetRingCount() const;

	/* Sends score update to clients */
	UFUNCTION(Reliable, Client)
	void InformAboutRing(class ATimeIsUpPlayerState* PlayerState);

protected:

	/* Current player number */
	UPROPERTY(Transient, Replicated)
	int32 PlayerNumber;

	/* Number of rings */
	UPROPERTY(Transient, Replicated)
	int32 NumRings;

	void ScorePoints();
};
