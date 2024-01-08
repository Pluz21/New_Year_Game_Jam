// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NYNS_GameJam_Project/ActorComponents/MoverComponent.h>
#include "Door.generated.h"

UCLASS()
class NYNS_GAMEJAM_PROJECT_API ADoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoverComponent> moverCompo;
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
