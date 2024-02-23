#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* owner);

		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position;
	};
}
