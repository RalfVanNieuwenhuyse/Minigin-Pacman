#include "Component.h"

dae::Component::Component(GameObject* owner)
{
	m_Owner = owner;
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_Owner;
}