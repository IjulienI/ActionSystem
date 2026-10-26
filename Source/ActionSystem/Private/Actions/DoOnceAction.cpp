// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/DoOnceAction.h"

#include "ActionSystem.h"

UDoOnceAction::UDoOnceAction()
{
	Advanced.ActionName = TEXT("Do Once");
}

void UDoOnceAction::OnInit_Implementation(UObject* WorldContextObject)
{
	Super::OnInit_Implementation(WorldContextObject);
	bWasTriggered = false;

	if (Action && Action->GetAutoInit())
	{
		Action->Initialize(WorldContextObject);
	}
}

void UDoOnceAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);

	if (bWasTriggered)
	{
		Finish();
		return;
	}

	if (!Action)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("Do Once '%s' on %s has no action."), *Advanced.ActionName, *GetNameSafe(GetTypedOuter<AActor>()));
		Finish();
		return;
	}

	bWasTriggered = true;
	Action->OnFinishDelegate.AddUniqueDynamic(this, &UDoOnceAction::OnActionFinished);
	Action->Execute(InInstigator);
}

void UDoOnceAction::OnCancel_Implementation()
{
	if (Action)
	{
		Action->OnFinishDelegate.RemoveDynamic(this, &UDoOnceAction::OnActionFinished);
		Action->Cancel();
	}
	
	Super::OnCancel_Implementation();
}

void UDoOnceAction::OnDestroy_Implementation()
{
	if (Action)
	{
		Action->OnFinishDelegate.RemoveDynamic(this, &UDoOnceAction::OnActionFinished);
		Action->Deinitialize();
	}
	
	Super::OnDestroy_Implementation();
}

void UDoOnceAction::OnActionFinished()
{
	if (Action)
	{
		Action->OnFinishDelegate.RemoveDynamic(this, &UDoOnceAction::OnActionFinished);
	}
	
	Finish();
}
