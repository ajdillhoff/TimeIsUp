// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpGameMode.h"
#include "TimeIsUpPlayerController.h"

ATimeIsUpGameMode::ATimeIsUpGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
  // Default Controller Class
  PlayerControllerClass = ATimeIsUpPlayerController::StaticClass();
  
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/Blueprints/MyCharacter.MyCharacter_C'"));
	if (PlayerPawnBPClass.Object != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Object;
	}
}
