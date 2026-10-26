// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionBase.h"

#include "ActionSystem.h"
#include "Chaos/PBDSuspensionConstraintData.h"


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

bool UActionBase::ResolveTransform(const FActionTransform& InTransform, FTransform& OutTransform) const
{
	if (InTransform.Source == EActionTransformSource::Absolute)
	{
		OutTransform = InTransform.Transform;
		return true;
	}
	
	const AActor* Actor = nullptr;
	switch (InTransform.Source)
	{
	case EActionTransformSource::Self:
		Actor = GetTypedOuter<AActor>();
		break;
	case EActionTransformSource::Instigator:
		Actor = Instigator;
		break;
	case EActionTransformSource::Reference:
		Actor = InTransform.Reference;
		break;
	default:
		break;
	}
	
	if (!Actor)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("%s: transform source is invalid (no actor to read from) in %s") ,*GetClass()->GetName(), *GetNameSafe(GetTypedOuter<AActor>()));
		return false;
	}
	OutTransform = Actor->GetActorTransform();
	return true;
}
