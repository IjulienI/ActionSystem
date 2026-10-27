// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "DecoratorAction.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)
class ACTIONSYSTEM_API UDecoratorAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	virtual void OnInit_Implementation(UObject* WorldContextObject) override;
	virtual void OnCancel_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	
	
protected:
	bool RunChild();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActionSystem")
	void OnChildFinished();
	
	bool HasChild() const { return Child != nullptr; }
	
	UPROPERTY(EditAnywhere, Instanced, Category = "Action", meta = (DisplayName = "Action"))
	TObjectPtr<UActionBase> Child;
	
private:
	UFUNCTION()
	void HandleChildFinished();

	void UnbindChild();
};
