// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

void AMenuGameMode::BeginPlay()

{

	Super::BeginPlay();

	if (MenuWidgetClass)

	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);

		if (IsValid(MenuWidget))
		{
			MenuWidget->AddToViewport();
		}

	}

}

void AMenuGameMode::PostLogin(APlayerController* NewPlayer)

{
	if (IsValid(NewPlayer))

	{
		NewPlayer->SetShowMouseCursor(true);
		NewPlayer->SetInputMode(FInputModeUIOnly());
	}
}