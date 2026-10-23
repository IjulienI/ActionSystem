// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions.h"

//---------------------------------------
// DestroyActors
//---------------------------------------
void UDestroyActors::Execute_Implementation()
{
	Super::Execute_Implementation();
	
	for (TObjectPtr<AActor>& Actor : Actors)
	{
		if (!ensure(Actor)) continue;
		
		Actor->Destroy();
	}
	Actors.Empty();
}

//---------------------------------------
// LightSwitch
//---------------------------------------
#include "Engine/Light.h"

void ULightSwitch::Init_Implementation(UObject* WorldContextObject)
{
	Super::Init_Implementation(WorldContextObject);
	bIsOn = bStartOn;
	SetLightsEnabled(bIsOn);
}

void ULightSwitch::Execute_Implementation()
{
	Super::Execute_Implementation();
	
	SetLightsEnabled(!bIsOn);
	bIsOn = !bIsOn;
}

void ULightSwitch::SetLightsEnabled(bool bEnabled)
{
	for (TObjectPtr<ALight>& Light : Lights)
	{
		if (!ensure(Light)) continue;
		
		Light->SetEnabled(bEnabled);
	}
}
