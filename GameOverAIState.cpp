//Classe défine
#include "GameOverAIState.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	GameOverAIState::GameOverAIState(GameDataRef data, int whoWin)
	{
		_data = data;
		_whoWin = whoWin;
	}

	void GameOverAIState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON_FILEPATH);


		if ( _whoWin == STATE_YOU_WON )
		{
			this->_data->assets.LoadTexture("Win Title", TITLE_YOU_WIN_FILEPATH);
		}
		else if ( _whoWin == STATE_AI_WON )
		{
			this->_data->assets.LoadTexture("Win Title", TITLE_AI_WIN_FILEPATH);
		}

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));
		this->_wintitle.setTexture(this->_data->assets.GetTexture("Win Title"));

		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4 * 2.5) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4 * 3.5) - (this->_homeButton.getLocalBounds().height / 2));
		this->_wintitle.setPosition((this->_data->window.getSize().x / 2) - (this->_wintitle.getLocalBounds().width / 2), (this->_data->window.getSize().y / 4 ) - (this->_wintitle.getLocalBounds().height / 2));
	}

	void GameOverAIState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameStateAI(_data)), true);
			}

			if (this->_data->input.IsSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);

			}
		}
	}

	void GameOverAIState::Update()
	{

	}

	void GameOverAIState::Draw()
	{
		this->_data->window.clear();

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_wintitle);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}
