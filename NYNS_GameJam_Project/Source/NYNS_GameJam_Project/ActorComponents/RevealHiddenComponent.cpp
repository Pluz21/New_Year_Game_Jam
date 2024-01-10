// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/RevealHiddenComponent.h"
#include "Kismet/GameplayStatics.h"
#include <Components/LightComponentBase.h>

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
	onReveal.AddDynamic(this, &URevealHiddenComponent::DestroyActor);
}



void URevealHiddenComponent::RevealHidden()
{
	//if (!canReveal)return;
	UE_LOG(LogTemp, Warning, TEXT("Reveal Hidden Called from RevealHiddenComponent"));
	if (allHiddenActors.Num() <= 0)return;
	int _sizeI = allHiddenActors.Num();
	for (int i = 0; i < _sizeI; i++)
	{
		if (!allHiddenActors[i])continue;
		TArray<USceneComponent*> _allComponents;
		allHiddenActors[i]->GetComponents<USceneComponent>(_allComponents);
	
		int _size = _allComponents.Num();
		UE_LOG(LogTemp, Warning, TEXT("%f, all compo size = "), _size);
		if (_allComponents.Num() <= 0)continue;
		for (int j = 0; j < _size; j++)
		{

			if (_allComponents[j] == nullptr)continue;
			_allComponents[j]->SetVisibility(true, true);
			UPrimitiveComponent* _meshCompo = Cast<UPrimitiveComponent>(_allComponents[j]);
			if(_meshCompo)
				_meshCompo->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
		}
		}
		
		onReveal.Broadcast();
}

void URevealHiddenComponent::PlayRevealSound()
{
	if(canPlaySound)
	UGameplayStatics::PlaySound2D(GetWorld(), revealSound);
	canPlaySound = false;
}

void URevealHiddenComponent::DestroyActor()
{
	if (!shouldDestroyAfterReveal || !GetOwner())return;
		GetOwner()->Destroy();
}

