// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystemTypes.generated.h"

//---------------------------------------
// TriggerPolicy
//---------------------------------------
UENUM(BlueprintType)
enum class EActionTriggerPolicy : uint8
{
	Ignore,
	Restart,
	Queue
};

//---------------------------------------
// Advanced Tab
//---------------------------------------
USTRUCT(BlueprintType)
struct FActionAdvancedSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bAutoInit = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FString ActionName = TEXT("Action");
};

//---------------------------------------
// ActionTarget
//---------------------------------------
UENUM(BlueprintType)
enum class EActionTargetSource : uint8
{
	Self,
	Instigator,
	Reference
};

USTRUCT(BlueprintType)
struct FActionTarget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	EActionTargetSource Source = EActionTargetSource::Instigator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta = (EditCondition = "Source == EActionTargetSource::Reference", EditConditionHides))
	TObjectPtr<AActor> Reference;
};

//---------------------------------------
// ActionTransform
//---------------------------------------
UENUM(BlueprintType)
enum class EActionTransformSource : uint8
{
	Self,
	Instigator,
	Reference,
	Absolute
};

USTRUCT(BlueprintType)
struct FActionTransform
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	EActionTransformSource Source = EActionTransformSource::Absolute;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (EditCondition = "Source == EActionTransformSource::Reference", EditConditionHides))
	TObjectPtr<AActor> Reference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform", meta = (EditCondition = "Source == EActionTransformSource::Absolute", EditConditionHides))
	FTransform Transform = FTransform::Identity;
};