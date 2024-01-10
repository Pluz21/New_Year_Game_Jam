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
	onValidTargetHit.AddDynamic(this, &UGrabberComponent::Grab);

}

void UGrabberComponent::FindTargetInReach()
{
	FHitResult _hitResult;
	FVector _ownerLocation = GetOwner()->GetActorLocation();
	FVector _cameraNormalDirection = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();

	FVector _targetLocation = _ownerLocation + _cameraNormalDirection * maxGrabDistance;

	FQuat _ownerQuat = GetOwner()->GetActorQuat();
	FRotator _ownerRotation = GetOwner()->GetActorRotation();
	FCollisionShape _sphere = FCollisionShape::MakeSphere(grabRadius);
	DrawDebugSphere(GetWorld(), _targetLocation,
		_sphere.GetSphereRadius(), 12, FColor::Magenta, false, 1, 0, 3);
	
	FCollisionQueryParams _customParams;
	_customParams.AddIgnoredActor(GetOwner());
	//ECollisionChannel::ECC_EngineTraceChannel1
	bool _hit = GetWorld()->SweepSingleByChannel( _hitResult, _ownerLocation, // might need to change for more accurate grabbing linetrace
		_targetLocation,
		FQuat::Identity, ECC_GameTraceChannel2,
		_sphere, _customParams);
	if (!_hit)return;
	DrawDebugPoint(GetWorld(), _hitResult.ImpactPoint, 20, FColor::Cyan, false, 5, 0);
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *_hitResult.GetActor()->GetName());

	targetLocation = _targetLocation;
	AActor* _actorHit = _hitResult.GetActor();
	actorHit = _actorHit;
	onValidTargetHit.Broadcast(_hit,_hitResult);
	hitResult = _hitResult;
	hit = _hit;
	


}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandleComponent()
{
	UPhysicsHandleComponent* _physicsHandleComponent = GetOwner()->
		GetComponentByClass<UPhysicsHandleComponent>();
	return _physicsHandleComponent;
}

void UGrabberComponent::Grab(bool _hit, FHitResult _hitResult)
{

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
}





void UGrabberComponent::Hold()
{
	if (!isGrabbing)return;
	if (physicsHandle && physicsHandle->GetGrabbedComponent())
	{

		FVector _ownerLocation = GetOwner()->GetActorLocation();
		FVector _cameraNormalDirection = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();
		//FVector _targetLocation = _ownerLocation + _cameraNormalDirection * holdDistance;
		_ownerLocation += FVector(0, 0, holdHeight);
		FVector _targetLocation = _ownerLocation + _cameraNormalDirection * holdDistance;//+ FVector(0, 100, 0);
		physicsHandle->SetTargetLocationAndRotation(_targetLocation,
			GetOwner()->GetActorRotation());
		DrawDebugSphere(GetWorld(), _targetLocation, 20, 10, FColor::Blue);
		SetIsHolding(true);
	}
}

void UGrabberComponent::Release()
{
	if (physicsHandle->GetGrabbedComponent() && isGrabbing == true)
	{
		UPrimitiveComponent* _grabbedComponent = physicsHandle->GetGrabbedComponent();
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* _heldActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		_grabbedComponent->SetSimulatePhysics(true);
		physicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("Releasing and Removing tag from %s"), *_heldActor->GetName());
		SetIsGrabbing();
	}

}

void UGrabberComponent::SetIsGrabbing()
{
	isGrabbing = !isGrabbing;
	if(!isGrabbing)
		SetIsHolding(false);

	UE_LOG(LogTemp, Warning, TEXT("is grabbing : %d"), isGrabbing);

}

void UGrabberComponent::SetIsHolding(bool _value)
{
	isHolding = _value;
}

