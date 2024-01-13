// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class UGameViewportClient;
/**
 * 
 */
UCLASS()
class NYNS_GAMEJAM_PROJECT_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<UGameViewportClient> gameViewPortClient = nullptr;
public:
    virtual void Init() override;

    UFUNCTION()
    virtual void BeginLoadingScreen(const FString& _mapName);
    UFUNCTION()
    virtual void EndLoadingScreen(UWorld* _inLoadedWorld);
	
    void AddWidget();
};
