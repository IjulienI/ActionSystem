// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/SequentialAction.h"

USequentialAction::USequentialAction()
{
	Advanced.ActionName = "Sequential";
}

void USequentialAction::Execute_Implementation()
{
	Super::Execute_Implementation();
	
	ActionIndex = 0;
	ExecuteAction();
}

void USequentialAction::ExecuteAction()
{
	while (Actions.IsValidIndex(ActionIndex) && !ensure(Actions[ActionIndex]))
	{
		++ActionIndex;
	}
	
	if (!Actions.IsValidIndex(ActionIndex))
	{
		ActionIndex = INDEX_NONE;
		Finish();
		return;
	}

	UActionBase* Action = Actions[ActionIndex];
	Action->OnFinishDelegate.AddUniqueDynamic(this, &USequentialAction::OnEndAction);
	Action->Execute();
}

void USequentialAction::OnEndAction()
{
	if (Actions.IsValidIndex(ActionIndex) && Actions[ActionIndex])
	{
		Actions[ActionIndex]->OnFinishDelegate.RemoveDynamic(this, &USequentialAction::OnEndAction);
	}

	++ActionIndex;
	ExecuteAction();
}
