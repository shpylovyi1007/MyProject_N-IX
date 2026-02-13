// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapCube.h"

// Sets default values
AOverlapCube::AOverlapCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;
    
	CubeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    
	CubeMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
    
	CubeMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CubeMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    
	CubeMesh->SetGenerateOverlapEvents(true);
	
}

// Called when the game starts or when spawned
void AOverlapCube::BeginPlay()
{
	Super::BeginPlay();
	
	CubeMesh->OnComponentBeginOverlap.AddDynamic(this, &AOverlapCube::OnCubeBeginOverlap);
}

// Called every frame
void AOverlapCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverlapCube::OnCubeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									   bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 
				3.0f, 
				FColor::Green, 
				FString::Printf(TEXT("Overlap with cube: %s"), *GetName())
			);
		}
	}
}
