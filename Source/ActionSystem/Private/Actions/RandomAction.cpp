// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/RandomAction.h"

void URandomAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	if (Actions.IsEmpty())
	{
		Finish();
		return;
	}

	const int32 RandomIndex = FMath::RandRange(0, Actions.Num() -1);
	SelectedAction = Actions[RandomIndex];
	if (ensure(SelectedAction))
	{
		SelectedAction->OnFinishDelegate.AddUniqueDynamic(this, &URandomAction::OnEndAction);
		SelectedAction->Execute(Instigator);
	}
}

void URandomAction::OnEndAction()
{
	if (SelectedAction)
	{
		SelectedAction->OnFinishDelegate.RemoveDynamic(this, &URandomAction::OnEndAction);
	}
	
	Finish();
}
