// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/HideActorComponent.h"
#include <Components/LightComponentBase.h>

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
	Hide();
	UE_LOG(LogTemp, Warning, TEXT("Initi hideactor"));

}

void UHideActorComponent::Hide()
{
	if (!GetOwner())return; //|| GetOwner()->GetComponentByClass<UStaticMeshComponent>() == nullptr)return;
	
	
	TArray<UPrimitiveComponent*> _allComponents;
	TArray<ULightComponentBase*> _allLightComponents;
	GetOwner()->GetComponents<UPrimitiveComponent>(_allComponents);
	GetOwner()->GetComponents<ULightComponentBase>(_allLightComponents);

	int _size = _allComponents.Num();
	for (int i = 0; i < _size; i++)
	{
		_allComponents[i]->SetVisibility(false, true);
		bool _isSimulatingPhysics = _allComponents[i]->IsSimulatingPhysics();
		UpdateHasPhysicsEnabled(_isSimulatingPhysics);
		if (_isSimulatingPhysics)
			_allComponents[i]->SetSimulatePhysics(false);
		_allComponents[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Warning, TEXT("Hidden %s"), *_allComponents[i]->GetName());

	}
	int _sizeLight = _allLightComponents.Num();
	for (int j = 0; j < _sizeLight; j++)
	{
		_allLightComponents[j]->SetVisibility(false, true);
		

	}
	
}

void UHideActorComponent::UpdateHasPhysicsEnabled(bool _value)
{
	hasPhysicsEnabled = _value;
}


