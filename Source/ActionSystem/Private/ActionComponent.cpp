// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "ActionComponent.h"
#include "ActionBase.h"


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

void UActionComponent::InitActions(const bool bAutoInit)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	for (UActionBase* Action : Actions)
	{
		if (!ensureMsgf(Action, TEXT("Current Action is nullptr"))) continue;
		
		if (bAutoInit && !Action->GetAutoInit()) continue;
		
		Action->Init(World);
	}
}

void UActionComponent::ExecuteActions()
{
	for (UActionBase* Action : Actions)
	{
		if (!ensureMsgf(Action, TEXT("Current Action is nullptr"))) continue;
		
		Action->Execute();
	}
}

void UActionComponent::DestroyActions()
{
	for (UActionBase* Action : Actions)
	{
		if (!ensureMsgf(Action, TEXT("Current Action is nullptr"))) continue;
		
		Action->Destroy();
	}
	Actions.Empty();
}
