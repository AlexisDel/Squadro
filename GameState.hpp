//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <sstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <SFML/Graphics.hpp>

//Classes nécessaires
#include "State.hpp"
#include "Game.hpp"
#include "Piece.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

#include "DEFINITIONS.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "GameState" dérivé de "State"
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState() { }

		void Init();
		void HandleInput();
		void Update();
		void Draw();

	private:

		//Met à jour l'array représentant le plateau
		void UpdateGameGrid();

		//Met à jour la position de sprites en fonction de gridArray
		void UpdateGraphicGrid();

		/** Renvoie les pièces à leur position initial si la pièce "id" est passé au dessus
 		* @param id un int : l'indice de la pièce qui vient de jouer
		**/
		void GetBackPiece(int id);

		/** Enlève la pièce "id" du jeu si elle est revenu à sa position de départ
 		* @param id un int : l'indice de la pièce qui vient de jouer
		**/
		void RemovePiece(int id);

		//Arrête la partie si un des joueur à gagné
		void CheckForWin();

		/** Recupère l'indice du pion sur lequel le joueur à clicker, le fait avancé, change ses paramètres et éxecute les fonctions suivantes :
 		*	GetBackPiece(i); RemovePiece(i); CheckForWin(); UpdateGameGrid(); UpdateGraphicGrid();
		**/
		void CheckAndMovePiece();


		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		std::vector <Piece> Pieces;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[7][7];

		char gridArray[7][7];

		sf::Clock _clock;

		std::vector<int> yellow_possible_piece;
		std::vector<int> red_possible_piece;


		int turn;
		int gameState;


	};
}
