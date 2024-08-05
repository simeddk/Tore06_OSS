#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	NoTeam, Red, Blue
};

UCLASS()
class OSS_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool IsHostileTeam(ACPlayerState* OtherPS) { return Team != OtherPS->Team; }

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	ETeamType Team;

	UPROPERTY(BlueprintReadOnly, Replicated)
	float Death;
};
