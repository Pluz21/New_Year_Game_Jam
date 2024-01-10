// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideActorComponent.generated.h"
class URevealHiddenComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UHideActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHideActorComponent();
	UPROPERTY(EditAnywhere)
	TObjectPtr<URevealHiddenComponent> revealHiddenCompo;

	UPROPERTY(EditAnywhere)
	bool ignorePhysics = true;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	void Hide();
	UFUNCTION() void UpdateCollision(UPrimitiveComponent* _compoToUpdate);

		
};
