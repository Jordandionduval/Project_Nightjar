// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
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
    maxHealth = 100;
    Health = maxHealth;

    //Initialze dash propreties
    DashDistance = 600.0f;
    DashCoolDown = 1.0f;
    bCanDash = true;
    isGrabbingEnemy = false;
    GrabbedEnemy = nullptr;


    //Create and attach a camera component
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCameraComponent->SetupAttachment(RootComponent);
    TopDownCameraComponent->SetRelativeLocation(FVector(-500.0f, 0.0f, 800.0f));
    TopDownCameraComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
    TopDownCameraComponent->bUsePawnControlRotation = false;
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
void ACharacterController::MoveRight(float value) {
    //Move character right/left relative to camera
    AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
}

void ACharacterController::MoveUp(float value) {
    
    //Move Character up/down relative to camera
    AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
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
void ACharacterController::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        Die();
    }
}

// Function to handle character death
void ACharacterController::Die()
{
    // Placeholder for death logic, like playing a death animation and removing the character from the game
    UE_LOG(LogTemp, Warning, TEXT("Character Died!"));
    Destroy();
}


