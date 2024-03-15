#include "MoveCommand.h"
#include "Transform.h"
#include "GTime.h"


dae::MoveCommand::MoveCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{
	m_Transform = GetGameObject()->GetTransform();
}

void dae::MoveCommand::Execute()
{	
	auto newPos = m_Transform->GetLocalPosition() + m_Direction * m_MoveSpeed * GTime::GetInstance().GetDeltaTime();
	m_Transform->SetPosition(newPos);
}

void dae::MoveCommand::SetDirection(glm::vec3 direction)
{
	 m_Direction = direction;
}

void dae::MoveCommand::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}
