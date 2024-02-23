#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "Image.h"
#include "ImageRender.h"
#include "Transform.h"
#include "Text.h"
#include "TextRender.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();
	
	//go->SetTexture("background.tga");
	//scene.Add(go);

	/*go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);*/

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);

	auto background = std::make_shared<dae::GameObject>();	
	scene.Add(background);
	background->AddComponent<dae::Image>()->SetTexture("background.tga");
	background->AddComponent<dae::ImageRender>();

	auto logo = std::make_shared<dae::GameObject>();
	scene.Add(logo);
	logo->AddComponent<dae::Image>()->SetTexture("logo.tga");
	logo->AddComponent<dae::ImageRender>();
	logo->GetTransform().get()->SetPosition(216,180,0);

	auto text = std::make_shared<dae::GameObject>();
	scene.Add(text);
	auto textcomp = text->AddComponent<dae::Text>();
	textcomp->SetFont(font);
	textcomp->SetText("Programming 4 Assignment");
	text->AddComponent<dae::TextRender>();
	text->GetTransform().get()->SetPosition(80, 20, 0);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}