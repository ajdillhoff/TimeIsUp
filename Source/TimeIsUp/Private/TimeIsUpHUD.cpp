

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpHUD.h"
#include "TimeIsUpPlayerController.h"
#include "TimeIsUpPlayerState.h"
#include "TimeIsUpGameState.h"


ATimeIsUpHUD::ATimeIsUpHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UFont> ScoreFontOb(TEXT("/Game/UI/HUD/ScoreFont"));

	ScoreFont = ScoreFontOb.Object;
}

void ATimeIsUpHUD::DrawPlayerScore() {
	Canvas->SetDrawColor(FColor::White);
	const float TimerPosX = Canvas->ClipX - Canvas->OrgX + 20.f;
	const float TimerPosY = Canvas->OrgY;

	ATimeIsUpGameState* const CurrentGameState = Cast<ATimeIsUpGameState>(GetWorld()->GameState);

	if (CurrentGameState) {
		FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), ScoreFont, FColor::White);
		TextItem.EnableShadow(FLinearColor::Black);
		float TextScale = 0.57f;
		FString Text = "";

		ATimeIsUpPlayerController* PC = Cast<ATimeIsUpPlayerController>(PlayerOwner);
		if (PC) {
			ATimeIsUpPlayerState* CurrentPlayerState = Cast<ATimeIsUpPlayerState>(PC->PlayerState);
			int numPlayers = CurrentGameState->NumPlayers;

			for (int i = 0; i < numPlayers; i++) {
				Text = Text + "P" + FString::FromInt(i+1) + ": " + FString::FromInt(CurrentGameState->PlayerScores[i]) + " ";
			}

			TextItem.Text = FText::FromString(Text);
			Canvas->DrawItem(TextItem);
		}
	}
}

void ATimeIsUpHUD::DrawHUD() {
	Super::DrawHUD();
	DrawPlayerScore();
}


