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

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	auto transformLocked = m_transform;
	if (!parent)
	{
		transformLocked->SetPosition(transformLocked->GetPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			auto parentTransformLocked = parent->m_transform;
			transformLocked->SetPosition(transformLocked->GetLocalPosition() - parentTransformLocked->GetPosition());
		}
		transformLocked->SetPositionDirty();
	}

	if (m_Parent)
	{
		m_Parent->RemoveChild(shared_from_this());
	}

	m_Parent = parent;

	if (m_Parent)
	{
		m_Parent->AddChild(shared_from_this());
	}
}

const dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

void dae::GameObject::ClearChildren()
{
	for (auto child : m_Children)
	{
		child->SetParent(nullptr, true);
	}
	m_Children.clear();
}

std::vector<std::shared_ptr<dae::GameObject>> dae::GameObject::GetChildren() const
{
	return m_Children;
}

void dae::GameObject::RemoveChild(const std::shared_ptr<GameObject>& child)
{
	m_Children.erase(std::remove(begin(m_Children), end(m_Children), child));
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
	m_Children.push_back(child);
}
