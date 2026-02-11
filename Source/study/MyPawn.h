#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "MyPawn.generated.h"

UCLASS()
class STUDY_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
	virtual void BeginPlay() override;
    
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
    
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
    
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;
    
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionMove;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionZoom;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionLook;
    
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionSpawnProjectile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AAProjectile> ProjectileClass;  
	
	UPROPERTY() 
	TObjectPtr<AAProjectile> LastSpawnedProjectile;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionRotateProjectile;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionIncreaseScale;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputActionDecreaseScale;
    
	
	void InputMove(const FInputActionValue& InputActionValue);
	void InputZoom(const FInputActionValue& InputActionValue);
	void InputLook(const FInputActionValue& InputActionValue);
	void IncreaseScale();
	void DecreaseScale();
	void SpawnProjectile();
	void RotateLastProjectile(const FInputActionValue& InputActionValue);
	
	float CurrentScale = 1.0f;  
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ReadOnlyStaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;


	
public: 
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};