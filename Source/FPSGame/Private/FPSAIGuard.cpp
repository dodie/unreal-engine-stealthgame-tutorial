// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameMode.h"
#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateAbstractDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnPawnHeard);

	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->CompleteMission(SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Blue, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f, false);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState || GuardState == EAIState::Alerted)
	{
		return;
	}

	GuardState = NewState;
	OnStateChanged(NewState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


