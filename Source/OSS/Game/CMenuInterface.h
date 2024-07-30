#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CMenuInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class OSS_API ICMenuInterface
{
	GENERATED_BODY()

public:
	virtual void Host(FString InDesiredSessionName) = 0;
	virtual void Join(uint32 InIndex) = 0;
	virtual void OpenMainMenuLevel() = 0;
	virtual void StartFindSession() = 0;
};
