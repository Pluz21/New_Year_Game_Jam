// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/Actors/Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	moverCompo = CreateDefaultSubobject<UMoverComponent>("MoverCompo");
	 
	
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("MeshCompo");
	meshCompo->SetupAttachment(RootComponent);
	AddOwnedComponent(moverCompo);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

