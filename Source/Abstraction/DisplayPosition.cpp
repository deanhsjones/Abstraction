// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/Actor.h"
#include "DisplayPosition.h"
#include "Engine/Engine.h"


// Sets default values for this component's properties
UDisplayPosition::UDisplayPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDisplayPosition::BeginPlay()
{
	Super::BeginPlay();

	

	// ...
	
}


// Called every frame
void UDisplayPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

FString ObjectName = GetOwner()->GetName();
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPosition);
	GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, FString::Printf(TEXT("%s is at %s"), *ObjectName, *ObjectPosition));
	


	// ...
}



