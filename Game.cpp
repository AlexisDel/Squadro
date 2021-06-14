//Classe définie
#include "Game.hpp"

//Erreur ?
#include "SplashState.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	Game::Game(int width, int height, std::string title)
	{
        //Créer une fenêtre
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        //Crée l'état ""écran de chargement" et l'initialise
		_data->machine.AddState(StateRef(new SplashState(this->_data)));
        //Lance le jeu
		this->Run();
	}

	void Game::Run()
	{

		while (this->_data->window.isOpen())
		{
      //Met à jour l'état de la pile et initialise le nouvel état si il à changé
			this->_data->machine.ProcessStateChanges();

			if (this->_clock.getElapsedTime().asSeconds() >= dt)
			{
        //"Ecoute" les entrées utilisateur
				this->_data->machine.GetActiveState()->HandleInput();
        //Met à jour l'état actuel
				this->_data->machine.GetActiveState()->Update();
        //réinitialise le Chronomètre
				this->_clock.restart();
			}

      //Affiche l'état actuel
			this->_data->machine.GetActiveState()->Draw();
		}
	}
}
