// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameDataWidget.h"

#include "MyGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 UGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKills() : 0;
}

int32 UGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 UGameDataWidget::GetTotalRoundNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining():0;
}

AMyGameModeBase* UGameDataWidget::GetGameMode() const
{
	return GetWorld() ? Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* UGameDataWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
