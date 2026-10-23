// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionBase.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class ACTIONSYSTEM_API UActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	//---------------------------------------
	// Public API
	//---------------------------------------
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActionSystem", meta = (WorldContext = "WorldContextObject"))
	void Init(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActionSystem")
	void Execute();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActionSystem")
	void Destroy();

	//---------------------------------------
	// Getters
	//---------------------------------------
	bool GetAutoInit() const { return bAutoInit; }

	//---------------------------------------
	// Local Getters
	//---------------------------------------
	UFUNCTION(BlueprintCallable, Category="ActionSystem")
	UObject* GetOwner() const { return  GetOuter(); }
	
	virtual UWorld* GetWorld() const override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action|Advanced", meta = (AllowPrivateAccess = true))
	bool bAutoInit = true;
};
