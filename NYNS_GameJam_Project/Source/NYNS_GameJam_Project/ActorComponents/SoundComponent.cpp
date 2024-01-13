// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/SoundComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "HideActorComponent.h"
#include "RevealHiddenComponent.h"


// Sets default values for this component's properties
USoundComponent::USoundComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USoundComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void USoundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void USoundComponent::Init()
{
	if (!GetOwner())return;
	ownerRef = GetOwner();
	CheckHasHideActorComponent();
	UAudioComponent* _audioComponent = ownerRef->GetComponentByClass<UAudioComponent>();
	USoundBase* _soundBase = _audioComponent->Sound;
	soundToPlay = _soundBase;
	soundAudioComponent= _audioComponent;
	_audioComponent->DestroyComponent();
	//staticSound = _staticSoundBase;
	//staticSoundAudioComponent = _audioStaticComponent;


	PlaySoundLogic();
	//if (!staticSound)return;

	UE_LOG(LogTemp, Warning, TEXT("Initi soundocmpo"));

}

void USoundComponent::PlaySoundLogic()
{
	if (!canPlaySound)return;
	if (!soundToPlay)return;
	if (canDelaySound)	
	{
		//if (canAddStatic)
		//{
			//GetWorld()->GetTimerManager().SetTimer(staticSoundDelayHandler, this, &USoundComponent::PlayStatic, soundDelay, false);
			//UE_LOG(LogTemp, Warning, TEXT("Called Static timer"));

				

		//}
		
		GetWorld()->GetTimerManager().SetTimer(soundDelayHandler, this, &USoundComponent::PlaySoundInWorld, soundDelay, false);
		UE_LOG(LogTemp, Warning, TEXT("Called regular Sound timer"));

	}
	//PlaySoundInWorld();
}

void USoundComponent::PlaySoundInWorld()
{
	
	 UGameplayStatics::PlaySound2D(GetWorld(), soundToPlay);


}
void USoundComponent::PlayStatic()
{
	////UGameplayStatics::PlaySound2D(GetWorld(), staticSound, 1.0f, 1.0f, 0.0f, nullptr, true);
	//float _soundDuration = soundToPlay->Duration;
	//GetWorld()->GetTimerManager().SetTimer(soundDelayHandler, this, &USoundComponent::StopStaticSound, _soundDuration-1 , true);
}
void USoundComponent::CheckHasHideActorComponent()

{
	UHideActorComponent* _hideCompo = GetOwner()->GetComponentByClass<UHideActorComponent>();
	if (_hideCompo)
	{
		canPlaySound = false;
	}
}

void USoundComponent::StopStaticSound()
{	
	//if (!staticSoundAudioComponent)return;
	UE_LOG(LogTemp, Warning, TEXT("Stop static called"));

}







