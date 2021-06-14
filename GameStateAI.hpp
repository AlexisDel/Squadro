//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
//Classes nécessaires
#include "State.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "GameOverAIState.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "GameStateAI" dérivé de "State"
	class GameStateAI : public State
	{
	public:
		GameStateAI(GameDataRef data);
		~GameStateAI() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:
		void UpdateGameGrid();

		void UpdateGraphicGrid();

		void GetBackPiece(int id);

		void RemovePiece(int id);

		void CheckAndMovePiece();

		void AIMovePiece();

		void CheckForWin();

		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		std::vector <Piece> Pieces;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[7][7];

		char gridArray[7][7];

		sf::Clock _clock;

		sf::Clock _AIclock;

		std::vector<int> ai_possible_piece;
		std::vector<int> you_possible_piece;

		std::vector<int> ai_possible_move;

		int turn;
		int gameState;


	};
}
