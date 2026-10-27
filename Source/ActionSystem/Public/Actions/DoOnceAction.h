// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/DecoratorAction.h"
#include "DoOnceAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API UDoOnceAction : public UDecoratorAction
{
	GENERATED_BODY()
	
public:
	UDoOnceAction();
	virtual void Execute_Implementation(AActor* InInstigator) override;

	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void Reset() { bWasTriggered = false; }
	
protected:
	virtual void OnInit_Implementation(UObject* WorldContextObject) override;
	
private:
	bool bWasTriggered = false;
};
