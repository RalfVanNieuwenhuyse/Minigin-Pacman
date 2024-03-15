#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform;

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObject);

		void Execute() override;
		void SetDirection(glm::vec3 direction);
		void SetMoveSpeed(float moveSpeed);

	private:
		std::shared_ptr<Transform> m_Transform{ nullptr };
		glm::vec3 m_Direction{};
		float m_MoveSpeed{};
	};
}

