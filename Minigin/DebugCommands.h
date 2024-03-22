#pragma once
#include "Command.h"

namespace dae
{
	class LivesComponent;

	class DebugCommands : public GameObjectCommand
	{
	public:
		DebugCommands(GameObject* gameObject);

		void Execute() override;
		
	private:
		std::shared_ptr<LivesComponent> m_Lives{ nullptr };
	};
}

