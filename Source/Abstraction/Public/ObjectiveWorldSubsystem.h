// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameframework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveComponent.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWorldSubsystem.generated.h"

class UObjectiveComponent;
class UObjectiveHud;

/**
 * 
 */
UCLASS()
class ABSTRACTION_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:


	void OnObjectiveCompleted();

	UFUNCTION(BlueprintCallable)
		FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
		void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	void OnMapStart();
	
protected:

	virtual void Deinitialize() override;
	
	void CreateObjectiveWidgets();

	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompleteWidget();
	void RemoveObjectivesCompleteWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

private:
	UObjectiveHud* ObjectiveWidget = nullptr;
	UUserWidget* ObjectivesCompleteWidget = nullptr;

	TArray<UObjectiveComponent*> Objectives;
	
};
