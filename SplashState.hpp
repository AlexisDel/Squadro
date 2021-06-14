//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

//Classes nécessaires
#include "State.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "SplashState" dérivé de "State"
	class SplashState : public State
	{
	public:

		SplashState(GameDataRef data);
		~SplashState() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
	};
}
