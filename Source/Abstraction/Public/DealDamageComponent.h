// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DealDamageComponent.generated.h"

class UCapsuleComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UDealDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDealDamageComponent();

	//virtual void TickComponent(float Deltatime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* GetTriggerCapsule() const { return TriggerCapsule; }

	bool IsActive() const { return bActive; }
	void SetActive(bool IsActive) { bActive = IsActive; }


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 20.0f;
	
	//base damage distrubuted over this time
	UPROPERTY(EditAnywhere)
	float DamageTotalTime = 2.0f;

	//interval at which to apply damge
	UPROPERTY(EditAnywhere, NoClear)
	float TakeDamageInterval = 0.5f;
	

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule;

	bool bActive = true;

};
