#include "DebugCommands.h"
#include "LivesComponent.h"

dae::DebugCommands::DebugCommands(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Lives = GetGameObject()->GetComponent<LivesComponent>();
}

void dae::DebugCommands::Execute()
{
	m_Lives->RemoveLives();
}
