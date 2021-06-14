//Définition unique de la classe
#pragma once

//Bibliothèque nécessaire
#include <SFML/Graphics.hpp>

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "AssetManager"
	class InputManager
	{
	public:
		InputManager() {} //Constructeur
		~InputManager() {} //Destructeur

		/** Vérifie si l'utilisateur à clicker avec la souris sur un certain objet
 		* @param objet un sprite : l'objet sur lequel il doit clicker
 		* @param button un Button : le bouton avec lequel il doit cliker
 		* @param &window un RenderWindow : une référence de la fenêtre sur laquelle il doit clicker
 		* @return un booléan
 		**/
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);


		/** Récupère la postion en x et en y de la souris
 		* @param &window un RenderWindow : une référence de la fenêtre sur laquelle le curseur doit être
 		* @return un Vector2i : objet représentant un vecteur ayant un attribut x et y (qui sont des entiers)
 		**/
		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}
