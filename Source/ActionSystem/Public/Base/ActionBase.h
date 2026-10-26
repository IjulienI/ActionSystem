// Copyright (c) 2026 Julien soum. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "ActionSystemTypes.h"
#include "UObject/Object.h"
#include "ActionBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishDelegate);

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced, CollapseCategories)
class ACTIONSYSTEM_API UActionBase : public UObject
{
	GENERATED_BODY()
	
public:	
	//---------------------------------------
	// Public API
	//---------------------------------------
	UFUNCTION(BlueprintCallable, Category = "ActionSystem", meta = (WorldContext = "WorldContextObject"))
	void Initialize(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ActionSystem")
	void Execute(AActor* InInstigator);
	
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void Deinitialize();

	//---------------------------------------
	// Getters
	//---------------------------------------
	bool GetAutoInit() const { return Advanced.bAutoInit; }
	bool GetInitialized() const { return bInitialized; }

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", AdvancedDisplay)
	FActionAdvancedSettings Advanced;

protected:
	//---------------------------------------
	// Internal API
	//---------------------------------------
	UFUNCTION(BlueprintNativeEvent, Category = "ActionSystem")
	void OnInit(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintNativeEvent, Category = "ActionSystem")
	void OnDestroy();
	
	UFUNCTION(BlueprintCallable, Category = "ActionSystem")
	void Finish() const;
	
	//---------------------------------------
	// Internal vars
	//---------------------------------------
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Action", AdvancedDisplay)
	TObjectPtr<AActor> Instigator;
	
	bool bInitialized = false;

	//---------------------------------------
	// Resolvers
	//---------------------------------------
	UFUNCTION(BlueprintPure, Category = "ActionSystem")
	AActor* ResolveTarget(const FActionTarget& Target) const;
	
	UFUNCTION(BlueprintPure, Category = "ActionSystem")
	bool ResolveTransform(const FActionTransform& InTransform, FTransform& OutTransform) const;
};
