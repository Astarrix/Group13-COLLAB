
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"


UCLASS()
class GROUP_13_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int LeftBitShift(int data, int pos);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int RightBitShift(int data, int pos);
};