// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionConditionBase.generated.h"

class UActionBase;

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced, CollapseCategories)
class ACTIONSYSTEM_API UActionConditionBase : public UObject
{
	GENERATED_BODY()
	
public:
	bool Evaluate(const UActionBase* Action) const;
	
	virtual UWorld* GetWorld() const override;
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ActionSystem")
	bool EvaluateCondition(const UActionBase* Action) const;
	
	UPROPERTY(EditAnywhere, Category = "Condition")
	bool bInvert = false;
};
