// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class ANYNS_GameJam_ProjectCharacter;

enum class GameState
{
	NONE,
	PLAYING,
	PAUSED
};
UCLASS()
class NYNS_GAMEJAM_PROJECT_API UMainMenu : public UUserWidget
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuIsVisibleEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGamePausedEvent);
	UPROPERTY()
	FInitEvent onInit;
	UPROPERTY(BlueprintAssignable)
	FMenuIsVisibleEvent onMenuIsVisible;
	UPROPERTY()
	FGamePausedEvent onGamePaused;

	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ANYNS_GameJam_ProjectCharacter> playerRef = nullptr;
	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;
	//UPROPERTY()
	//TObjectPtr<UInputMappingContext> mappingContext;
public:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* widgetToHide;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UUserWidget> widgetToHideref;

	GameState currentState = GameState::NONE;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Init();
	UFUNCTION()
	void InitInput();

	UFUNCTION(BlueprintCallable)
	void SetActive();
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	UFUNCTION(BlueprintCallable)
	void DisplayCursor();
	UMainMenu* GetMainMenuWidget() { return this; }
	UFUNCTION(BlueprintCallable)
	void SetPlayerInputMode();
};
