// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#include "Actions/DoOnceAction.h"

UDoOnceAction::UDoOnceAction()
{
	Advanced.ActionName = TEXT("Do Once");
}

void UDoOnceAction::OnInit_Implementation(UObject* WorldContextObject)
{
	Super::OnInit_Implementation(WorldContextObject);
	bWasTriggered = false;
}

void UDoOnceAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	if (bWasTriggered)
	{
		Finish();
		return;
	}
	
	bWasTriggered = true;
	if (!RunChild())
	{
		Finish();
	}
}
