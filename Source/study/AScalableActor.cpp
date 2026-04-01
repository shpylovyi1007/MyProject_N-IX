// Fill out your copyright notice in the Description page of Project Settings.


#include "AScalableActor.h"

// Sets default values
AAScalableActor::AAScalableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void AAScalableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAScalableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

