// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpGameMode.h"
#include "TimeIsUpPlayerController.h"
#include "TimeIsUpGameState.h"
#include "TimeIsUpPlayerState.h"
#include "TimeIsUpHUD.h"

ATimeIsUpGameMode::ATimeIsUpGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
  // Default Controller Class
  PlayerControllerClass = ATimeIsUpPlayerController::StaticClass();
	GameStateClass = ATimeIsUpGameState::StaticClass();
	PlayerStateClass = ATimeIsUpPlayerState::StaticClass();
	HUDClass = ATimeIsUpHUD::StaticClass();
  
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/Blueprints/MyCharacter.MyCharacter_C'"));
	if (PlayerPawnBPClass.Object != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Object;
	}

	NumPlayers = 0;
}

void ATimeIsUpGameMode::InitNewPlayer(AController* NewPlayer, const TSharedPtr<FUniqueNetId>& UniqueId, const FString& Options) {
	Super::InitNewPlayer(NewPlayer, UniqueId, Options);

	// assign a player number
	ATimeIsUpPlayerState* NewPlayerState = CastChecked<ATimeIsUpPlayerState>(NewPlayer->PlayerState);
	const int32 PlayerNum = NumPlayers;
	NewPlayerState->SetPlayerNum(NumPlayers);

	ATimeIsUpGameState* const MyGameState = CastChecked<ATimeIsUpGameState>(GameState);
	if (MyGameState) {
		if (PlayerNum >= MyGameState->PlayerScores.Num()) {
			MyGameState->NumPlayers++;
			MyGameState->PlayerScores.AddZeroed(PlayerNum - MyGameState->PlayerScores.Num() + 1);
		}
	}

	NumPlayers++;
}

void ATimeIsUpGameMode::InitGameState() {
	Super::InitGameState();

	ATimeIsUpGameState* const MyGameState = Cast<ATimeIsUpGameState>(GameState);
	if (MyGameState) {
		MyGameState->NumPlayers = NumPlayers;
	}
}

void ATimeIsUpGameMode::CoinGet(AController* Player) {
	ATimeIsUpPlayerState* PlayerState = Player ? Cast<ATimeIsUpPlayerState>(Player->PlayerState) : NULL;

	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, "COIN GET");

	if (Player) {
		PlayerState->ScoreRing();
		PlayerState->InformAboutRing(PlayerState);
	}
}

void ATimeIsUpGameMode::DefaultTimer() {
	Super::DefaultTimer();
}

void ATimeIsUpGameMode::HandleMatchHasStarted() {
	Super::HandleMatchHasStarted();
}
