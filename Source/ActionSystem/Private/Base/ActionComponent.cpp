// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionComponent.h"

#include "ActionSystem.h"
#include "Base/CompositeAction.h"


UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitActions();
}

void UActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyActions();
	Super::EndPlay(EndPlayReason);
}

void UActionComponent::InitActions() const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	if (RootAction)
	{
		RootAction->Initialize(World);
		return;
	}
	UE_LOG(LogActionSystem, Warning, TEXT("ExecuteActions: no Root Action set on %s."), *GetNameSafe(GetOwner()));
}

void UActionComponent::ExecuteActions(AActor* InInstigator)
{
	if (bRunning)
	{
		switch (TriggerPolicy)
		{
		case EActionTriggerPolicy::Ignore:
			return;
		case EActionTriggerPolicy::Restart:
			if (RootAction)
			{
				RootAction->Cancel();
				RootAction->OnFinishDelegate.RemoveDynamic(this, &UActionComponent::OnRootActionFinished);
			}
			bRunning = false;
			StartRootAction(InInstigator);
			return;
		case EActionTriggerPolicy::Queue:
			PendingInstigators.Add(InInstigator);
			return;
		}
	}
	
	StartRootAction(InInstigator);
}

void UActionComponent::DestroyActions()
{
	PendingInstigators.Empty();
	bRunning = false;

	if (RootAction)
	{
		RootAction->OnFinishDelegate.RemoveDynamic(this, &UActionComponent::OnRootActionFinished);
		RootAction->Deinitialize();
	}
}

void UActionComponent::OnRootActionFinished()
{
	if (RootAction)
	{
		RootAction->OnFinishDelegate.RemoveDynamic(this, &UActionComponent::OnRootActionFinished);
	}
	bRunning = false;
	
	
	if (TriggerPolicy != EActionTriggerPolicy::Queue && PendingInstigators.IsEmpty())
	{
		return;
	}
	
	AActor* NextInstigator = PendingInstigators[0].Get();
	PendingInstigators.RemoveAt(0);
	
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this, NextInstigator]()
	{
		StartRootAction(NextInstigator);
	}));
}

void UActionComponent::StartRootAction(AActor* InInstigator)
{
	if (!RootAction)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("ExecuteActions: no Root Action set on %s."), *GetNameSafe(GetOwner()));
		return;
	}

	bRunning = true;
	RootAction->OnFinishDelegate.AddUniqueDynamic(this, &UActionComponent::OnRootActionFinished);
	RootAction->Execute(InInstigator);
}
