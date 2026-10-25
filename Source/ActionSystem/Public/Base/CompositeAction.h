// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "CompositeAction.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)
class ACTIONSYSTEM_API UCompositeAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	virtual void Init_Implementation(UObject* WorldContextObject) override
	{
		Super::Init_Implementation(WorldContextObject);
		for (UActionBase* Action : Actions)
		{
			if (!ensure(Action)) continue;
				
			Action->Init(WorldContextObject);
		}
	}
	
	virtual void Destroy_Implementation() override
	{
		for (UActionBase* Action : Actions)
		{
			if (!ensure(Action)) continue;
				
			Action->Destroy();
		}
		Actions.Empty();
		Super::Destroy_Implementation();
	}
	
protected:
	UPROPERTY(EditAnywhere, Instanced, Category = "Action")
	TArray<TObjectPtr<UActionBase>> Actions;
};
