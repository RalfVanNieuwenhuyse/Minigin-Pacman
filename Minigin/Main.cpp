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
#include "InputManager.h"

#include "Scene.h"
#include "Image.h"
#include "ImageRender.h"
#include "Transform.h"
#include "Text.h"
#include "TextRender.h"
#include "FPS.h"
#include "Rotatetor.h"
#include "TrashTheCache.h"

#include "MoveCommand.h"


void createCharacters(dae::Scene& scene)
{
	auto& input = dae::InputManager::GetInstance();

	const float moveSpeed{ 100 };
	const glm::vec3 moveDirectionHor{ 1, 0, 0 };
	const glm::vec3 moveDirectionVert{ 0, 1, 0 };

#pragma region Pacman
	auto pacman = std::make_shared<dae::GameObject>();
	scene.Add(pacman);
	pacman->AddComponent<dae::Image>()->SetTexture("pacman.png");
	pacman->AddComponent<dae::ImageRender>();
	pacman->GetTransform()->SetPosition((640 / 2) + 10 , (480 / 2) + 60, 0);

	auto pMoveCommand = input.AddKeyboardCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(pacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_A, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionHor);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(pacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_D, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionHor);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(pacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_W, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionVert);
	pMoveCommand->SetMoveSpeed(moveSpeed);

	pMoveCommand = input.AddKeyboardCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(pacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_S, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionVert);
	pMoveCommand->SetMoveSpeed(moveSpeed);
#pragma endregion

#pragma region MsPacman
	auto mspacman = std::make_shared<dae::GameObject>();
	scene.Add(mspacman);
	mspacman->AddComponent<dae::Image>()->SetTexture("mspacman.png");
	mspacman->AddComponent<dae::ImageRender>();
	mspacman->GetTransform()->SetPosition((640 / 2) - 10, (480 / 2) + 60, 0);

	pMoveCommand = input.AddXboxCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(mspacman.get()),
		dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadLeft, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionHor);
	pMoveCommand->SetMoveSpeed(2.f * moveSpeed);

	pMoveCommand = input.AddXboxCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(mspacman.get()),
		dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadRight, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionHor);
	pMoveCommand->SetMoveSpeed(2.f * moveSpeed);

	pMoveCommand = input.AddXboxCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(mspacman.get()),
		dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadUp, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(-moveDirectionVert);
	pMoveCommand->SetMoveSpeed(2.f * moveSpeed);

	pMoveCommand = input.AddXboxCommand<dae::MoveCommand>(std::make_unique<dae::MoveCommand>(mspacman.get()),
		dae::XboxControllerInput{ 0, dae::XboxController::ControllerButton::DPadDown, dae::ButtonState::Pressed });
	pMoveCommand->SetDirection(moveDirectionVert);
	pMoveCommand->SetMoveSpeed(2.f * moveSpeed);
#pragma endregion
}

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

	

	

	/*auto trashTheCash = std::make_shared<dae::GameObject>();
	scene.Add(trashTheCash);
	trashTheCash->AddComponent<dae::TrashTheCache>();*/

	createCharacters(scene);
	
}


int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}