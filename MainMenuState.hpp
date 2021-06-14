//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

//Classes nécessaires
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "GameStateAI.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "MainMenuState" dérivé de "State"
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pvpButton;

		sf::Sprite _iaButton;

		sf::Sprite _title;
	};
}
