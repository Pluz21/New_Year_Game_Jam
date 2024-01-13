// Made by Skyler, Pluz21, KingCache,Annihilator & BigRizzlerK


#include "NYNS_GameJam_Project/World/CustomGameInstance.h"
#include <MoviePlayer/Public/MoviePlayer.h>

void UCustomGameInstance::Init()
{
    Super::Init();

    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::BeginLoadingScreen);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UCustomGameInstance::EndLoadingScreen);
}

void UCustomGameInstance::BeginLoadingScreen(const FString& _mapName)
{
    if (!IsRunningDedicatedServer())
    {
        FLoadingScreenAttributes _loadingScreen;
        _loadingScreen.bAutoCompleteWhenLoadingCompletes = false;
        UE_LOG(LogTemp, Warning, TEXT("Loading screen called"));
        _loadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

        GetMoviePlayer()->SetupLoadingScreen(_loadingScreen);
    }
}

void UCustomGameInstance::EndLoadingScreen(UWorld* _inLoadedWorld)
{

}

void UCustomGameInstance::AddWidget()
{
    //APlayerController* _controller = GetWorld()->GetFirstPlayerController();
    //gameViewPortClient->addwid
}
