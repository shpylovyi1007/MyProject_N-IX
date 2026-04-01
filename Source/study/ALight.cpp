// Fill out your copyright notice in the Description page of Project Settings.


#include "ALight.h"

// Sets default values
AALight::AALight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AALight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AALight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

