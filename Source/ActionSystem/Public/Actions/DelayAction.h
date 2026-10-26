// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActionBase.h"
#include "DelayAction.generated.h"


UCLASS()
class ACTIONSYSTEM_API UDelayAction : public UActionBase
{
	GENERATED_BODY()
	
public:
	UDelayAction();
	virtual void Execute_Implementation(AActor* Instigator) override;
	virtual void OnCancel_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true, ClampMin = 0, Units = "s"))
	float Duration = 0.2f;
	
	FTimerHandle TimerHandle;

	void OnEndTimer();
};
