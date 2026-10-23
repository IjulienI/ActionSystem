// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"


class UActionBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONSYSTEM_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionComponent();

	//---------------------------------------
	// Base overrides
	//---------------------------------------
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//---------------------------------------
	// Public API
	//---------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void InitActions(bool bAutoInit = false);
	
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void ExecuteActions();
	
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void DestroyActions();

private:
	//---------------------------------------
	// Internal vars
	//---------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActionSystem", meta = (AllowPrivateAccess = true))
	TArray<UActionBase*> Actions;
};
