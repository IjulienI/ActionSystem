// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionBase.h"

void UActionBase::Init_Implementation(UObject* WorldContextObject)
{
}

void UActionBase::Execute_Implementation(AActor* InInstigator)
{
	Instigator = InInstigator;
	
	if (!Advanced.bAutoInit)
	{
		UWorld* World = GetWorld();
		if (!ensure(World))
		{
			return;
		}
		
		Init(World);
	}
}

void UActionBase::Destroy_Implementation()
{
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
