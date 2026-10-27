// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/RepeatAction.h"

URepeatAction::URepeatAction()
{
	Advanced.ActionName = TEXT("Repeat");
}

void URepeatAction::Execute_Implementation(AActor* InInstigator)
{
	Super::Execute_Implementation(InInstigator);
	
	ClearNextRun();
	CompletedRuns = 0;

	if (!RunChild())
	{
		Finish();
	}
}

void URepeatAction::OnCancel_Implementation()
{
	ClearNextRun();
	Super::OnCancel_Implementation();
}

void URepeatAction::OnDestroy_Implementation()
{
	ClearNextRun();
	Super::OnDestroy_Implementation();
}

void URepeatAction::OnChildFinished_Implementation()
{
	Super::OnChildFinished_Implementation();
	
	++CompletedRuns;

	if (Count > 0 && CompletedRuns >= Count)
	{
		Finish();
		return;
	}

	UWorld* World = GetWorld();
	if (!ensure(World))
	{
		Finish();
		return;
	}

	NextRunHandle = World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		NextRunHandle.Invalidate();
		if (!RunChild())
		{
			Finish();
		}
	}));
}

void URepeatAction::ClearNextRun()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(NextRunHandle);
	}
	NextRunHandle.Invalidate();
}