// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABlockCube.generated.h"

UCLASS()
class STUDY_API AABlockCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABlockCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> CubeStaticMesh;
	
	UFUNCTION()
	void OnCubeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
				   UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
				   const FHitResult& Hit);
};
