#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(StatsLog,All,All);

void ASTUPlayerState::LogInfo()
{
	UE_LOG(StatsLog,Warning,TEXT("TeamID:%i, Kills:%i, Deaths:%i"),TeamID, GetKills(), GetDeaths());
}
