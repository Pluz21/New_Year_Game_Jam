// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "GrabberComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UGrabberComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGrabEvent, AActor*, grabbedActor);

	UPROPERTY(BlueprintAssignable)
	FGrabEvent onGrab;

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();
	UPROPERTY(EditAnywhere, Category = "Grabber",meta = (ClampMin = "10", ClampMax = "100"))
	float grabRadius = 60;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grabber")
	bool isGrabbing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grabber", meta = (ClampMin = "30", ClampMax = "600"))
	float maxGrabDistance = 600;
	UPROPERTY(EditAnywhere, Category = "Grabber", meta = (ClampMin = "10", ClampMax = "1000"))
	float holdDistance = 200;
	UPROPERTY(EditAnywhere, Category = "Grabber", meta = (ClampMin = "10", ClampMax = "100"))
	float holdHeight = 50; //test for github
	UPROPERTY(VisibleAnywhere)
	FVector targetLocation = FVector(0);
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPhysicsHandleComponent> physicsHandle;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPrimitiveComponent> hitComponent;
	UPROPERTY(VisibleAnywhere)
	FHitResult hitResult;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init();

	bool FindTargetInReach(FHitResult& _hitResult);
	UPhysicsHandleComponent* GetPhysicsHandleComponent();
	UFUNCTION(BlueprintCallable)
	void Grab();
	void Hold();
	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void SetIsGrabbing();
		
};
