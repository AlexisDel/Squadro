//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <map>
#include <SFML/Graphics.hpp>

//Espace de nom : Squadro
namespace Squadro
{
	//Classe "AssetManager"
	class AssetManager
	{
	public:
		AssetManager() { } //Constructeur
		~AssetManager() { } //Destructeur

		/** Charge et nomme une texture
 		* @param name un string : le nom de la texture
 		* @param fileName un sting : l'emplacement de la texture
 		**/
		void LoadTexture(std::string name, std::string fileName);

		/** Utilise une texture
 		* @param name un string : le nom de la texture
		* @return une référence vers la texture "name"
		**/
		sf::Texture &GetTexture(std::string name);


	private:
		//Map contenant toute les textures ainsi que leurs noms associés
		std::map<std::string, sf::Texture> _textures;
	};
}
