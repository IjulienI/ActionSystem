// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/LightSwitchAction.h"

#include "Engine/Light.h"

ULightSwitchAction::ULightSwitchAction()
{
	Advanced.ActionName = "LightSwitch";
}

void ULightSwitchAction::OnInit_Implementation(UObject* WorldContextObject)
{
	Super::OnInit_Implementation(WorldContextObject);
	
	for (TObjectPtr<ALight>& Light : Lights)
	{
		if (!ensure(Light)) continue;
		
		Light->SetEnabled(bStartOn);
	}
	bIsOn = bStartOn;
}

void ULightSwitchAction::Run_Implementation()
{
	Super::Run_Implementation();
	
	bIsOn = !bIsOn;
	for (TObjectPtr<ALight>& Light : Lights)
	{
		if (!ensure(Light)) continue;
		
		Light->SetEnabled(bIsOn);
	}
}
