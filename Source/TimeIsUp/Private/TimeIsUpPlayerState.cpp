

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpPlayerState.h"
#include "TimeIsUpPlayerController.h"
#include "TimeIsUpGameState.h"


ATimeIsUpPlayerState::ATimeIsUpPlayerState(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerNumber = 0;
	NumRings = 0;
}

void ATimeIsUpPlayerState::Reset() {
	Super::Reset();

	SetPlayerNum(0);
	NumRings = 0;
}

void ATimeIsUpPlayerState::SetPlayerNum(int32 NewPlayerNumber) {
	PlayerNumber = NewPlayerNumber;
}

void ATimeIsUpPlayerState::ScoreRing() {
	NumRings++;
	ScorePoints();
}

int32 ATimeIsUpPlayerState::GetPlayerNum() const {
	return PlayerNumber;
}

int32 ATimeIsUpPlayerState::GetRingCount() const {
	return NumRings;
}

void ATimeIsUpPlayerState::InformAboutRing_Implementation(class ATimeIsUpPlayerState* PlayerState) {
	/* Search for the player */
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		ATimeIsUpPlayerController *TestPC = Cast<ATimeIsUpPlayerController>(*It);
		if (TestPC) {
			ULocalPlayer *LocalPlayer = Cast<ULocalPlayer>(TestPC->Player);
			TSharedPtr<FUniqueNetId> LocalID = LocalPlayer->GetUniqueNetId();
			if (LocalID.IsValid() && *LocalPlayer->GetUniqueNetId() == *PlayerState->UniqueId) {
				TestPC->OnRingGet();
			}
		}
	}
}

void ATimeIsUpPlayerState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATimeIsUpPlayerState, PlayerNumber);
	DOREPLIFETIME(ATimeIsUpPlayerState, NumRings);
}

/* Update the game state */
void ATimeIsUpPlayerState::ScorePoints() {
	ATimeIsUpGameState* const MyGameState = Cast<ATimeIsUpGameState>(GetWorld()->GameState);
	if (MyGameState && PlayerNumber >= 0) {
		if (PlayerNumber >= MyGameState->PlayerScores.Num()) {
			MyGameState->PlayerScores.AddZeroed(PlayerNumber - MyGameState->PlayerScores.Num() + 1);
		}

		MyGameState->PlayerScores[PlayerNumber]++;
	}

}
