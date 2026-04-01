// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALight.generated.h"

UCLASS()
class STUDY_API AALight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AALight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
