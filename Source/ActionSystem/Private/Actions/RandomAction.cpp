// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/RandomAction.h"

void URandomAction::Execute_Implementation()
{
	Super::Execute_Implementation();

	const int32 RandomIndex = FMath::RandRange(0, Actions.Num() -1);
	const auto SelectedAction = Actions[RandomIndex];
	if (ensure(SelectedAction))
	{
		SelectedAction->Execute();
	}
	Finish();
}
