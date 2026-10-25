// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionComponent.h"
#include "Base/CompositeAction.h"


UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	InitActions(true);
}

void UActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyActions();
	Super::EndPlay(EndPlayReason);
}

void UActionComponent::InitActions(const bool bAutoInit) const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	if (!ensureMsgf(RootAction, TEXT("Current Action is nullptr"))) return;
	
	RootAction->Init(World);
}

void UActionComponent::ExecuteActions() const
{
	if (!ensureMsgf(RootAction, TEXT("Current Action is nullptr"))) return;;
	
	RootAction->Execute();
}

void UActionComponent::DestroyActions() const
{
	if (!ensureMsgf(RootAction, TEXT("Current Action is nullptr"))) return;;
	
	RootAction->Destroy();
}
