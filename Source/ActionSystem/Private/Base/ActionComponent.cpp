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
	UE_LOG(LogActionSystem, Warning, TEXT("UActionComponent::InitActions failed : Root Action is nullptr in %s"), *GetOwner()->GetName());
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
			// TODO : Cancel logic
			return;
		case EActionTriggerPolicy::Queue:
			++QueueCounter;
			return;
		}
	}
	
	Instigator = InInstigator;
	
	if (RootAction)
	{
		bRunning = true;
		RootAction->OnFinishDelegate.AddUniqueDynamic(this, &UActionComponent::OnRootActionFinished);
		RootAction->Execute(Instigator);
		return;
	}
	UE_LOG(LogActionSystem, Warning, TEXT("UActionComponent::ExecuteActions failed : Root Action is nullptr in %s"), *GetOwner()->GetName());
}

void UActionComponent::DestroyActions() const
{
	if (!RootAction) return;
	
	RootAction->Deinitialize();
}

void UActionComponent::OnRootActionFinished()
{
	if (RootAction)
	{
		RootAction->OnFinishDelegate.RemoveDynamic(this, &UActionComponent::OnRootActionFinished);
		bRunning = false;
	}
	
	if (TriggerPolicy == EActionTriggerPolicy::Queue && QueueCounter > 0)
	{
		--QueueCounter;
		ExecuteActions(Instigator);
	}
}
