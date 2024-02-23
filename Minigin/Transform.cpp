#include "GameObject.h"
#include "Transform.h"

dae::Transform::Transform(GameObject* owner)
	: Component(owner)
{
	m_position.x = 0.f;
	m_position.y = 0.f;
	m_position.z = 0.f;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
