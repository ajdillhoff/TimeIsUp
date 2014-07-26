

#pragma once

#include "GameFramework/PlayerController.h"
#include "TimeIsUpPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TIMEISUP_API ATimeIsUpPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

  UPROPERTY(BlueprintReadWrite, CATEGORY=ControllerProperties)
	uint32 coinCount;
	
};
