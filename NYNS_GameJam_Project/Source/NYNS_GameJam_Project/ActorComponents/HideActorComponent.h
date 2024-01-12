// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UHideActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHideActorComponent();

	UPROPERTY(VisibleAnywhere)
	bool hasPhysicsEnabled = false;;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	void Hide();
	void UpdateHasPhysicsEnabled(bool _value);
	UFUNCTION(BlueprintCallable)
	bool GetHasPhysicsEnabled() { return hasPhysicsEnabled; }

		
};
