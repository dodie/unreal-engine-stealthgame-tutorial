// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 10.0f));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);
	RootComponent = OverlapComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(OverlapComp);

	LaunchPitchAngle = 35.0f;
	LaunchStrength = 1500;
}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
	}
}



