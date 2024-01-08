// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/GrabberComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include <DrawDebugHelpers.h>

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Hold();

}

void UGrabberComponent::Init()
{
	physicsHandle = GetPhysicsHandleComponent();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("no physics handle found"));

	}

}

bool UGrabberComponent::FindTargetInReach(FHitResult& _hitResult)
{
	FVector _ownerLocation = GetOwner()->GetActorLocation();
	FVector _cameraNormalDirection = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();
	// Better for linetrace
	/*
	APawn* _pawnRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!_pawnRef)return;
	ADragon* _dragonRef = Cast<ADragon>(_pawnRef);
	if (!_dragonRef || !_dragonRef->baseGunRef)return;
	//_dragonRef->GetPawnViewLocation();
	FRotator CameraRotation;
	FVector _cameraForwardVector;
	FVector _spawnPointRef; // only used to get the rotation from GetPlayerViewPoint since it OUTs FVector and FRotator;

	FVector _spawnPointVector = _dragonRef->baseGunRef->materialChangerMesh->GetComponentLocation();
	_dragonRef->playerController->GetPlayerViewPoint(_spawnPointRef, CameraRotation);
	
	_cameraForwardVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::X);

	FVector _lookAtLocation = _spawnPointVector + (_cameraForwardVector * 10000);

	*/
	FVector _targetLocation = _ownerLocation + _cameraNormalDirection * maxGrabDistance;

	FQuat _ownerQuat = GetOwner()->GetActorQuat();
	FRotator _ownerRotation = GetOwner()->GetActorRotation();
	FCollisionShape _sphere = FCollisionShape::MakeSphere(grabRadius);
	DrawDebugSphere(GetWorld(), _targetLocation,
		_sphere.GetSphereRadius(), 12, FColor::Magenta, false, 1, 0, 3);
	
	FCollisionQueryParams _customParams;
	_customParams.AddIgnoredActor(GetOwner());
	//ECollisionChannel::ECC_EngineTraceChannel1

	bool _hit = GetWorld()->SweepSingleByChannel(_hitResult, _ownerLocation, // might need to change for more accurate grabbing linetrace
		_targetLocation,
		FQuat::Identity, ECC_GameTraceChannel2,
		_sphere, _customParams);
	if (!_hit)return false;
	DrawDebugPoint(GetWorld(), _hitResult.ImpactPoint, 20, FColor::Cyan, false, 5, 0);
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *_hitResult.GetActor()->GetName());

	targetLocation = _targetLocation;
	return _hit;



}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandleComponent()
{
	UPhysicsHandleComponent* _physicsHandleComponent = GetOwner()->
		GetComponentByClass<UPhysicsHandleComponent>();
	return _physicsHandleComponent;
}

void UGrabberComponent::Grab()
{

	FHitResult _hitResult;

	bool _hasHit = FindTargetInReach(_hitResult);
	hitResult = _hitResult;
	if (!_hasHit)
	{
		Release();

		return;
	}

	UPrimitiveComponent* _hitComponent = _hitResult.GetComponent();
	hitComponent = _hitComponent;
	_hitComponent->WakeAllRigidBodies();
	_hitComponent->SetSimulatePhysics(true);   // might need to be actor

	_hitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	physicsHandle->GrabComponentAtLocationWithRotation(
		_hitComponent, NAME_None,		// might need to be actor
		_hitResult.ImpactPoint,
		_hitComponent->GetComponentRotation());
	SetIsGrabbing();
	
	//onGrab.Broadcast(_hitResult.GetActor());
}

void UGrabberComponent::Hold()
{
	if (!isGrabbing)return;
	if (physicsHandle && physicsHandle->GetGrabbedComponent())
	{

		FVector _ownerLocation = GetOwner()->GetActorLocation();
		FVector _cameraNormalDirection = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();
		FVector _targetLocation = _ownerLocation + _cameraNormalDirection * holdDistance;

		physicsHandle->SetTargetLocationAndRotation(_targetLocation,
			GetOwner()->GetActorRotation());
		DrawDebugSphere(GetWorld(), _targetLocation, 20, 10, FColor::Blue);
	}
}

void UGrabberComponent::Release()
{
	if (physicsHandle->GetGrabbedComponent() && isGrabbing == true)
	{
		UPrimitiveComponent* _grabbedComponent = physicsHandle->GetGrabbedComponent();
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* _heldActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		_grabbedComponent->SetSimulatePhysics(false);
		physicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("Removing tag from %s"), *_heldActor->GetName());
		SetIsGrabbing();
	}

}

void UGrabberComponent::SetIsGrabbing()
{
	isGrabbing = !isGrabbing;
}

