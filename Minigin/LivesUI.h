#pragma once
#include "Component.h"
#include "Event.h"

namespace dae
{
	class LivesUI :	public Component
	{
	public:
		LivesUI(GameObject* owner);
		~LivesUI() = default;
		LivesUI(const LivesUI& other) = delete;
		LivesUI(LivesUI&& other) = delete;
		LivesUI& operator=(const LivesUI& other) = delete;
		LivesUI& operator=(LivesUI&& other) = delete;
	private:
		void UpdateLives(const dae::Event* e);
	};
}


