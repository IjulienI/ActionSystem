// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "InstantAction.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)
class ACTIONSYSTEM_API UInstantAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	virtual void Execute_Implementation() override final
	{
		Super::Execute_Implementation();
		Run();
		Finish();
	}
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ActionSystem")
	void Run();
};

inline void UInstantAction::Run_Implementation()
{
	
}
