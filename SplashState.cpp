//Classe définie
#include "SplashState.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update()
	{
		if (this->_clock.getElapsedTime().asSeconds() > 2)
		{
			this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
		}
	}

	void SplashState::Draw()
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw( this->_background );

		this->_data->window.display();
	}
}
