// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionBase.h"


void UActionBase::Initialize(UObject* WorldContextObject)
{
	if (bInitialized) return;
	
	bInitialized = true;
	OnInit(WorldContextObject);
}

void UActionBase::OnInit_Implementation(UObject* WorldContextObject)
{
}

void UActionBase::Deinitialize()
{
	if (!bInitialized) return;
	
	OnDestroy();
	bInitialized = false;
}

void UActionBase::OnDestroy_Implementation()
{
}

void UActionBase::Execute_Implementation(AActor* InInstigator)
{
	Instigator = InInstigator;
	
	if (!bInitialized)
	{
		if (UWorld* World = GetWorld())
		{
			Initialize(World);
		}
	}
}

UWorld* UActionBase::GetWorld() const
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}
	if (const auto* Outer = GetOuter())
	{
		return Outer->GetWorld();
	}
	return nullptr;
}

void UActionBase::Finish() const
{
	OnFinishDelegate.Broadcast();
}

AActor* UActionBase::ResolveTarget(const FActionTarget& Target) const
{
	switch (Target.Source)
	{
	case EActionTargetSource::Self:
		return GetTypedOuter<AActor>();
	case EActionTargetSource::Instigator:
		return Instigator;
	case EActionTargetSource::Reference:
		return Target.Reference;
	}
	return nullptr;
}
