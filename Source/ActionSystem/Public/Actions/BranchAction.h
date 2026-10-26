// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActionBase.h"
#include "BranchAction.generated.h"

class UActionConditionBase;

UCLASS()
class ACTIONSYSTEM_API UBranchAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	UBranchAction();
	virtual void OnInit_Implementation(UObject* WorldContextObject) override;
	virtual void Execute_Implementation(AActor* InInstigator) override;
	virtual void OnCancel_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "ActionSystem", meta = (AllowPrivateAccess = true))
	TObjectPtr<UActionConditionBase> Condition;
	
	UPROPERTY(EditAnywhere, Category = "ActionSystem", meta = (AllowPrivateAccess = true, EditCondition = "Condition != nullptr"))
	TObjectPtr<UActionBase> OnTrue;
	
	UPROPERTY(EditAnywhere, Category = "ActionSystem", meta = (AllowPrivateAccess = true, EditCondition = "Condition != nullptr"))
	TObjectPtr<UActionBase> OnFalse;
	
	UPROPERTY(Transient)
	TObjectPtr<UActionBase> ChosenAction;

	UFUNCTION()
	void OnChosenActionFinished();
};
