//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
//Classes nécessaires
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "PauseState" dérivé de "State"
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);
		~PauseState() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _resumeButton;

		sf::Sprite _homeButton;

	};
}
