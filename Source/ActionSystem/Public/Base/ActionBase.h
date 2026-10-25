// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishDelegate);

USTRUCT(BlueprintType)
struct FActionAdvancedSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoInit = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action")
	FString ActionName = TEXT("Action");
};

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced, CollapseCategories)
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
	bool GetAutoInit() const { return Advanced.bAutoInit; }

	//---------------------------------------
	// Local Getters
	//---------------------------------------
	UFUNCTION(BlueprintCallable, Category="ActionSystem")
	UObject* GetOwner() const { return  GetOuter(); }
	
	virtual UWorld* GetWorld() const override;

	//---------------------------------------
	// Delegates
	//---------------------------------------
	UPROPERTY(BlueprintAssignable, Category = "ActionSystem")
	FOnFinishDelegate OnFinishDelegate;
	
	//---------------------------------------
	// Public vars
	//---------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", AdvancedDisplay, meta = (AllowPrivateAccess = true))
	FActionAdvancedSettings Advanced;

protected:
	//---------------------------------------
	// Internal API
	//---------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void Finish() const;
};
