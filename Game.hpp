//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
//Classes nécessaires
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
    //Structure "GameData"
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

    //Poiteur "GameDataRef" qui pointe vers la structure "GameData"
	typedef std::shared_ptr<GameData> GameDataRef;

    //Classe "Game"
	class Game
	{
	public:
        /** Créer une fenêtre et lance le jeu
 		* @param width un int : la largeur de la fenêtre
 		* @param height un int : la hauteur de la fenêtre
		* @param title un string : le titre de la fenêtre
 		**/
		Game(int width, int height, std::string title);
		~Game() { }

	private:
    //Fréquence d'actualisation
		const float dt = 1.0 / 60.0;
		sf::Clock _clock;

    //Definition de "_data" comme une structure dérivée de "GameData"
		GameDataRef _data = std::make_shared<GameData>();

    //Fait tourner le jeu
		void Run();
	};
}
