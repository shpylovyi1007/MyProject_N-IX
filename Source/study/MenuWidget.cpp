#include "MenuWidget.h"

#include "MyCharacter.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"




void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ContinueButton)
		ContinueButton->OnClicked.AddDynamic(this, &UMenuWidget::OnContinueClicked);

	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitClicked);

	if (GoToSettingsButton)
		GoToSettingsButton->OnClicked.AddDynamic(this, &UMenuWidget::OnGoToSettings);

	if (GoToMainMenuButton)
		GoToMainMenuButton->OnClicked.AddDynamic(this, &UMenuWidget::OnGoToMainMenu);

	if (PlayerNameInput)
		PlayerNameInput->OnTextChanged.AddDynamic(this, &UMenuWidget::OnPlayerNameChanged);

	if (ShowNameCheckBox)
		ShowNameCheckBox->OnCheckStateChanged.AddDynamic(this, &UMenuWidget::OnShowNameChanged);
}

void UMenuWidget::OnContinueClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	SetVisibility(ESlateVisibility::Hidden);

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void UMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMenuWidget::OnGoToSettings()
{
	if (MenuSwitcher)
		MenuSwitcher->SetActiveWidgetIndex(1);
}

void UMenuWidget::OnGoToMainMenu()
{
	if (MenuSwitcher)
		MenuSwitcher->SetActiveWidgetIndex(0);
}
void UMenuWidget::OnPlayerNameChanged(const FText& Text)
{
	if (AMyCharacter* Pawn = Cast<AMyCharacter>(
		GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Pawn->PlayerName = Text.ToString();
	}
}

void UMenuWidget::OnShowNameChanged(bool bIsChecked)
{
	if (AMyCharacter* Pawn = Cast<AMyCharacter>(
		GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Pawn->bShowPlayerName = bIsChecked;
	}
}