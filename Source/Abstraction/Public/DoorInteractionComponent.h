// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere)
	//FRotator DesiredRotation = FRotator::ZeroRotator;

	//FRotator StartRotation = FRotator::ZeroRotator;
	//FRotator FinalRotation = FRotator::ZeroRotator;

	/*UPROPERTY(EditAnywhere)
		float TimeToRotate = 1.0f;*/

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox;

	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.4f;

	float DoorLastOpened = 0.f;


	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 0.8f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 0.3f;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
		
};
