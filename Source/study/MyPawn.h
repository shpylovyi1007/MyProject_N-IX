// #pragma once
//
// class UMenuWidget;                                   
//
// #include "CoreMinimal.h"
// #include "GameFramework/Pawn.h"
// #include "GameFramework/SpringArmComponent.h"
// #include "Camera/CameraComponent.h"
// #include "InputActionValue.h"
// #include "InputMappingContext.h"
// #include "Components/WidgetComponent.h"
// #include "Components/CapsuleComponent.h"
// #include "MyPawn.generated.h"
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyActors);
//
// UCLASS()
// class STUDY_API AMyPawn : public APawn
// {
// 	GENERATED_BODY()
//
// public:
// 	AMyPawn();
// 	
// 	UPROPERTY(BlueprintAssignable, Category = "Events")
// 	FOnDestroyActors OnDestroyActors;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
// 	FString PlayerName = TEXT("Player");
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
// 	bool bShowPlayerName = true;
// 	
// 	
// 	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
// 	FORCEINLINE UCameraComponent* GetFollowCamera() const { return CameraComponent; }
//
// protected:
// 	virtual void BeginPlay() override;
//     
// 	// UPROPERTY(EditDefaultsOnly)
// 	// TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
// 	
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
// 	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<USpringArmComponent> SpringArmComponent;
//     
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UCameraComponent> CameraComponent;
//     
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputMappingContext> InputMappingContext;
//     
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionMove;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionZoom;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionLook;
//     
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionSpawnProjectile;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	TSubclassOf<class AAProjectile> ProjectileClass;  
// 	
// 	UPROPERTY() 
// 	TObjectPtr<AAProjectile> LastSpawnedProjectile;
// 	
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionRotateProjectile;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionIncreaseScale;
//
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionDecreaseScale;
//     
// 	UPROPERTY(EditDefaultsOnly)
// 	TObjectPtr<UInputAction> InputActionLineTrace;
// 	
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	TObjectPtr<UStaticMeshComponent> ReadOnlyStaticMesh;
// 	
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	TObjectPtr<UCapsuleComponent> CapsuleComponent;
// 	
// 	UPROPERTY(EditDefaultsOnly, Category = "Input")
// 	TObjectPtr<UInputAction> InputActionInteract;
//     
// 	UPROPERTY(EditDefaultsOnly, Category = "Input")
// 	TObjectPtr<UInputAction> InputActionDestroy;
// 	
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
// 	float ForwardInputValue;
//
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
// 	float RightInputValue;
//
// 	void ResetMovementInput(const FInputActionValue& Value);
//
// 	 
//     
// 	void PerformLineTrace();
// 	void InputMove(const FInputActionValue& InputActionValue);
// 	void InputZoom(const FInputActionValue& InputActionValue);
// 	void InputLook(const FInputActionValue& InputActionValue);
// 	void RotateLastProjectile(const FInputActionValue& InputActionValue);
// 	void IncreaseScale();
// 	void DecreaseScale();
// 	void SpawnProjectile();
// 	void InteractWithAll();
// 	void DestroyAllScalableActors(); 
// 	void InteractWithAllLights();
// 	
// 	
// 	float CurrentScale = 1.0f;  
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
// 	TObjectPtr<UWidgetComponent> WidgetComponent;
// 	
// 	UPROPERTY(EditDefaultsOnly, Category = "Input")
// 	TObjectPtr<UInputAction> InputActionPause;
//
// 	UPROPERTY(EditDefaultsOnly, Category = "UI")
// 	TSubclassOf<UMenuWidget> PauseMenuClass;
//
// 	UPROPERTY()
// 	TObjectPtr<UMenuWidget> PauseMenuInstance;
//
// 	void TogglePause();
// 	
// 	void Move(const FInputActionValue& Value);
// 	void Look(const FInputActionValue& Value);
//
// 	
// public: 
// 	virtual void Tick(float DeltaTime) override;
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
// };