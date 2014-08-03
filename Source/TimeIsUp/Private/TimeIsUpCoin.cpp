

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpGameMode.h"
#include "TimeIsUpCoin.h"


ATimeIsUpCoin::ATimeIsUpCoin(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	TSubobjectPtr<USphereComponent> CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(15.4f);
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	bReplicates = true;
}

void ATimeIsUpCoin::BeginPlay() {
	Super::BeginPlay();

	ATimeIsUpGameMode* GameMode = GetWorld()->GetAuthGameMode<ATimeIsUpGameMode>();
	if (GameMode) {
		GameMode->LevelCoins.Add(this);
	}
}

void ATimeIsUpCoin::ReceiveActorBeginOverlap(class AActor* OtherActor) {
	Super::ReceiveActorBeginOverlap(OtherActor);
	PickupOnTouch(Cast<ATimeIsUpCharacter>(OtherActor));
}

bool ATimeIsUpCoin::CanBePickedUp(class ATimeIsUpCharacter* TestPawn) const {
	return TestPawn != NULL;
}

void ATimeIsUpCoin::GiveCoinTo(class ATimeIsUpCharacter *Pawn) {
	// PlayerState needs to know
	// GameState needs to know

	/* After the game started, TimeIsUpCoin could no longer reference the GameMode */
	AController* PC = Pawn->GetController();
	ATimeIsUpGameMode *Game = GetWorld()->GetAuthGameMode<ATimeIsUpGameMode>();
	if (Game) {
		Game->CoinGet(PC);
	}
}

void ATimeIsUpCoin::PickupOnTouch(class ATimeIsUpCharacter *Pawn) {
	if (Pawn) {
		if (CanBePickedUp(Pawn)) {
			GiveCoinTo(Pawn);
			PickedUpBy = Pawn;
		}
	}
}

void ATimeIsUpCoin::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATimeIsUpCoin, PickedUpBy);
}