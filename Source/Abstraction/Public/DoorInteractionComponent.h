// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	FRotator StartRotation = FRotator::ZeroRotator;
	
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
		float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox1;
	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox2;


	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve OpenCurve;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.4f;

	float DoorLastOpened;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	bool bDoorIsOpen = false;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
