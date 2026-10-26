// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/BranchAction.h"

#include "ActionSystem.h"
#include "Base/ActionConditionBase.h"

UBranchAction::UBranchAction()
{
	Advanced.ActionName = TEXT("Branch");
}

void UBranchAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	if (!Condition)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("Branch '%s' on %s has no condition and was skipped."), *Advanced.ActionName, *GetNameSafe(GetTypedOuter<AActor>()));
		Finish();
		return;
	}

	ChosenAction = Condition->Evaluate(this) ? OnTrue : OnFalse;

	if (!ChosenAction)
	{
		Finish();
		return;
	}

	ChosenAction->OnFinishDelegate.AddUniqueDynamic(this, &UBranchAction::OnChosenActionFinished);
	ChosenAction->Execute(Instigator);
}

void UBranchAction::OnInit_Implementation(UObject* WorldContextObject)
{
	Super::OnInit_Implementation(WorldContextObject);
	
	for (UActionBase* Output : { OnTrue.Get(), OnFalse.Get() })
	{
		if (Output && Output->GetAutoInit())
		{
			Output->Initialize(WorldContextObject);
		}
	}
}

void UBranchAction::OnDestroy_Implementation()
{
	for (UActionBase* Output : { OnTrue.Get(), OnFalse.Get() })
	{
		if (Output)
		{
			Output->Deinitialize();
		}
	}
	
	Super::OnDestroy_Implementation();
}

void UBranchAction::OnChosenActionFinished()
{
	if (ChosenAction)
	{
		ChosenAction->OnFinishDelegate.RemoveDynamic(this, &UBranchAction::OnChosenActionFinished);
		ChosenAction = nullptr;
	}
	
	Finish();
}
