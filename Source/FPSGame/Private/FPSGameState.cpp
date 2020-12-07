// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"


void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bSuccess)
{
// 	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
// 	{
// 		APawn* Pawn = It->Get();
// 		if (Pawn && Pawn->IsLocallyControlled())
// 		{
// 			Pawn->DisableInput(nullptr);
// 		}
// 	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PlayerController = Cast<AFPSPlayerController>(It->Get());
		if (PlayerController && PlayerController->IsLocalController())
		{
			PlayerController->OnMissionCompleted(InstigatorPawn, bSuccess);

			APawn* MyPawn = PlayerController->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(nullptr);
			}
		}
	}
}

