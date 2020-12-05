// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpoint)
		{
			APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());

			if (PlayerController) {
				TArray<AActor*> SpectatingViewpoints;
				UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, SpectatingViewpoints);

				if (SpectatingViewpoints.Num() > 0)
				{
					PlayerController->SetViewTargetWithBlend(SpectatingViewpoints[0], 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("No spectating viewpoint defined, can't set new viewport in FPSGameMode!"));
		}
	}

	OnMissionCompleted(InstigatorPawn);
}
