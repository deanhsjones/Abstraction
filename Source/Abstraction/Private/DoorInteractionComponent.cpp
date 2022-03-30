// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

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

	DesiredRotation;//open angle
	StartRotation = GetOwner()->GetActorRotation();	//initialyaw
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation; //closedyaw
	const FRotator CurrentRotation = FRotator::ZeroRotator;
	
	

	/*GetOwner()->SetActorRotation(DesiredRotation);*/
	CurrentRotationTime = 0.0f;

	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentTime = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("CurrentTime %f"), &CurrentTime);

	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();*/
	/*if (!CurrentRotation.Equals(FinalRotation, 5.0f))*/
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (CurrentRotationTime < TimeToRotate)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("CurrentRotationTime %f, TimeToRotate %f"), &CurrentRotationTime, &TimeToRotate);*/
		
		if (!bDoorIsOpen && TriggerBox1 && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			if (PlayerPawn && TriggerBox1->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				OpenDoor(DeltaTime);



			}
			/*if (PlayerPawn && TriggerBox2->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				
				OpenDoor(DeltaTime);



			}*/

		}
	}
	else 
		if (PlayerPawn && bDoorIsOpen && !(TriggerBox1->IsOverlappingActor(PlayerPawn)) ) //&& !(TriggerBox2->IsOverlappingActor(PlayerPawn))
		{
			CloseDoor(DeltaTime);
		}
				DebugDraw();
}

void UDoorInteractionComponent::OpenDoor(float DeltaTime)
{
	

				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.1f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(CurrentRotation, FinalRotation, RotationAlpha);
				APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
				//CurrentRotation += DeltaRotation * DeltaTime;
				if (TriggerBox1->IsOverlappingActor(PlayerPawn))
				{
					GetOwner()->SetActorRotation(CurrentRotation);
				}

				/*if (TriggerBox2->IsOverlappingActor(PlayerPawn))
				{
					GetOwner()->SetActorRotation(CurrentRotation * -1);
				}*/

				
				//UE_LOG(LogTemp, Warning, TEXT("Open door %s"), *GetOwner()->GetActorRotation().ToString());
				//UE_LOG(LogTemp, Warning, TEXT("Doorlastopen %f"), &DoorLastOpened);
				if (CurrentRotation == FinalRotation)
				{
					DoorState = EDoorState::DS_Open;
					bDoorIsOpen = true;
				}
	
}

void UDoorInteractionComponent::CloseDoor(float DeltaTime)
{
	CurrentRotationTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("RotationTime %f"), CurrentRotationTime);

	const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 3.0f);
	const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
	const FRotator CurrentRotation = FMath::Lerp(FinalRotation, StartRotation, RotationAlpha);
	GetOwner()->SetActorRotation(CurrentRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Close Door %s"), *GetOwner()->GetActorRotation().ToString());
	DoorState = EDoorState::DS_Closed;
	bDoorIsOpen = false;
	CurrentRotationTime = 0;
	
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