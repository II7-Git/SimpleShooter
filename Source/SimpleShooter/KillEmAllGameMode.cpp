// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    // 죽은 Pawn이 플레이어인 경우-> 게임 오버
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    // AI 상대를 죽인 경우-> 남은 AI 개수를 세서 전부 사망시 게임 종료
    for (AShooterAIController *Controller : TActorRange<AShooterAIController>(GetWorld()))
    {

        if (!Controller->IsDead())
        {
            return;
        }
    }

    // 모든 AI를 없애서 승리함
    EndGame(true);
    return;
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    // 월드 내에 있는 모든 ACotroller 객체 리턴
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        // 플레이어가 남으면 true ,AI만 남으면 false
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
