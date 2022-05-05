// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

class UHealthComponent;
class UParticleSystemComponent;
class UDamageHandlerComponent;

DECLARE_MULTICAST_DELEGATE(FOnInteractionStart);
DECLARE_MULTICAST_DELEGATE(FOnInteractionCancel);

UCLASS()
class ABSTRACTION_API AAbstractionPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

	/** Called when the actor falls out of the world 'safely' (below KillZ and such) */
	void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	FOnInteractionStart OnInteractionStart;
	FOnInteractionCancel OnInteractionCancel;

	UFUNCTION(BlueprintCallable)
		const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
		const float GetCurrentHealth() const;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	UDamageHandlerComponent* DamageHandlerComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	void StartInteraction();
	void StopInteraction();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;



};
