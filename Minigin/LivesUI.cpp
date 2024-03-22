#include "LivesUI.h"
#include "iostream"
#include "EventManager.h"
#include "GameObject.h"
#include "LivesComponent.h"

dae::LivesUI::LivesUI(GameObject* owner)
	:Component(owner)
{
	auto boundUpdateLife = std::bind(&LivesUI::UpdateLives, this, std::placeholders::_1);
	GameObjectEvent event;
	event.eventType = "LiveUpdated";
	EventManager::GetInstance().AddObserver(event, boundUpdateLife);
}

void dae::LivesUI::UpdateLives(const dae::Event* e)
{
	if (const GameObjectEvent* event = dynamic_cast<const GameObjectEvent*>(e))
	{
		std::cout << "lives updated " << event->gameObject->GetComponent<LivesComponent>()->GetLives() << '\n';
	}
	
	
}
