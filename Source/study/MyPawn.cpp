#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AProjectile.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(RootComponent);
    
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    
    
    
    
    
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CapsuleComponent->SetCapsuleHalfHeight(90.0f);
    CapsuleComponent->SetCapsuleRadius(50.0f);
    RootComponent = CapsuleComponent;
    CapsuleComponent->SetCollisionProfileName(TEXT("CustomProfileName"));
    
    ReadOnlyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReadOnlyStaticMesh"));
    ReadOnlyStaticMesh->SetupAttachment(RootComponent);
}

void AMyPawn::BeginPlay()
{
    Super::BeginPlay();
  
    if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
        
        if(UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            InputLocalPlayerSubsystem->AddMappingContext(InputMappingContext, 1);
        }
    }
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if(UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
        Input->BindAction(InputActionZoom, ETriggerEvent::Triggered, this, &ThisClass::InputZoom);
        Input->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
        Input->BindAction(InputActionIncreaseScale, ETriggerEvent::Started, this, &ThisClass::IncreaseScale);
        Input->BindAction(InputActionDecreaseScale, ETriggerEvent::Started, this, &ThisClass::DecreaseScale);
        Input->BindAction(InputActionSpawnProjectile, ETriggerEvent::Started, this, &ThisClass::SpawnProjectile);
        Input->BindAction(InputActionRotateProjectile, ETriggerEvent::Triggered, this, &ThisClass::RotateLastProjectile);
    }
}

void AMyPawn::InputMove(const FInputActionValue& InputActionValue)
{
    const FVector2D& MovementVector = InputActionValue.Get<FVector2D>();
    
    FVector NewLocation = GetActorLocation();

    NewLocation += GetActorForwardVector() * MovementVector.Y;

    NewLocation += GetActorRightVector() * MovementVector.X;



    SetActorLocation(NewLocation, true);
}

void AMyPawn::InputZoom(const FInputActionValue& InputActionValue)

{

    float ZoomValue = InputActionValue.Get<float>();



    float NewTargetArmLength = SpringArmComponent->TargetArmLength + ZoomValue;

    SpringArmComponent->TargetArmLength = FMath::Clamp(NewTargetArmLength, 200, 500);

}

void AMyPawn::InputLook(const FInputActionValue& InputActionValue)

{

    FVector2D LookAxisVector=InputActionValue.Get<FVector2D>();



    AddControllerYawInput(LookAxisVector.X);

    AddControllerPitchInput(LookAxisVector.Y);

}

void AMyPawn::IncreaseScale()
{
    CurrentScale = FMath::Clamp(CurrentScale + 0.25f, 0.5f, 2.0f);
    SetActorScale3D(FVector(CurrentScale, CurrentScale, CurrentScale));
}

void AMyPawn::DecreaseScale()
{
    CurrentScale = FMath::Clamp(CurrentScale - 0.25f, 0.5f, 2.0f);
    SetActorScale3D(FVector(CurrentScale, CurrentScale, CurrentScale));
}

void AMyPawn::SpawnProjectile()
{
    if (!ProjectileClass) return;
    
    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
    FRotator SpawnRotation = GetActorRotation();
    
    LastSpawnedProjectile = GetWorld()->SpawnActor<AAProjectile>(
        ProjectileClass,
        SpawnLocation,
        SpawnRotation
    );
    
}

void AMyPawn::RotateLastProjectile(const FInputActionValue& InputActionValue)
{
    LastSpawnedProjectile->RotateProjectile(5.0f);
}

