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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Action", AdvancedDisplay)
	TObjectPtr<AActor> Instigator;
	
	bool bInitialized = false;

	//---------------------------------------
	// Internal funcs
	//---------------------------------------
	UFUNCTION(BlueprintPure, Category = "ActionSystem")
	AActor* ResolveTarget(const FActionTarget& Target) const;
};
