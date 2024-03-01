#include "Rotatetor.h"
#include "Transform.h"
#include "GTime.h"

dae::Rotatetor::Rotatetor(GameObject* owner)
	:Component(owner)
{
	SetupRequiredComponents();
	//CheckForRequiredComponents();
}

void dae::Rotatetor::Update()
{
	auto curCircleProgress = m_LastCircleProgress + m_RotateSpeed * dae::GTime::GetInstance().GetTimeStep();

	if (curCircleProgress != m_LastCircleProgress)
	{		
		glm::vec3 newPos = { cos(curCircleProgress) * m_CircleRadius ,sin(curCircleProgress) * m_CircleRadius, 0 };

		m_Transform->SetPosition(newPos);

		m_LastCircleProgress = curCircleProgress;
		if (m_LastCircleProgress >= MAX_ROTATION)
		{
			m_LastCircleProgress -= MAX_ROTATION;
		}
	}
}

void dae::Rotatetor::SetRotateSpeed(float speed)
{
	m_RotateSpeed = speed;
}

void dae::Rotatetor::SetCircleRadius(float radius)
{
	m_CircleRadius = radius;
}

void dae::Rotatetor::CheckForRequiredComponents() const
{
	if (m_Transform)
	{
		throw std::invalid_argument("RotatorComponent needs a TransformComponent, currently expired");
	}
}

void dae::Rotatetor::SetupRequiredComponents()
{
	m_Transform = GetOwner()->GetTransform();
}
