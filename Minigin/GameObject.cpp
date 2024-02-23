#include <string>
#include "Transform.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
	m_transform = AddComponent<Transform>();
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Update();	
	}
}

void dae::GameObject::Render() const
{	
	for (auto& component : m_Components)
	{
		component->Render();		
	}
}

void dae::GameObject::Destroy()
{
	m_IsDestroyed = true;
}

bool dae::GameObject::IsDestroyed()
{
	return m_IsDestroyed;
}

std::shared_ptr<dae::Transform> dae::GameObject::GetTransform() const
{
	return m_transform;
}
