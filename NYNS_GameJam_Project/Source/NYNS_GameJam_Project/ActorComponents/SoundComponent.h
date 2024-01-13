// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYNS_GAMEJAM_PROJECT_API USoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoundComponent();
	UPROPERTY()
	TObjectPtr<AActor> ownerRef;

	UPROPERTY()
	TObjectPtr<USoundBase> soundToPlay;
	//UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Sound Settings")
	//TObjectPtr<USoundBase> staticSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent> soundAudioComponent;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Sound Settings")
	//TObjectPtr<UAudioComponent> staticSoundAudioComponent;

	UPROPERTY()
	FTimerHandle soundDelayHandler;
	UPROPERTY()
	FTimerHandle staticSoundDelayHandler;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Sound Settings")
	bool canDelaySound = false;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Sound Settings")
	//bool canAddStatic = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Sound Settings", meta = (EditCondition = "!playSoundWorld"))
	bool canPlaySound = true;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100"), meta = (EditCondition = "canAddStatic"), Category = "Sound Settings")
	//float staticVolume = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.5", ClampMax = "100"), meta = (EditCondition = "canDelaySound"), Category = "Sound Settings")
	float soundDelay = 0;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	void PlaySoundLogic();
	void PlaySoundInWorld();
	void PlayStatic();
	void SetCanPlaySound(bool _value) {canPlaySound = _value; }
	void CheckHasHideActorComponent();
	void StopStaticSound();

};
