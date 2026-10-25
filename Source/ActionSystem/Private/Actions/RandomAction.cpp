// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/RandomAction.h"

void URandomAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);

	const int32 RandomIndex = FMath::RandRange(0, Actions.Num() -1);
	const auto SelectedAction = Actions[RandomIndex];
	if (ensure(SelectedAction))
	{
		SelectedAction->Execute(Instigator);
	}
	Finish();
}
