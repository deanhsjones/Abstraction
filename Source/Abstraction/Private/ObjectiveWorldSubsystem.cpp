// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
//#include "ObjectiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../AbstractionGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveHud.h"

void UObjectiveWorldSubsystem::Deinitialize()
{
	ObjectiveWidget = nullptr;
	ObjectivesCompleteWidget = nullptr;
}

//void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
//{
//	if (ObjectiveWidget == nullptr)
//	{
//		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
//	}
//}


void UObjectiveWorldSubsystem::CreateObjectiveWidgets()
{
	if (ObjectiveWidget == nullptr)
	{
		AAbstractionGameModeBase* GameMode = Cast<AAbstractionGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ObjectiveWidget = CreateWidget<UObjectiveHud>(PlayerController, GameMode->ObjectiveWidgetClass);
			ObjectivesCompleteWidget = CreateWidget<UUserWidget>(PlayerController, GameMode->ObjectivesCompleteWidgetClass);
		}
	}
}


void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
		ObjectiveWidget->UpdateObjectiveText(GetCompletedObjectiveCount(), Objectives.Num());

	}
	/*ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is a nullptr"));*/
}

void UObjectiveWorldSubsystem::RemoveObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		ObjectiveWidget->RemoveFromViewport();
	}
}





void UObjectiveWorldSubsystem::DisplayObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->AddToViewport();
	}
}

void UObjectiveWorldSubsystem::RemoveObjectivesCompleteWidget()
{
	if (ObjectivesCompleteWidget)
	{
		ObjectivesCompleteWidget->RemoveFromViewport();
	}
}

//void UObjectiveWorldSubsystem::OnObjectiveCompleted()
//{
//	DisplayObjectiveWidget();
//}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT("Completed!");
	}

	return RetObjective;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);

	}
}

uint32 UObjectiveWorldSubsystem::GetCompletedObjectiveCount()
{
	uint32 ObjectiveCompleted = 0u;
	for (const UObjectiveComponent* OC : Objectives)
	{
		if (OC && OC->GetState() == EObjectiveState::OS_Completed)
		{
			++ObjectiveCompleted;
		}
	}

	return ObjectiveCompleted;
}

void UObjectiveWorldSubsystem::OnMapStart()
{
	AAbstractionGameModeBase* GameMode = Cast<AAbstractionGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		CreateObjectiveWidgets();
		DisplayObjectiveWidget();
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent)
{
	int32 numRemoved = ObjectiveComponent->OnStateChanged().RemoveAll(this);
	check(numRemoved);
	Objectives.Remove(ObjectiveComponent);
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* UObjectiveComponent, EObjectiveState ObjectiveState)
{
	if (ObjectiveWidget && ObjectivesCompleteWidget)
	{
		if (GetCompletedObjectiveCount() == Objectives.Num())
		{
			//GameOver
			RemoveObjectiveWidget();
			DisplayObjectivesCompleteWidget();
		}
		else
		{
			DisplayObjectiveWidget();
		}
	}
}
