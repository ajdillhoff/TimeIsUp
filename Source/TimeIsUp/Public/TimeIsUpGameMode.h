// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TimeIsUpCoin.h"
#include "TimeIsUpGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of TimeIsUpCharacter

UCLASS(config=Game)
class ATimeIsUpGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void InitNewPlayer(AController* NewPlayer, const TSharedPtr<FUniqueNetId>& UniqueId, const FString& Options) override;

	virtual void InitGameState() override;

	/* Notify when a player gets a coin */
	virtual void CoinGet(AController* Player);

	/* Update remaining time */
	virtual void DefaultTimer() override;

	/* Starts new match */
	virtual void HandleMatchHasStarted() override;

protected:
	int32 NumPlayers;

	int32 WinnerPlayer;

public:
	UPROPERTY()
	TArray<class ATimeIsUpCoin*> LevelCoins;
};
