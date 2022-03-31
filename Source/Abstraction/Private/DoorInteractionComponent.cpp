// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "ObjectiveWorldSubsystem.h"

#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("Abstraction.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display."),
	ECVF_Default);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Closed;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(UDoorInteractionComponent::OnDebugToggled));

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//DesiredRotation;//open angle
	StartRotation = GetOwner()->GetActorRotation();	//initialyaw
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation; //closedyaw
	const FRotator CurrentRotation = FRotator::ZeroRotator;
	
	

	/*GetOwner()->SetActorRotation(DesiredRotation);*/
	CurrentRotationTime = 0.0f;

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		OpenedEvent.AddUObject(ObjectiveWorldSubsystem, &UObjectiveWorldSubsystem::OnObjectiveCompleted); //bind openedevent to Uobject(objworld subsystem) and the function within it
	}

	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorState == EDoorState::DS_Closed)
	{
		if (TriggerBox1 && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox1->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_Opening;
				CurrentRotationTime = 0.0f;
			}
		}
	}

	else if (DoorState == EDoorState::DS_Opening)
	{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.1f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(CurrentRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);

				if (TimeRatio >= 1.0f)
				{
					DoorState = EDoorState::DS_Open;
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
					OpenedEvent.Broadcast();
				}
		//OpenDoor(DeltaTime);
	}


	DebugDraw();
}


void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UDoorInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 2.0f);
	}
}


//void UDoorInteractionComponent::OpenDoor(float DeltaTime)
//{
	

				/*APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
				
				if (TriggerBox1->IsOverlappingActor(PlayerPawn))
				{
				}*/

				/*if (TriggerBox2->IsOverlappingActor(PlayerPawn))
				{
					GetOwner()->SetActorRotation(CurrentRotation * -1);
				}*/

				
				//UE_LOG(LogTemp, Warning, TEXT("Open door %s"), *GetOwner()->GetActorRotation().ToString());
				//UE_LOG(LogTemp, Warning, TEXT("Doorlastopen %f"), &DoorLastOpened);
				//if (CurrentRotation == FinalRotation)
				/*{
					DoorState = EDoorState::DS_Open;
					bDoorIsOpen = true;
				}*/
	
//}

//void UDoorInteractionComponent::CloseDoor(float DeltaTime)
//{
//	CurrentRotationTime += DeltaTime;
//	//UE_LOG(LogTemp, Warning, TEXT("RotationTime %f"), CurrentRotationTime);
//
//	const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 3.0f);
//	const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
//	const FRotator CurrentRotation = FMath::Lerp(FinalRotation, StartRotation, RotationAlpha);
//	GetOwner()->SetActorRotation(CurrentRotation);
//	//UE_LOG(LogTemp, Warning, TEXT("Close Door %s"), *GetOwner()->GetActorRotation().ToString());
//	DoorState = EDoorState::DS_Closed;
//	bDoorIsOpen = false;
//	CurrentRotationTime = 0;
//	
//}