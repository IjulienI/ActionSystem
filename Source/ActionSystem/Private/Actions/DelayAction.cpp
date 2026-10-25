// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/DelayAction.h"

void UDelayAction::Execute_Implementation()
{
	Super::Execute_Implementation();
	
	
	const UWorld* World = GetWorld();
	if (!World || Duration <= 0.0f)
	{
		Finish();
		return;
	}
	
	World->GetTimerManager().SetTimer(TimerHandle, this, &UDelayAction::OnEndTimer, Duration, false);
}

void UDelayAction::OnEndTimer()
{
	TimerHandle.Invalidate();
	Finish();
}

void UDelayAction::Destroy_Implementation()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}
	Super::Destroy_Implementation();
}