

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpPlayerController.h"


ATimeIsUpPlayerController::ATimeIsUpPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	coinCount = 0;
}

void ATimeIsUpPlayerController::OnRingGet() {
	//throw std::logic_error("The method or operation is not implemented.");
	// Kind of useless at the moment until I figure out how this ties in with everything else
}


