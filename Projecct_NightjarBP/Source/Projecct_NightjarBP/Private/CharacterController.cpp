// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // Rotation speed
    GetCharacterMovement()->GravityScale = 2.0f; // Gravity scale
    GetCharacterMovement()->AirControl = 0.80f; // Air control
    GetCharacterMovement()->JumpZVelocity = 600.0f; // Jump velocity
    GetCharacterMovement()->GroundFriction = 3.0f; // Ground friction
    GetCharacterMovement()->MaxWalkSpeed = 600.0f; // Walking speed
    GetCharacterMovement()->MaxFlySpeed = 600.0f; // Flying speed

    //Initialize health
    maxHealth = 5;
    Health = maxHealth;

    //Initialze dash propreties
    DashDistance = 600.0f;
    DashCoolDown = 1.0f;
    bCanDash = true;

    //Initialize grab properties
    isGrabbingEnemy = false;
    GrabbedEnemy = nullptr;

    //Initialize camera properties
    RotationSpeed = 100.0f;
    RotationSmoothness = 100.0f;
    LastRotation = FRotator(0.0f, 0.0f, 0.0f);

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
    CameraBoom->bDoCollisionTest = false; // Otherwise, characters behind us fling the camera forward
    CameraBoom->SetUsingAbsoluteRotation(true); // Enable to avoid camera rotating with character
    CameraBoom->SetWorldRotation(FRotator(-45.0f, 0.0f, 0.0f));
    //CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    //Create and attach a camera component
    //TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    //TopDownCameraComponent->SetupAttachment(RootComponent);
    //TopDownCameraComponent->SetRelativeLocation(FVector(-500.0f, 0.0f, 800.0f));
    //TopDownCameraComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    //TopDownCameraComponent->bUsePawnControlRotation = false;



    // Create a camera and attach to boom
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Smoothly interpolate to the target rotation if moving
    RotateCharacter(DeltaTime);
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterController::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &ACharacterController::MoveUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterController::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterController::StopJumping);
    
    PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ACharacterController::MeleeAttack);
    PlayerInputComponent->BindAction("GrabEnemy", IE_Pressed, this, &ACharacterController::GrabEnemy);
    PlayerInputComponent->BindAction("ThrowEnemy", IE_Pressed, this, &ACharacterController::ThrowEnemy);
    PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ACharacterController::Dash);

}

void ACharacterController::RotateCharacter(float DeltaTime) {
    FVector velocity = GetCharacterMovement()->Velocity;
    float speed = velocity.Length();

    // If speed is 0.0f, don't update rotation.
    // Since we get the rotation from velocity in the Z-axis, a null rotation would set up back facing forward.
    // Instead, we save the last valid rotation and update it on tick to avoid having the character face forward on input release
    if (speed != 0.0f && speed > RotationSmoothness) {
        FRotator CurrentRotation = GetActorRotation();
        FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, velocity.Rotation(), DeltaTime, RotationSpeed);
        // Updating the smooth rotation for Yaw while keeping current rotation for the other axes
        LastRotation = FRotator(CurrentRotation.Pitch, SmoothRotation.Yaw, CurrentRotation.Roll);
    }

    SetActorRotation(LastRotation);
}

void ACharacterController::MoveRight(float value) {
    //Move character right/left relative to camera
    if (Controller && value != 0.0f && Health != 0)
    {
        // Move the character
        CurrentDirection.Y = value;
        AddMovementInput(FVector::RightVector, value);

        // Determine the target rotation based on the input direction
        TargetRotation = value > 0.0f ? FRotator(0.0f, 90.0f, 0.0f) : FRotator(0.0f, -90.0f, 0.0f);
    }
    else
    {
        // Stop moving in the Y direction if no input
        CurrentDirection.Y = 0.0f;
    }
}

void ACharacterController::MoveUp(float value) {
    //Move character up/down relative to camera
    if (Controller && value != 0.0f && Health != 0)
    {
        // Move the character
        CurrentDirection.X = value;
        AddMovementInput(FVector::ForwardVector, value);

        // Determine the target rotation based on the input direction
        TargetRotation = value > 0.0f ? FRotator(0.0f, 0.0f, 0.0f) : FRotator(0.0f, 180.0f, 0.0f);
    }
    else
    {
        // Stop moving in the X direction if no input
        CurrentDirection.X = 0.0f;
    }
}

void ACharacterController::MeleeAttack() {
    
    UE_LOG(LogTemp, Warning, TEXT("MELEE ATTACK"));

    
}
void ACharacterController::GrabEnemy()
{
    if (!isGrabbingEnemy)
    {
        // Placeholder for grab logic, like checking for nearby enemies and grabbing one
        isGrabbingEnemy = true;
        UE_LOG(LogTemp, Warning, TEXT("Enemy Grabbed!"));
    }
}

// Function to handle throwing a grabbed enemy
void ACharacterController::ThrowEnemy()
{
    if (isGrabbingEnemy)
    {
        // Placeholder for throw logic, like launching the grabbed enemy
        isGrabbingEnemy = false;
        GrabbedEnemy = nullptr;
        UE_LOG(LogTemp, Warning, TEXT("Enemy Thrown!"));
    }
}

// Function to handle dash input
void ACharacterController::Dash()
{
    if (bCanDash)
    {
        FVector DashDirection = GetActorForwardVector();
        LaunchCharacter(DashDirection * DashDistance, true, true);
        bCanDash = false;

        // Start cooldown timer
        GetWorldTimerManager().SetTimer(DashCooldownTimerHandle, this, &ACharacterController::ResetDash, DashCoolDown, false);

        UE_LOG(LogTemp, Warning, TEXT("Dash!"));
    }
}

// Function to handle jump input
void ACharacterController::Jump() 
{
    ACharacter::Jump();
}

// Function to handle stop jumping input
void ACharacterController::StopJumping()
{
    ACharacter::StopJumping();
}

// Function to reset dash availability after cooldown
void ACharacterController::ResetDash()
{
    bCanDash = true;
}

// Function to handle taking damage
void ACharacterController::TakeDamage(int DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0)
    {
        Die();
    }
}

// Function to handle character death
void ACharacterController::Die()
{
    // Placeholder for death logic, like playing a death animation and removing the character from the game
    UE_LOG(LogTemp, Warning, TEXT("Character Died!"));
    //Destroy(); // Destroying the character would break the parent reference for the camera
}


