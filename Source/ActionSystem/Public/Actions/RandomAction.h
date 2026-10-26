// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/CompositeAction.h"
#include "RandomAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONSYSTEM_API URandomAction : public UCompositeAction
{
	GENERATED_BODY()
	
public:
	virtual void Execute_Implementation(AActor* Instigator) override;
	
private:
	UFUNCTION()
	void OnEndAction();
	
	TObjectPtr<UActionBase> SelectedAction;
};
