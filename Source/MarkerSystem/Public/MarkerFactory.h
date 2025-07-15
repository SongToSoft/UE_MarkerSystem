// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Marker.h>
#include <MyPlayerCharacter.h>

/**
 * 
 */
class MARKERSYSTEM_API MarkerFactory
{
public:
	MarkerFactory();
	~MarkerFactory();

	void SpawnMarker(const TSubclassOf<AMarker>& markerClass, const EMarkerType type, const AMarkerSystemCharacter& character);

private:
	void RemoveMarker(AMarker* marker);
};
