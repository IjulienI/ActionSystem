// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Base/DecoratorAction.h"

#include "ActionSystem.h"

void UDecoratorAction::OnInit_Implementation(UObject* WorldContextObject)
{
	Super::OnInit_Implementation(WorldContextObject);
	
	if (Child && Child->GetAutoInit())
	{
		Child->Initialize(WorldContextObject);
	}
}

void UDecoratorAction::OnCancel_Implementation()
{
	UnbindChild();

	if (Child)
	{
		Child->Cancel();
	}
	
	Super::OnCancel_Implementation();
}

void UDecoratorAction::OnDestroy_Implementation()
{
	UnbindChild();

	if (Child)
	{
		Child->Deinitialize();
	}
	
	Super::OnDestroy_Implementation();
}

bool UDecoratorAction::RunChild()
{
	if (!Child)
	{
		UE_LOG(LogActionSystem, Warning, TEXT("%s '%s' on %s has no action to run."), *GetClass()->GetName(), *Advanced.ActionName, *GetNameSafe(GetTypedOuter<AActor>()));
		return false;
	}

	Child->OnFinishDelegate.AddUniqueDynamic(this, &UDecoratorAction::HandleChildFinished);
	Child->Execute(Instigator);
	return true;
}

void UDecoratorAction::OnChildFinished_Implementation()
{
	Finish();
}

void UDecoratorAction::HandleChildFinished()
{
	UnbindChild();
	OnChildFinished();
}

void UDecoratorAction::UnbindChild()
{
	if (Child)
	{
		Child->OnFinishDelegate.RemoveDynamic(this, &UDecoratorAction::HandleChildFinished);
	}
}
