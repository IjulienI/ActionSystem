// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/ActionConditionBase.h"


bool UActionConditionBase::Evaluate(const UActionBase* Action) const
{
	return EvaluateCondition(Action) != bInvert;
}

bool UActionConditionBase::EvaluateCondition_Implementation(const UActionBase* Action) const
{
	return false;
}

UWorld* UActionConditionBase::GetWorld() const
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
