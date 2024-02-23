#include "FPS.h"
#include "Text.h"
#include "GTime.h"

dae::FPS::FPS(GameObject* owner)
	:Component(owner)
{
	SetupRequiredComponents();
	CheckRequiredComponents();
}

void dae::FPS::Update()
{
	m_Delay += dae::GTime().GetInstance().GetDeltaTime();

	if (m_Delay >= m_MaxDelay )
	{
		float fps = 1.f / dae::GTime().GetInstance().GetDeltaTime();
		float roundedfps = std::round(fps * 10.0f)/10.0f;		
		auto stringFPS = std::to_string(roundedfps);

		GetOwner()->GetComponent<Text>().get()->SetText(stringFPS);
		m_Delay = 0;
	}
	
}

void dae::FPS::CheckRequiredComponents() const
{
	if (!m_Text)
	{
		throw std::invalid_argument("FPS needs Text");
	}
}

void dae::FPS::SetupRequiredComponents()
{
	auto Owner = GetOwner();
	if (!m_Text)
	{
		m_Text = Owner->GetComponent<Text>().get();
		if (!m_Text)
		{
			m_Text = Owner->AddComponent<Text>().get();
		}
	}

	GetOwner()->GetComponent<Text>().get()->SetText("000");
}

