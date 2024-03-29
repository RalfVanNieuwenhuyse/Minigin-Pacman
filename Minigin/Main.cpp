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

#include "LivesComponent.h"
#include "LivesUI.h"
#include "PlayerScore.h"
#include "ScoreUI.h"

#include "MoveCommand.h"
#include "DebugCommands.h"


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

	pacman->AddComponent<dae::LivesComponent>()->SetLives(3);
	pacman->AddComponent<dae::PlayerScore>()->SetScore(0);

	input.AddKeyboardCommand<dae::RemoveLifeCommand>(std::make_unique<dae::RemoveLifeCommand>(pacman.get()),
		dae::KeyboardInput{SDL_SCANCODE_O, dae::ButtonState::Up });
	input.AddKeyboardCommand<dae::AddScoreCommand>(std::make_unique<dae::AddScoreCommand>(pacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_I, dae::ButtonState::Up });


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

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto empty = std::make_shared<dae::GameObject>();
	scene.Add(empty);
	empty->GetTransform()->SetPosition(5, (480 / 2), 0);

	auto pacmanLives = std::make_shared<dae::GameObject>();	
	scene.Add(pacmanLives);
	auto textcompPacLives = pacmanLives->AddComponent<dae::Text>();
	textcompPacLives->SetFont(font);
	pacmanLives->AddComponent<dae::TextRender>();
	pacmanLives->AddComponent<dae::LivesUI>()->SetObjectToCheck(pacman.get());
	pacmanLives->SetParent(empty.get(), false);

	auto pacmanScore = std::make_shared<dae::GameObject>();
	scene.Add(pacmanScore);
	auto textcompPacScore = pacmanScore->AddComponent<dae::Text>();
	textcompPacScore->SetFont(font);
	pacmanScore->AddComponent<dae::TextRender>();
	pacmanScore->AddComponent<dae::ScoreUI>()->SetObjectToCheck(pacman.get());
	pacmanScore->SetParent(empty.get(), false);
	pacmanScore->GetTransform()->SetPosition(0.f, 25.f, 0.f);

	

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

	mspacman->AddComponent<dae::LivesComponent>()->SetLives(3);
	mspacman->AddComponent<dae::PlayerScore>()->SetScore(0);

	input.AddKeyboardCommand<dae::RemoveLifeCommand>(std::make_unique<dae::RemoveLifeCommand>(mspacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_L, dae::ButtonState::Up });
	input.AddKeyboardCommand<dae::AddScoreCommand>(std::make_unique<dae::AddScoreCommand>(mspacman.get()),
		dae::KeyboardInput{ SDL_SCANCODE_K, dae::ButtonState::Up });

	auto mspacmanLives = std::make_shared<dae::GameObject>();
	scene.Add(mspacmanLives);
	auto textcompmsPacLives = mspacmanLives->AddComponent<dae::Text>();
	textcompmsPacLives->SetFont(font);
	mspacmanLives->AddComponent<dae::TextRender>();
	mspacmanLives->AddComponent<dae::LivesUI>()->SetObjectToCheck(mspacman.get());
	mspacmanLives->SetParent(empty.get(), false);
	mspacmanLives->GetTransform()->SetPosition(0.f, 55.f, 0.f);

	auto mspacmanScore = std::make_shared<dae::GameObject>();
	scene.Add(mspacmanScore);
	auto textcompmsPacScore = mspacmanScore->AddComponent<dae::Text>();
	textcompmsPacScore->SetFont(font);
	mspacmanScore->AddComponent<dae::TextRender>();
	mspacmanScore->AddComponent<dae::ScoreUI>()->SetObjectToCheck(mspacman.get());
	mspacmanScore->SetParent(empty.get(), false);
	mspacmanScore->GetTransform()->SetPosition(0.f, 80.f, 0.f);
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


	auto fontsmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto tooltippac = std::make_shared<dae::GameObject>();
	scene.Add(tooltippac);
	auto tooltippacText = tooltippac->AddComponent<dae::Text>();
	tooltippacText->SetFont(fontsmall);
	tooltippacText->SetText("pacman: move wasd, remove life by o, add score i");
	tooltippac->AddComponent<dae::TextRender>();
	tooltippac->GetTransform()->SetPosition(5, 60, 0);

	auto tooltipmspac = std::make_shared<dae::GameObject>();
	scene.Add(tooltipmspac);
	auto tooltipmspacText = tooltipmspac->AddComponent<dae::Text>();
	tooltipmspacText->SetFont(fontsmall);
	tooltipmspacText->SetText("mspacman: move dpad, remove life L, add score k");
	tooltipmspac->AddComponent<dae::TextRender>();
	tooltipmspac->GetTransform()->SetPosition(5, 85, 0);

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