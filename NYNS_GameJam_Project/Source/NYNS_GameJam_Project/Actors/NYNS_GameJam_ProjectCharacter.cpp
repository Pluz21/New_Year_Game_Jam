// Copyright Epic Games, Inc. All Rights Reserved.

#include "NYNS_GameJam_ProjectCharacter.h"
#include "NYNS_GameJam_ProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "NYNS_GameJam_Project/ActorComponents/GrabberComponent.h"

//////////////////////////////////////////////////////////////////////////
// ANYNS_GameJam_ProjectCharacter

ANYNS_GameJam_ProjectCharacter::ANYNS_GameJam_ProjectCharacter()
{
	//Custom Components
	grabberComponent = CreateDefaultSubobject<UGrabberComponent>(TEXT("GrabberComponent"));
	physicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");

	
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AddOwnedComponent(grabberComponent);
	AddOwnedComponent(physicsHandle);
}

void ANYNS_GameJam_ProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Init();
	

}


void ANYNS_GameJam_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANYNS_GameJam_ProjectCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANYNS_GameJam_ProjectCharacter::Look);
	
		// Grab
		EnhancedInputComponent->BindAction(grabInput, ETriggerEvent::Triggered, this, &ANYNS_GameJam_ProjectCharacter::Grab);
		EnhancedInputComponent->BindAction(grabInput, ETriggerEvent::Completed, this, &ANYNS_GameJam_ProjectCharacter::StopGrab);

		//Inspect
		EnhancedInputComponent->BindAction(inspectInput, ETriggerEvent::Triggered, this, &ANYNS_GameJam_ProjectCharacter::Inspect);
		EnhancedInputComponent->BindAction(inspectInput, ETriggerEvent::Completed, this, &ANYNS_GameJam_ProjectCharacter::Inspect);
		
	}
}

void ANYNS_GameJam_ProjectCharacter::Init()
{
	InitInputs();
}

void ANYNS_GameJam_ProjectCharacter::InitInputs()
{
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


void ANYNS_GameJam_ProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ANYNS_GameJam_ProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANYNS_GameJam_ProjectCharacter::Grab()
{
	if (!grabberComponent)return;
	if (grabberComponent->isGrabbing)
	{
		grabberComponent->Release();
	}
	else
	{
		grabberComponent->FindTargetInReach();
	}
}

void ANYNS_GameJam_ProjectCharacter::StopGrab()
{
}

void ANYNS_GameJam_ProjectCharacter::Inspect(const FInputActionValue& _value)
{
	//bool _trigger = _value.Get<bool>();
//UE_LOG(LogTemp, Warning, TEXT("Triggered inspect : %d"), _trigger);

	FHitResult HitResult;


	FVector StartLocation;
	FRotator PlayerRotation;
	Controller->GetPlayerViewPoint(StartLocation, PlayerRotation);

	FVector ForwardVector = PlayerRotation.Vector();
	FVector TargetLocation = StartLocation + ForwardVector * 200;

	TArray<AActor*> ToIgnore; // Declared as a member variable for the moment

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation, TargetLocation, ECC_GameTraceChannel2);

	if (bHit)
	{
		DrawDebugLine(GetWorld(), StartLocation,
			HitResult.ImpactPoint, FColor::Green, false, 2.0f, 0, 2.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(),
			StartLocation, TargetLocation, FColor::Red, false, 2.0f, 0, 2.0f);
	}


}

void ANYNS_GameJam_ProjectCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ANYNS_GameJam_ProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}