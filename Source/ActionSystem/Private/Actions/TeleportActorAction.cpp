// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/TeleportActorAction.h"

void UTeleportActorAction::Run_Implementation()
{
	Super::Run_Implementation();
	
	AActor* Actor = ResolveTarget(Target);
	if (ensure(Actor))
	{
		Actor->SetActorLocation(Location);
	}
}
