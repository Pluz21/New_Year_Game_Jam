// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

	UPROPERTY(EditAnywhere)
	FRotator rotationOffset = FRotator(0,140,0);
	UPROPERTY(EditAnywhere)
	FRotator initialRotation = FRotator(0);
	UPROPERTY(EditAnywhere)
	bool canRotate = false;
	UPROPERTY(EditAnywhere)
	float rotatingTime = 1.f;
	UPROPERTY(VisibleAnywhere)
	float maxRotateDistanceAllowed = 2.5;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();

	UFUNCTION()
	void SetCanRotate(bool _value) { canRotate = _value; }
	UFUNCTION()
	void Rotate();
	UFUNCTION()
	bool CheckRotateDistance();
		
};
