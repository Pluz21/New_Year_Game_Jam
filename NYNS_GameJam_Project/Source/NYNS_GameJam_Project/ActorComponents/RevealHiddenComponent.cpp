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

	// ...
}

void URevealHiddenComponent::Init()
{
	onConditionToRevealIsMet.AddDynamic(this, &URevealHiddenComponent::RevealHidden);
	onReveal.AddDynamic(this, &URevealHiddenComponent::PlayRevealSound);
}



void URevealHiddenComponent::RevealHidden()
{
	UE_LOG(LogTemp, Warning, TEXT("Reveal Hidden Called from RevealHiddenComponent"));
	if (allHiddenActors.Num() <= 0)return;
	int _size = allHiddenActors.Num();
	for (int i = 0; i < _size; i++)
	{
		if (allHiddenActors[i] == nullptr)continue;
		UStaticMeshComponent* _meshCompo = allHiddenActors[i]->
			GetComponentByClass<UStaticMeshComponent>();
		if (!_meshCompo) return;
		_meshCompo->SetVisibility(true, true);
		allHiddenActors[i]->GetComponentByClass<UStaticMeshComponent>()->
			SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		onReveal.Broadcast();
	}
}

void URevealHiddenComponent::PlayRevealSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), revealSound);

}

