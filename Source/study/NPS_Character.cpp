#include "NPS_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ANPS_Character::ANPS_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ANPS_Character::BeginPlay()
{
	Super::BeginPlay();
}
