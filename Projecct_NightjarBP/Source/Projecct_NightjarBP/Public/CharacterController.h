// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"	
#include "CharacterController.generated.h"


UCLASS()
class PROJECCT_NIGHTJARBP_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Actions

	void MoveRight(float value);
	void MoveUp(float value);
	void MeleeAttack();
	void GrabEnemy();
	void ThrowEnemy();
	void Dash();
	void Jump();
	void StopJumping();



	//Health Management
	void TakeDamage(float damageAmount);
	void Die();

	//Propreties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"));
	bool isGrabbingEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"));
	AActor* GrabbedEnemy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"));
	float DashDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"));
	float DashCoolDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"));
	bool bCanDash;

	//Timers
	FTimerHandle DashCooldownTimerHandle;
	
	//Helper functions
	void ResetDash();

	// Camera components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent*CameraBoom;

	//Camera component 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent*TopDownCameraComponent;

	// Rotation properties
	FRotator TargetRotation;
	float RotationSpeed;
	FVector CurrentDirection;
};
