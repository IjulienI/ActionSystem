// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/CompositeAction.h"
#include "SequentialAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API USequentialAction : public UCompositeAction
{
	GENERATED_BODY()
	
public:
	USequentialAction();
	virtual void Execute_Implementation(AActor* Instigator) override;
	
private:
	void ExecuteAction();
	
	UFUNCTION()
	void OnEndAction();
	
	int32 ActionIndex = INDEX_NONE;
};
