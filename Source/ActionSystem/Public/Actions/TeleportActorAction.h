// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstantAction.h"
#include "TeleportActorAction.generated.h"

UCLASS()
class ACTIONSYSTEM_API UTeleportActorAction : public UInstantAction
{
	GENERATED_BODY()
	
public:
	virtual void Run_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = true))
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = true))
	FActionTarget Target;
};
