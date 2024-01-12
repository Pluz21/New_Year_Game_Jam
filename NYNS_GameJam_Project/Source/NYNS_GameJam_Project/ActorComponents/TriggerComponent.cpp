// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/TriggerComponent.h"
#include <Kismet/GameplayStatics.h>

#include "NYNS_GameJam_Project/ActorComponents/RevealHiddenComponent.h"
#include <NYNS_GameJam_Project/Actors/NYNS_GameJam_ProjectCharacter.h>

#include "GrabberComponent.h"
#include "MoverComponent.h"
#include <Components/BoxComponent.h>
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
	
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UTriggerComponent::Init()
{
	if (GetOwner())
	{
		revealHiddenCompo = 
			GetOwner()->GetComponentByClass<URevealHiddenComponent>();

	}
	InitEvents();
}

void UTriggerComponent::InitEvents()
{
	if (GetOwner())
	{
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UTriggerComponent::ManageOverlap);

	}
	onSnap.AddDynamic(this, &UTriggerComponent::HandleSnap);
	onSnap.AddDynamic(this, &UTriggerComponent::PlaySound);
	onSnap.AddDynamic(this, &UTriggerComponent::HandleReveal);
	

}


void UTriggerComponent::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	if (!_overlapped || !_overlap)return;
	UE_LOG(LogTemp, Warning, TEXT("Overlappin with : %s"), *_overlap->GetName());
	SnapTarget(_overlap);
}

void UTriggerComponent::SnapTarget(AActor* _actorToSnap)
{
	if (!_actorToSnap)return;

	UPrimitiveComponent* _primitiveCompo = _actorToSnap->
		GetComponentByClass<UPrimitiveComponent>();
	if (!_primitiveCompo)return;
	FAttachmentTransformRules _worldTransform = FAttachmentTransformRules::KeepRelativeTransform;
	FAttachmentTransformRules _snap = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	FAttachmentTransformRules _snapScale = FAttachmentTransformRules::SnapToTargetIncludingScale;


	_primitiveCompo->SetSimulatePhysics(false);	
	_actorToSnap->AttachToComponent(GetOwner()->
		GetComponentByClass<UBoxComponent>(), _snap);

		ANYNS_GameJam_ProjectCharacter* _playerRef = 
			Cast<ANYNS_GameJam_ProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	UGrabberComponent* _grabberCompo = _playerRef->GetComponentByClass<UGrabberComponent>();
	if (!_grabberCompo)return;
		_grabberCompo->Release();
		snappedActor = _actorToSnap;
	onSnap.Broadcast();
}

void UTriggerComponent::HandleSnap()
{
	int _size = doorsToOpen.Num();
	for (int i = 0; i < _size; i++)
	{
		UMoverComponent* _moveCompo =
			doorsToOpen[i]->GetComponentByClass<UMoverComponent>();
		if (!_moveCompo)return;
		_moveCompo->SetCanRotate(true);
	}
}

void UTriggerComponent::PlaySound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), snapSound);

}

void UTriggerComponent::HandleReveal()
{

	if (revealHiddenCompo)
	{
		revealHiddenCompo->GetOnConditionToRevealIsMet().Broadcast();
	}
}

