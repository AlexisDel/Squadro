//Classe définie
#include "MainMenuState.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("PVP Button", MAIN_MENU_PVP_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("IA Button", MAIN_MENU_IA_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_pvpButton.setTexture(this->_data->assets.GetTexture("PVP Button"));
		this->_iaButton.setTexture(this->_data->assets.GetTexture("IA Button"));
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));

		this->_pvpButton.setPosition((SCREEN_WIDTH / 2) - (this->_pvpButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT * 1.7/4) - (this->_pvpButton.getGlobalBounds().height / 2));
		this->_iaButton.setPosition((SCREEN_WIDTH / 2) - (this->_iaButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT * 3/4) - (this->_iaButton.getGlobalBounds().height / 2));
		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.2);

	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pvpButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState( StateRef( new GameState( _data ) ), true );
			}

			if (this->_data->input.IsSpriteClicked(this->_iaButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState( StateRef( new GameStateAI( _data ) ), true );
			}
		}
	}

	void MainMenuState::Update()
	{

	}

	void MainMenuState::Draw()
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pvpButton);
		this->_data->window.draw(this->_iaButton);
		this->_data->window.draw(this->_title);

		this->_data->window.display();
	}
}
