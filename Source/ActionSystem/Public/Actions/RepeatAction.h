// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/DecoratorAction.h"
#include "RepeatAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API URepeatAction : public UDecoratorAction
{
	GENERATED_BODY()
	
public:
	URepeatAction();
	virtual void Execute_Implementation(AActor* InInstigator) override;
	
protected:
	virtual void OnCancel_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	virtual void OnChildFinished_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Action", meta = (AllowPrivateAccess = true, ClampMin = 0, UIMin = 0))
	int32 Count = 2;

	int32 CompletedRuns = 0;

	FTimerHandle NextRunHandle;

	void ClearNextRun();
};
