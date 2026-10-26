// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstantAction.h"
#include "LightSwitchAction.generated.h"

class ALight;

UCLASS()
class ACTIONSYSTEM_API ULightSwitchAction : public UInstantAction
{
	GENERATED_BODY()
	
public:
	ULightSwitchAction();
	virtual void OnInit_Implementation(UObject* WorldContextObject) override;
	virtual void Run_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Action", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<ALight>> Lights;
	
	UPROPERTY(EditAnywhere, Category = "Action")
	bool bStartOn = true;
	
	bool bIsOn = false;
};
