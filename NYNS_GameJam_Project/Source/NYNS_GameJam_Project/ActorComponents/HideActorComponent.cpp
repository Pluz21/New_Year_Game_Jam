// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/HideActorComponent.h"

// Sets default values for this component's properties
UHideActorComponent::UHideActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHideActorComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UHideActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHideActorComponent::Init()
{
	Reveal();
}

void UHideActorComponent::Reveal()
{
	if (!GetOwner() || GetOwner()->GetComponentByClass<UStaticMeshComponent>() == nullptr)return;
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(false, true);
	UE_LOG(LogTemp, Warning, TEXT("called init inside HIDDEN ACTOR"));
	//GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);

}

