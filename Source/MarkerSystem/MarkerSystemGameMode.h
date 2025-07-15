// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <MarkerFactory.h>

#include "MarkerSystemGameMode.generated.h"

UCLASS(minimalapi)
class AMarkerSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMarkerSystemGameMode();

	MarkerFactory* GetMarkerFactory() const { return m_markerFactory.get(); };

private:
	std::unique_ptr<MarkerFactory> m_markerFactory;
};



