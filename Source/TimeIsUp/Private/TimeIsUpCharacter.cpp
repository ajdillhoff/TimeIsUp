// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TimeIsUpPrivatePCH.h"
#include "TimeIsUpCharacter.h"
#include "PaperFlipbookComponent.h"
#include "TimeIsUpPlayerController.h"

ATimeIsUpCharacter::ATimeIsUpCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	CapsuleComponent->SetCapsuleHalfHeight(96.0f);
	CapsuleComponent->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUseControllerViewRotation = false;
	CharacterMovement->bOrientRotationToMovement = false;

	// Configure character movement
	CharacterMovement->GravityScale = 2.0f;
	CharacterMovement->AirControl = 0.0f;
	CharacterMovement->JumpZVelocity = 1000.f;
	CharacterMovement->GroundFriction = 10.0f;
	CharacterMovement->MaxWalkSpeed = 1000.0f;
	CharacterMovement->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	CharacterMovement->bConstrainToPlane = true;
	CharacterMovement->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	CharacterMovement->bUseFlatBaseForFloorChecks = true;

	// Note: The reference to the RunningAnimation and IdleAnimation flipbooks to play on the Sprite component
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ATimeIsUpCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeed > 0.0f) ? RunningAnimation : IdleAnimation;

	Sprite->SetFlipbook(DesiredAnimation);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATimeIsUpCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAxis("MoveRight", this, &ATimeIsUpCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &ATimeIsUpCharacter::TouchStarted);
}

void ATimeIsUpCharacter::MoveRight(float Value)
{
	// Update animation to match the motion
	UpdateAnimation();

	// Set the rotation so that the character faces his direction of travel.
	if (Value < 0.0f)
	{
		Sprite->SetWorldRotation(FRotator(0.0, 180.0f, 0.0f));
	}
	else if (Value > 0.0f)
	{
		Sprite->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	}

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ATimeIsUpCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ATimeIsUpCharacter::OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
  {
    // We don't actually have any other actors, so we don't have to check for anything
    ATimeIsUpPlayerController *playerController = Cast<ATimeIsUpPlayerController>(this->Controller);
    
    if (playerController) {
      // Looks like we've got it m80
      playerController->coinCount++;
      UE_LOG(LogClass, Display, TEXT("Look like we've made it!"))
    }
  }
}
void ATimeIsUpCharacter::ReceiveHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalForce, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalForce, Hit);
  
  UE_LOG(LogClass, Display, TEXT("Look like we've made it!"))
  ATimeIsUpCharacter *otherCharacter = Cast<ATimeIsUpCharacter>(Other);
  if (otherCharacter) {
    otherCharacter->Destroy();
  }
}
