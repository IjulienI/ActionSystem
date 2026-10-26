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
	virtual void OnInit_Implementation(UObject* WorldContextObject) override
	{
		Super::OnInit_Implementation(WorldContextObject);
		for (UActionBase* Action : Actions)
		{
			if (Action && Action->GetAutoInit())
			{
				Action->Initialize(WorldContextObject);
			}
		}
	}
	
	virtual void OnCancel_Implementation() override
	{
		for (UActionBase* Action : Actions)
		{
			if (Action)
			{
				Action->Cancel();
			}
		}
		
		Super::OnCancel_Implementation();
	}
	
	virtual void OnDestroy_Implementation() override
	{
		for (UActionBase* Action : Actions)
		{
			if (Action)
			{
				Action->Deinitialize();
			}
		}
		
		Super::OnDestroy_Implementation();
	}
	
protected:
	UPROPERTY(EditAnywhere, Instanced, Category = "Action")
	TArray<TObjectPtr<UActionBase>> Actions;
};
