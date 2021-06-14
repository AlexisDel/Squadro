//Classe définie
#include "AssetManager.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		//Si elle existe on charge la texture dans la variable local "tex"
		if (tex.loadFromFile(fileName))
		{
			//On charge la texture dans la map "_textures" et on lui associe le nom "name"
			this->_textures[name] = tex;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}
}
