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
	URandomAction();
	virtual void Execute_Implementation(AActor* Instigator) override;
	virtual void OnCancel_Implementation() override;
	
private:
	UFUNCTION()
	void OnEndAction();
	
	UPROPERTY(Transient)
	TObjectPtr<UActionBase> SelectedAction;
};
