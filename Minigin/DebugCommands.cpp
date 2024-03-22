#include "DebugCommands.h"
#include "LivesComponent.h"
#include "PlayerScore.h"

dae::RemoveLifeCommand::RemoveLifeCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Lives = GetGameObject()->GetComponent<LivesComponent>();
}

void dae::RemoveLifeCommand::Execute()
{
	m_Lives->RemoveLives();
}

dae::AddScoreCommand::AddScoreCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_ScoreComp = GetGameObject()->GetComponent<PlayerScore>();
}

void dae::AddScoreCommand::Execute()
{
	m_ScoreComp->AddScore(100);
}
