// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	/*GetOwner()->SetActorRotation(DesiredRotation);*/
	CurrentRotationTime = 0.0f;

	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();*/
	/*if (!CurrentRotation.Equals(FinalRotation, 5.0f))*/
	if(CurrentRotationTime < TimeToRotate)
	{
		CurrentRotationTime += DeltaTime;
		const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);

		//CurrentRotation += DeltaRotation * DeltaTime;
		GetOwner()->SetActorRotation(CurrentRotation);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	}

	// ...
}

