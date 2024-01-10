// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "GrabberComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API UGrabberComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValidTargetHitEvent, bool, _hit,FHitResult, _hitResult);

	UPROPERTY(BlueprintAssignable)
	FValidTargetHitEvent onValidTargetHit;

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
	TObjectPtr<AActor> actorHit = nullptr;
	UPROPERTY(VisibleAnywhere)
	FVector targetLocation = FVector(0);
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPhysicsHandleComponent> physicsHandle;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPrimitiveComponent> hitComponent;
	UPROPERTY(VisibleAnywhere)
	FHitResult hitResult;
	UPROPERTY(VisibleAnywhere)
	bool hit = false;;
	UPROPERTY(VisibleAnywhere)
	bool isHolding = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init();
	UFUNCTION(BlueprintCallable)
	void FindTargetInReach();
	UPhysicsHandleComponent* GetPhysicsHandleComponent();
	UFUNCTION(BlueprintCallable)
	void Grab(bool _hit,FHitResult _hitResult);
	void Hold();
	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void SetIsGrabbing();
	UFUNCTION(BlueprintCallable)
	void SetIsHolding(bool _value);
	UFUNCTION()
	bool GetHitBool() { return hit; }
	UFUNCTION()
	FHitResult GetHitResult() { return hitResult; }
		
};
