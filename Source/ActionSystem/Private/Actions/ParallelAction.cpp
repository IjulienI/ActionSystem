// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/ParallelAction.h"

UParallelAction::UParallelAction()
{
	Advanced.ActionName = "Parallel";
}

void UParallelAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	RemainingActions = 0;
	for (TObjectPtr<UActionBase>& Action : Actions)
	{
		if (!ensure(Action)) continue;

		Action->OnFinishDelegate.AddUniqueDynamic(this, &UParallelAction::OnEndAction);
		++RemainingActions;
	}

	if (RemainingActions == 0)
	{
		Finish();
		return;
	}
	
	for (TObjectPtr<UActionBase>& Action : Actions)
	{
		if (Action)
		{
			Action->Execute(Instigator);
		}
	}
}

void UParallelAction::OnCancel_Implementation()
{
	for (TObjectPtr<UActionBase>& Action : Actions)
	{
		if (Action)
		{
			Action->OnFinishDelegate.RemoveDynamic(this, &UParallelAction::OnEndAction);
		}
	}
	
	Super::OnCancel_Implementation();
}

void UParallelAction::OnEndAction()
{
	if (--RemainingActions > 0)
	{
		return;
	}

	for (TObjectPtr<UActionBase>& Action : Actions)
	{
		if (Action)
		{
			Action->OnFinishDelegate.RemoveDynamic(this, &UParallelAction::OnEndAction);
		}
	}

	Finish();
}
