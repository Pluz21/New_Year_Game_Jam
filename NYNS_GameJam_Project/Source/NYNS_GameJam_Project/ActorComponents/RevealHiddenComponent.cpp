// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/RevealHiddenComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URevealHiddenComponent::URevealHiddenComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	
}



void URevealHiddenComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}


// Called every frame
void URevealHiddenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//RevealHidden();
	// ...
}

void URevealHiddenComponent::Init()
{
	onConditionToRevealIsMet.AddDynamic(this, &URevealHiddenComponent::RevealHidden);
	onReveal.AddDynamic(this, &URevealHiddenComponent::PlayRevealSound);
}



void URevealHiddenComponent::RevealHidden()
{
	//if (!canReveal)return;
	UE_LOG(LogTemp, Warning, TEXT("Reveal Hidden Called from RevealHiddenComponent"));
	if (allHiddenActors.Num() <= 0)return;
	int _sizeI = allHiddenActors.Num();
	for (int i = 0; i < _sizeI; i++)
	{
		if (!allHiddenActors[i])return;
		TArray<UPrimitiveComponent*> _allComponents;
		allHiddenActors[i]->GetComponents<UPrimitiveComponent>(_allComponents);
		if (_allComponents.Num() <= 0)return;
		int _sizeJ = _allComponents.Num();
		for (int j = 0; j < _sizeJ; j++)
		{

			if (_allComponents[j] == nullptr)continue;
			_allComponents[j]->SetVisibility(true, true);
			_allComponents[j]->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
		/*UPrimitiveComponent* _primitiveToReveal = allHiddenActors[j]->
			GetComponentByClass<UPrimitiveComponent>();
		_primitiveToReveal->SetVisibility(true, true);
		_primitiveToReveal->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);*/
		//allHiddenActors[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//UStaticMeshComponent* _meshCompo = allHiddenActors[i]->
		//	GetComponentByClass<UStaticMeshComponent>();
		//if (!_meshCompo) return;
		//_meshCompo->SetVisibility(true, true);
		//allHiddenActors[i]->GetComponentByClass<UStaticMeshComponent>()->
		//	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

	}
		onReveal.Broadcast();
}

void URevealHiddenComponent::PlayRevealSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), revealSound);

}

