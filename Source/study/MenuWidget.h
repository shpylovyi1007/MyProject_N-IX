// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class UButton;
class UImage;
class UWidgetSwitcher;
class UEditableText;
class UCheckBox;

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
	
protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GoToSettingsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GoToMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> PlayerNameInput;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> ShowNameCheckBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void OnGoToSettings();

	UFUNCTION()
	void OnGoToMainMenu();

	UFUNCTION()
	void OnPlayerNameChanged(const FText& Text);

	UFUNCTION()
	void OnShowNameChanged(bool bIsChecked);
};
