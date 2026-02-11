// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "ABlockCube.h"

// Sets default values
AABlockCube::AABlockCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CubeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeStaticMesh"));
	CubeStaticMesh->SetupAttachment(RootComponent);  
	
	CubeStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CubeStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	CubeStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CubeStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	CubeStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    
	CubeStaticMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AABlockCube::BeginPlay()
{
	Super::BeginPlay();
	CubeStaticMesh->OnComponentHit.AddDynamic(this, &AABlockCube::OnCubeHit);
}


void AABlockCube::OnCubeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
							  UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
							  const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,                         
				3.0f,                        
				FColor::Red,                 
				FString::Printf(TEXT("Hit cube: %s"), *GetName())  
			);
		}
	}
}


// Called every frame
void AABlockCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

