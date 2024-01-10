// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RevealHiddenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API URevealHiddenComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConditionToRevealIsMet);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRevealEvent);

	UPROPERTY(BlueprintAssignable)
	FConditionToRevealIsMet onConditionToRevealIsMet;
	UPROPERTY(BlueprintAssignable)
	FRevealEvent onReveal;


	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URevealHiddenComponent();

	UPROPERTY(EditAnywhere, Category = "Reveal Hidden")
	TArray<AActor*> allHiddenActors;

	UPROPERTY(EditAnywhere, Category = "Reveal Hidden")
	TObjectPtr<USoundBase> revealSound;

	UPROPERTY()
	bool canPlaySound = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reveal Hidden")
	bool shouldDestroyAfterReveal = true;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	UFUNCTION(BlueprintCallable)
	void RevealHidden();
	UFUNCTION()
	void PlayRevealSound();
	FConditionToRevealIsMet& GetOnConditionToRevealIsMet() { return onConditionToRevealIsMet; }
	FRevealEvent& GetOnReveal() { return onReveal; }
	UFUNCTION()
	void DestroyActor();
		
};
