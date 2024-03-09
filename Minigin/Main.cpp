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
#include "FPS.h"
#include "Rotatetor.h"
#include "TrashTheCache.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	auto background = std::make_shared<dae::GameObject>();	
	scene.Add(background);
	background->AddComponent<dae::Image>()->SetTexture("background.tga");
	background->AddComponent<dae::ImageRender>();

	auto logo = std::make_shared<dae::GameObject>();
	scene.Add(logo);
	logo->AddComponent<dae::Image>()->SetTexture("logo.tga");
	logo->AddComponent<dae::ImageRender>();
	logo->GetTransform()->SetPosition(216,180,0);

	auto text = std::make_shared<dae::GameObject>();
	scene.Add(text);
	auto textcomp = text->AddComponent<dae::Text>();
	textcomp->SetFont(font);
	textcomp->SetText("Programming 4 Assignment");
	text->AddComponent<dae::TextRender>();
	text->GetTransform()->SetPosition(80, 20, 0);

	auto fps = std::make_shared<dae::GameObject>();
	scene.Add(fps);	
	auto textFPScomp = fps->AddComponent<dae::Text>();
	textFPScomp->SetFont(font);	
	textFPScomp->SetText("test");
	fps->AddComponent<dae::TextRender>();
	fps->AddComponent<dae::FPS>();
	fps->GetTransform()->SetPosition(0, 420, 0);

	auto empty = std::make_shared<dae::GameObject>();
	scene.Add(empty);
	empty->GetTransform()->SetPosition(640/2, (480/2) + 60, 0);

	auto pacman = std::make_shared<dae::GameObject>();
	scene.Add(pacman);
	pacman->SetParent(empty.get(), false);
	pacman->AddComponent<dae::Image>()->SetTexture("pacman.png");
	pacman->AddComponent<dae::ImageRender>();
	pacman->AddComponent<dae::Rotatetor>();

	auto mspacman = std::make_shared<dae::GameObject>();
	scene.Add(mspacman);
	mspacman->SetParent(pacman.get(), false);
	mspacman->AddComponent<dae::Image>()->SetTexture("mspacman.png");
	mspacman->AddComponent<dae::ImageRender>();
	mspacman->AddComponent<dae::Rotatetor>()->SetRotateSpeed(-2);

	auto trashTheCash = std::make_shared<dae::GameObject>();
	scene.Add(trashTheCash);
	trashTheCash->AddComponent<dae::TrashTheCache>();
	
}


int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}