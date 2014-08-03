

#pragma once

#include "GameFramework/Actor.h"
#include "TimeIsUpCharacter.h"
#include "TimeIsUpCoin.generated.h"

/**
 *
 */
UCLASS()
class TIMEISUP_API ATimeIsUpCoin : public AActor {
	GENERATED_UCLASS_BODY()

	virtual void ReceiveActorBeginOverlap(class AActor* OtherActor) override;

	virtual bool CanBePickedUp(class ATimeIsUpCharacter* TestPawn) const;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(Transient, Replicated)
	ATimeIsUpCharacter* PickedUpBy;

	virtual void GiveCoinTo(class ATimeIsUpCharacter *Pawn);

	void PickupOnTouch(class ATimeIsUpCharacter *Pawn);

};
