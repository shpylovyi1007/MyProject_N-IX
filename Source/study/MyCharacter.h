// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Components/WidgetComponent.h"
#include "MyCharacter.generated.h"

class UMenuWidget;
class AAProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyActorsCharacter);

UCLASS()
class STUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDestroyActorsCharacter OnDestroyActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString PlayerName = TEXT("Player");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bShowPlayerName = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float ForwardInputValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float RightInputValue;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	   UPROPERTY(EditDefaultsOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UWidgetComponent> WidgetComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionMove;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionZoom;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionLook;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionSpawnProjectile;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionRotateProjectile;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionIncreaseScale;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionDecreaseScale;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionLineTrace;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionInteract;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionDestroy;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> InputActionPause;

    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<AAProjectile> ProjectileClass;

    UPROPERTY()
    TObjectPtr<AAProjectile> LastSpawnedProjectile;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuWidget> PauseMenuClass;

    UPROPERTY()
    TObjectPtr<UMenuWidget> PauseMenuInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> ReadOnlyStaticMesh;
	
	
    float CurrentScale = 1.0f;

    void InputMove(const FInputActionValue& Value);
    void InputMoveCompleted(const FInputActionValue& Value);
    void InputZoom(const FInputActionValue& Value);
    void InputLook(const FInputActionValue& Value);
    void LookCompleted(const FInputActionValue& Value);
    void IncreaseScale();
    void DecreaseScale();
    void SpawnProjectile();
    void RotateLastProjectile(const FInputActionValue& Value);
    void PerformLineTrace();
    void InteractWithAllLights();
    void DestroyAllScalableActors();
    void TogglePause();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
