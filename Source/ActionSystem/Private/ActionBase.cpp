// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "ActionBase.h"

void UActionBase::Init_Implementation(UObject* WorldContextObject)
{
}

void UActionBase::Execute_Implementation()
{
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
