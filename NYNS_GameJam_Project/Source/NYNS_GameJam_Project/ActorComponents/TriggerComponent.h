// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <NYNS_GameJam_Project/Actors/Door.h>
#include "TriggerComponent.generated.h"

class URevealHiddenComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UTriggerComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSnapEvent);
	UPROPERTY(BlueprintAssignable)
	FSnapEvent onSnap;

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TObjectPtr<URevealHiddenComponent> revealHiddenCompo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<ADoor*> doorsToOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TObjectPtr<USoundBase> snapSound;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	bool shouldDestroyAfterOverlap = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TObjectPtr<AActor> snappedActor;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	bool canSnap = true;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init();
	void InitEvents();
	UFUNCTION()
	void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	UFUNCTION(BlueprintCallable)
	void SnapTarget(AActor* _actorToSnap);
	
	UFUNCTION()
	void HandleSnap();
	UFUNCTION()
	void PlaySound();

	//Other interactions
	UFUNCTION()
	void HandleReveal();
	
	FSnapEvent& OnSnap() { return onSnap; }


};
