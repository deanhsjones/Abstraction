// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;

	// ...
}



// Called when the game starts
//void UObjectiveComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	//register
//	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
//	if (ObjectiveWorldSubsystem)
//	{
//		ObjectiveWorldSubsystem->AddObjective(this);
//	}
//
//	// ...
//	
//}

void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		State = NewState;
		StateChangedEvent.Broadcast(this, State);
	}
}

void UObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}

void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);

}





