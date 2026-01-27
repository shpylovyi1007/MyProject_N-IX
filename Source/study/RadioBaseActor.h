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
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComponent;

	UFUNCTION(BlueprintCallable, Category = "Radio")
     virtual  void RadioOnOff(bool bShouldBeOn);
};