// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/CompositeAction.h"
#include "ParallelAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API UParallelAction : public UCompositeAction
{
	GENERATED_BODY()
	
public:
	UParallelAction();
	virtual void Execute_Implementation(AActor* Instigator) override;

private:
	int32 RemainingActions = 0;

	UFUNCTION()
	void OnEndAction();
};
