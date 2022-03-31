// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbstractionGameModeBase.h"
#include "ObjectiveWorldSubsystem.h"


//#include "AbstractionCharacter.h"
//#include "UObject/ConstructorHelpers.h"


//AAbstractionGameModeBase::AAbstractionGameModeBase()
//{
//	// set default pawn class to our Blueprinted character
//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
//	if (PlayerPawnBPClass.Class != NULL)
//	{
//		DefaultPawnClass = PlayerPawnBPClass.Class;
//	}
//}


void AAbstractionGameModeBase::StartPlay()
{
	Super::StartPlay();

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}






	/*if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController (GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}

	if (ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}*/


}