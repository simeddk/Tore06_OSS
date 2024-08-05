#include "CPlayerState.h"
#include "Net/UnrealNetwork.h"

void ACPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPlayerState, Team);
	DOREPLIFETIME(ACPlayerState, Death);
}