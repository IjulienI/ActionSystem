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

void UActionComponent::ExecuteActions(AActor* Instigator) const
{
	if (RootAction)
	{
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
