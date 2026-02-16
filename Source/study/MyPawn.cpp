#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AProjectile.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    
   
    
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    RootComponent = CapsuleComponent;  
    
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CapsuleComponent->SetCapsuleHalfHeight(90.0f);
    CapsuleComponent->SetCapsuleRadius(50.0f);
    
    CapsuleComponent->SetSimulatePhysics(false);   
    CapsuleComponent->BodyInstance.bLockXRotation = true;
    CapsuleComponent->BodyInstance.bLockYRotation = true;
    
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(RootComponent);
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    
    ReadOnlyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReadOnlyStaticMesh"));
    ReadOnlyStaticMesh->SetupAttachment(RootComponent);
    ReadOnlyStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
    
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;    
    bUseControllerRotationRoll = false;
    
    if (SpringArmComponent)
    {
        SpringArmComponent->bUsePawnControlRotation = true;   
        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = false;
    }
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
        Input->BindAction(InputActionLineTrace, ETriggerEvent::Started, this, &ThisClass::PerformLineTrace);
    }
}

void AMyPawn::InputMove(const FInputActionValue& InputActionValue)
{
    const FVector2D& MovementVector = InputActionValue.Get<FVector2D>();
    
    FVector CurrentLocation = GetActorLocation();
    FVector DesiredMove = FVector::ZeroVector;
    
    DesiredMove += GetActorForwardVector() * MovementVector.Y * 10.0f;  
    
    DesiredMove += GetActorRightVector() * MovementVector.X * 10.0f;
    
    FVector NewLocation = CurrentLocation + DesiredMove;
    
    FHitResult HitResult;
    SetActorLocation(NewLocation, true, &HitResult, ETeleportType::None);
    
    if (HitResult.bBlockingHit)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Orange, 
                TEXT("Pawn is blocked!"));
        }
    }
}

void AMyPawn::InputZoom(const FInputActionValue& InputActionValue)

{

    float ZoomValue = InputActionValue.Get<float>();

    float NewTargetArmLength = SpringArmComponent->TargetArmLength + ZoomValue;

    SpringArmComponent->TargetArmLength = FMath::Clamp(NewTargetArmLength, 200, 500);

}

void AMyPawn::InputLook(const FInputActionValue& InputActionValue)
{
    const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
    
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


void AMyPawn::PerformLineTrace()
{
    if (!CameraComponent) return;
    
    FVector Start = CameraComponent->GetComponentLocation();
    FVector End = Start + (CameraComponent->GetForwardVector() * 10000.0f);
    
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);
    
    TArray<FHitResult> HitResults;
    
    bool bHit = UKismetSystemLibrary::LineTraceMulti(
        this,                                
        Start,
        End,
        UEngineTypes::ConvertToTraceType(ECC_Visibility),
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitResults,
        true,
        FLinearColor::Red,
        FLinearColor::Green,
        5.0f
    );
    
    for (const FHitResult& Hit : HitResults)
    {
        if (Hit.GetActor() && GEngine)
        {
            FString Type = Hit.bBlockingHit ? TEXT("Block") : TEXT("Overlap");
            FColor Color = Hit.bBlockingHit ? FColor::Red : FColor::Green;
            
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color,
                FString::Printf(TEXT("%s | %s"), *Hit.GetActor()->GetName(), *Type));
        }
    }
}