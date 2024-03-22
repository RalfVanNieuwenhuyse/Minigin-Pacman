#include "AchievementChecker.h"
//#include "Achievements.h"
#include "EventManager.h"
#include "PlayerScore.h"

extern CSteamAchievements* g_SteamAchievements;

dae::AchievementChecker::AchievementChecker(GameObject* owner)
	:Component(owner)
{
	auto boundUpdateScore = std::bind(&AchievementChecker::CheckForWin, this, std::placeholders::_1);
	GameObjectEvent event;
	event.eventType = "ScoreUpdated";
	EventManager::GetInstance().AddObserver(event, boundUpdateScore);
}

void dae::AchievementChecker::CheckForWin(const dae::Event* e)
{
	if (const GameObjectEvent* GameEvent = dynamic_cast<const GameObjectEvent*>(e))
	{	
		if (m_MINScore <= GameEvent->gameObject->GetComponent<PlayerScore>()->GetScore())
		{
			if (g_SteamAchievements) g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
		}		
	}
}
