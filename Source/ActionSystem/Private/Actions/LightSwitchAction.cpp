// Copyright (c) 2026 Julien soum. Licensed under the MIT License.


#include "Actions/LightSwitchAction.h"

#include "Engine/Light.h"

void ULightSwitchAction::Init_Implementation(UObject* WorldContextObject)
{
	Super::Init_Implementation(WorldContextObject);
	
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
