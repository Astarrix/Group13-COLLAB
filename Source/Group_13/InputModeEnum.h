#pragma once

#include "CoreMinimal.h"
#include "InputModeEnum.generated.h"

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	Game,
	GameAndUI,
	UI
};
