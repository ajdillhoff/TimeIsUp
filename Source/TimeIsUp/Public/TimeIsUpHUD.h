

#pragma once

#include "GameFramework/HUD.h"
#include "TimeIsUpHUD.generated.h"

/**
 * 
 */
UCLASS()
class TIMEISUP_API ATimeIsUpHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void DrawHUD() override;

protected:

	UPROPERTY()
	UFont* ScoreFont;

	void DrawPlayerScore();
	
};
