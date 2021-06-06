// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw); //Display Log
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	//OpenAngle = OpenAngle + InitialYaw;
	OpenAngle += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressureplate set!"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenDoor)
	{
		OpenTheDoor(DeltaTime);
		DoorLastOpenend = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenend > DoorCloseDelay)
		{
			CloseTheDoor(DeltaTime);
		}
	}	
}

void UOpenDoor::OpenTheDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}

	/*
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator OpenxDegrees;
	OpenxDegrees.Yaw = 90.f;
	//FRotator OpenDoor {0.f, 90.f, 0.f}; x,y,z

	GetOwner()->SetActorRotation(OpenxDegrees);


	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenXDegrees;
	OpenXDegrees.Yaw = FMath::Lerp(CurrentYaw, MyOpenAngle, 0.02f); //Lerp is not Linear Interpolation because it doesn't suddenly stop when at the end
	//OpenXDegrees.Yaw = FMath::FInterpConstantTo(CurrentYaw, MyOpenAngle, DeltaTime, 45); //Real Linear Interpolation
	//OpenXDegrees.Yaw = FMath::FInterpTo(CurrentYaw, MyOpenAngle, DeltaTime, 2); //Framerate Independ Interpolation with smooth ending

	GetOwner()->SetActorRotation(OpenXDegrees);
	*/
}

void UOpenDoor::CloseTheDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if (!AudioComponent) { return; }
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}

}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s mssing audio component"), *GetOwner()->GetName());
	}
}