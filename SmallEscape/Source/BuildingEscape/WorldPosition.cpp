// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//FString LogT = TEXT("Hello");
	//FString* PtrLog = &LogT;

	//(*PtrLog).Len();
	//PtrLog->Len();


	//UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog); //Yellow

	//UE_LOG(LogTemp, Error, TEXT("This is an error")); //Red
	//UE_LOG(LogTemp, Log, TEXT("This is a Log")); //Log
	//UE_LOG(LogTemp, Display, TEXT("This is a Display")); //Display Log

	//GetOwner()->GetName();

	//UE_LOG(LogTemp, Warning, TEXT("This is a: %s"), *GetOwner()->GetName());

	FString Object = GetOwner()->GetName();
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *Object, *ObjectPosition);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

