// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/ActorComponents/MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckRotateDistance();
	Rotate();
	// ...
}

void UMoverComponent::Init()
{
	if (!GetOwner())return;
	initialRotation = GetOwner()->GetComponentByClass<UStaticMeshComponent>()->GetSocketRotation("StaticMesh");
	//not optimal since using string
}

void UMoverComponent::Rotate()
{
	if (!GetOwner() || !canRotate)return;
	if (CheckRotateDistance())
	{

	FRotator _currentRotation = GetOwner()->GetActorRotation();
	FRotator _targetRotation = initialRotation + rotationOffset;
	float _rotationInterpSpeed = FMath::Abs(FRotator::NormalizeAxis(_targetRotation.Yaw - _currentRotation.Yaw)) / rotatingTime;
	//float _rotationInterpSpeed = FMath::Sign(_targetRotation.Yaw - _currentRotation.Yaw) * rotatingTime;

	FRotator _newRotation = FMath::RInterpConstantTo(_currentRotation, _targetRotation, GetWorld()->DeltaTimeSeconds, _rotationInterpSpeed);

	/*GetOwner()->GetComponentByClass<UStaticMeshComponent>()
		->AddWorldRotation(_newRotation);*/
	GetOwner()->SetActorRotation(_newRotation);
	}


	/*GetOwner()->GetComponentByClass<UStaticMeshComponent>()
		->AddWorldRotation(FRotator(0, 90, 0));*/
}

bool UMoverComponent::CheckRotateDistance()
{
	FVector _currentMeshRotationVector =GetOwner()->
		GetComponentByClass<UStaticMeshComponent>()->GetComponentRotation().Vector();
		float _dist = FVector::Dist(initialRotation.Vector(), _currentMeshRotationVector);
		if (_dist >= maxRotateDistanceAllowed)
		{
			return false;
		}
		return true;
}

