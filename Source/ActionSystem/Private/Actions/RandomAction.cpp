// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/RandomAction.h"

#include "ActionSystem.h"

void URandomAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	if (Actions.IsEmpty())
	{
		Finish();
		return;
	}
	
	SelectedAction = Actions[FMath::RandRange(0, Actions.Num() -1)];
	if (!SelectedAction)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("Random '%s' on %s picked an empty slot."), *Advanced.ActionName, *GetNameSafe(GetTypedOuter<AActor>()));
		Finish();
		return;
	}
	
	SelectedAction->OnFinishDelegate.AddUniqueDynamic(this, &URandomAction::OnEndAction);
	SelectedAction->Execute(Instigator);
}

void URandomAction::OnCancel_Implementation()
{
	if (SelectedAction)
	{
		SelectedAction->OnFinishDelegate.RemoveDynamic(this, &URandomAction::OnEndAction);
	}
	SelectedAction = nullptr;
	
	Super::OnCancel_Implementation();
}

void URandomAction::OnEndAction()
{
	if (SelectedAction)
	{
		SelectedAction->OnFinishDelegate.RemoveDynamic(this, &URandomAction::OnEndAction);
	}
	SelectedAction = nullptr;
	
	Finish();
}
