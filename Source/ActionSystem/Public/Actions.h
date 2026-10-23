// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "Actions.generated.h"


//---------------------------------------
// DestroyActors
//---------------------------------------
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ACTIONSYSTEM_API UDestroyActors : public UActionBase
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<AActor>> Actors;
};

//---------------------------------------
// LightSwitch
//---------------------------------------
class ALight;

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class ACTIONSYSTEM_API ULightSwitch : public UActionBase
{
	GENERATED_BODY()

public:
	virtual void Init_Implementation(UObject* WorldContextObject) override;
	virtual void Execute_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<ALight>> Lights;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true))
	bool bStartOn = true;
	
	bool bIsOn = false;
	
	void SetLightsEnabled(bool bEnabled);
};
