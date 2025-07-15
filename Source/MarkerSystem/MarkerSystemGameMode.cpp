// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarkerSystemGameMode.h"
#include "MarkerSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMarkerSystemGameMode::AMarkerSystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	m_markerFactory = std::make_unique<MarkerFactory>();
}
