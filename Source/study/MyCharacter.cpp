#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractableInterface.h"
#include "AProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "MenuWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bInheritPitch = true;
    SpringArmComponent->bInheritYaw = true;
    SpringArmComponent->bInheritRoll = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    WidgetComponent->SetupAttachment(RootComponent);
    WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
    WidgetComponent->Mobility = EComponentMobility::Movable;

    ReadOnlyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReadOnlyStaticMesh"));
    ReadOnlyStaticMesh->SetupAttachment(RootComponent);
    ReadOnlyStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsystem->AddMappingContext(InputMappingContext, 1);
            }
        }
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
        Input->BindAction(InputActionMove, ETriggerEvent::Completed, this, &ThisClass::InputMoveCompleted);
        Input->BindAction(InputActionZoom, ETriggerEvent::Triggered, this, &ThisClass::InputZoom);
        Input->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
        Input->BindAction(InputActionLook, ETriggerEvent::Completed, this, &ThisClass::LookCompleted);
        Input->BindAction(InputActionIncreaseScale, ETriggerEvent::Started, this, &ThisClass::IncreaseScale);
        Input->BindAction(InputActionDecreaseScale, ETriggerEvent::Started, this, &ThisClass::DecreaseScale);
        Input->BindAction(InputActionSpawnProjectile, ETriggerEvent::Started, this, &ThisClass::SpawnProjectile);
        Input->BindAction(InputActionRotateProjectile, ETriggerEvent::Triggered, this, &ThisClass::RotateLastProjectile);
        Input->BindAction(InputActionLineTrace, ETriggerEvent::Started, this, &ThisClass::PerformLineTrace);
        Input->BindAction(InputActionInteract, ETriggerEvent::Started, this, &ThisClass::InteractWithAllLights);
        Input->BindAction(InputActionDestroy, ETriggerEvent::Started, this, &ThisClass::DestroyAllScalableActors);
        Input->BindAction(InputActionPause, ETriggerEvent::Started, this, &ThisClass::TogglePause);
    }
}

void AMyCharacter::InputMove(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    ForwardInputValue = MovementVector.Y;
    RightInputValue = MovementVector.X;

    if (Controller)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void AMyCharacter::InputMoveCompleted(const FInputActionValue& Value)
{
    ForwardInputValue = 0.0f;
    RightInputValue = 0.0f;
}

void AMyCharacter::InputZoom(const FInputActionValue& Value)
{
    float ZoomValue = Value.Get<float>();
    float NewLength = SpringArmComponent->TargetArmLength + ZoomValue;
    SpringArmComponent->TargetArmLength = FMath::Clamp(NewLength, 200.0f, 500.0f);
}

void AMyCharacter::InputLook(const FInputActionValue& Value)
{
    const FVector2D LookVector = Value.Get<FVector2D>();
    AddControllerYawInput(LookVector.X);
    AddControllerPitchInput(LookVector.Y);
}

void AMyCharacter::LookCompleted(const FInputActionValue& Value)
{
}

void AMyCharacter::IncreaseScale()
{
    CurrentScale = FMath::Clamp(CurrentScale + 0.25f, 0.5f, 2.0f);
    SetActorScale3D(FVector(CurrentScale));
}

void AMyCharacter::DecreaseScale()
{
    CurrentScale = FMath::Clamp(CurrentScale - 0.25f, 0.5f, 2.0f);
    SetActorScale3D(FVector(CurrentScale));
}

void AMyCharacter::SpawnProjectile()
{
    if (!ProjectileClass) return;

    FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
    FRotator SpawnRotation = GetActorRotation();

    LastSpawnedProjectile = GetWorld()->SpawnActor<AAProjectile>(
        ProjectileClass, SpawnLocation, SpawnRotation);
}

void AMyCharacter::RotateLastProjectile(const FInputActionValue& Value)
{
    if (LastSpawnedProjectile)
    {
        LastSpawnedProjectile->RotateProjectile(5.0f);
    }
}

void AMyCharacter::PerformLineTrace()
{
    if (!CameraComponent) return;

    FVector Start = CameraComponent->GetComponentLocation();
    FVector End = Start + (CameraComponent->GetForwardVector() * 10000.0f);

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    TArray<FHitResult> HitResults;

    UKismetSystemLibrary::LineTraceMulti(
        this, Start, End,
        UEngineTypes::ConvertToTraceType(ECC_Visibility),
        false, ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitResults, true,
        FLinearColor::Red, FLinearColor::Green, 5.0f);

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

void AMyCharacter::InteractWithAllLights()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithInterface(
        GetWorld(), UInteractableInterface::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (Actor && Actor->Implements<UInteractableInterface>())
        {
            IInteractableInterface::Execute_OnInteract(Actor);
        }
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
            FString::Printf(TEXT("Interacted with %d actors!"), FoundActors.Num()));
    }
}

void AMyCharacter::DestroyAllScalableActors()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
            TEXT("Broadcasting destroy event!"));
    }
    OnDestroyActors.Broadcast();
}

void AMyCharacter::TogglePause()
{
    if (!PauseMenuClass) return;

    if (!PauseMenuInstance)
    {
        APlayerController* PC = Cast<APlayerController>(GetController());
        if (!PC) return;
        PauseMenuInstance = CreateWidget<UMenuWidget>(PC, PauseMenuClass);
        PauseMenuInstance->AddToViewport();
    }

    bool bIsPaused = UGameplayStatics::IsGamePaused(GetWorld());

    if (bIsPaused)
    {
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        PauseMenuInstance->SetVisibility(ESlateVisibility::Hidden);
        if (APlayerController* PC = Cast<APlayerController>(GetController()))
        {
            PC->SetShowMouseCursor(false);
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
    else
    {
        UGameplayStatics::SetGamePaused(GetWorld(), true);
        PauseMenuInstance->SetVisibility(ESlateVisibility::Visible);
        if (APlayerController* PC = Cast<APlayerController>(GetController()))
        {
            PC->SetShowMouseCursor(true);
            PC->SetInputMode(FInputModeUIOnly());
        }
    }
}