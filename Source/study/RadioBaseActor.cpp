#include "RadioBaseActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

ARadioBaseActor::ARadioBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
    
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(Root);
    
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(Root);
	AudioComponent->bAutoActivate = false;
}

void ARadioBaseActor::RadioOnOff(bool bShouldBeOn)
{
	if (AudioComponent)
	{
		AudioComponent->SetPaused(!bShouldBeOn);
	}
}