// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "MainMenu.h"
#include "NYNS_GameJam_Project/Actors/NYNS_GameJam_ProjectCharacter.h"
#include <Kismet/GameplayStatics.h>

void UMainMenu::NativeConstruct()
{
	Init();
	UE_LOG(LogTemp, Warning, TEXT("WidgetConstructorCalled"));
}

void UMainMenu::Init()
{
	playerRef = Cast<ANYNS_GameJam_ProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!playerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("failed playeref"));

	return;
	}
	if (playerRef->GetOnOpenedMenu().IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("bound onopenmenu event"));

		return;
	}
	playerRef->GetOnOpenedMenu().AddDynamic(this, &UMainMenu::SetActive);
	playerController = GetWorld()->GetFirstPlayerController();
	onMenuIsVisible.AddDynamic(this, &UMainMenu::PauseGame);
	//onGamePaused.AddDynamic(this, &UMainMenuWidget::InitInput);
	onGamePaused.AddDynamic(this, &UMainMenu::DisplayCursor);

	
	SetVisibility(ESlateVisibility::Hidden);
	onInit.Broadcast();
}


void UMainMenu::InitInput()
{
}

void UMainMenu::SetActive()
{
	UE_LOG(LogTemp, Warning, TEXT("CALLED EVENTS FROM MENU"));
	SetVisibility(ESlateVisibility::Visible);
	onMenuIsVisible.Broadcast();

}

void UMainMenu::PauseGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Pause game called"));

	SetPlayerInputMode();
	playerController->Pause();
	currentState = GameState::PAUSED;

	onGamePaused.Broadcast();
}

void UMainMenu::DisplayCursor()
{
	playerController->SetShowMouseCursor(true);

}

void UMainMenu::SetPlayerInputMode()
{
	FInputModeGameAndUI _inputMode;
	_inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(_inputMode);
}

