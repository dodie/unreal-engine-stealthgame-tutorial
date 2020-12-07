// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};


UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnStateChanged(EAIState NewState);

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bShouldPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* PatrolPoint1;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* PatrolPoint2;

	void MoveToNextPatrolPoint();

	AActor* CurrentPatrolPoint;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
