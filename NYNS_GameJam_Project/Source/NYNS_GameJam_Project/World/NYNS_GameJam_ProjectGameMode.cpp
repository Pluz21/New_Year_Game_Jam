// Copyright Epic Games, Inc. All Rights Reserved.

#include "NYNS_GameJam_ProjectGameMode.h"
#include "NYNS_GameJam_Project/Actors/NYNS_GameJam_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANYNS_GameJam_ProjectGameMode::ANYNS_GameJam_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
