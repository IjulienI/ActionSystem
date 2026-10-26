// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActionBase.h"
#include "DoOnceAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API UDoOnceAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	UDoOnceAction();
	virtual void Execute_Implementation(AActor* InInstigator) override;

	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void Reset() { bWasTriggered = false; }
	
protected:
	virtual void OnInit_Implementation(UObject* WorldContextObject) override;
	virtual void OnCancel_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UActionBase> Action;

	bool bWasTriggered = false;

	UFUNCTION()
	void OnActionFinished();
};
