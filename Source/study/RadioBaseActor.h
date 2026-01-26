#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadioBaseActor.generated.h"

UCLASS(Abstract)
class STUDY_API ARadioBaseActor : public AActor
{
	GENERATED_BODY()
    
public:    
	ARadioBaseActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAudioComponent* AudioComponent;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio")
	void RadioTurnOff();
	virtual void RadioTurnOff_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Radio")
	void RadioTurnOn();
	virtual void RadioTurnOn_Implementation();
};