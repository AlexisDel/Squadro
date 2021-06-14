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
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "GameOver" dérivé de "State"
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int whoWin);
		GameOverState() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _retryButton;

    sf::Sprite _homeButton;

		sf::Sprite _wintitle;

		int _whoWin;

	};
}
