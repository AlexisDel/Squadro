//Classe définie
#include "GameStateAI.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	GameStateAI::GameStateAI(GameDataRef data) : _data(data)
	{

	}

	void GameStateAI::Init()
	{
		gameState = STATE_PLAYING;
		turn = 0;

		you_possible_piece = {0,1,2,3,4};
		ai_possible_piece = {5,6,7,8,9};

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("Grid Corner", GRID_CORNER_FILEPATH);
		this->_data->assets.LoadTexture("Yellow Piece 1", Y1_FILEPATH);
		this->_data->assets.LoadTexture("Yellow Piece 2", Y2_FILEPATH);
		this->_data->assets.LoadTexture("Red Piece 1", R1_FILEPATH);
		this->_data->assets.LoadTexture("Red Piece 2", R2_FILEPATH);
		this->_data->assets.LoadTexture("Empty", EMPTY_FILEPATH);

		this->_data->assets.LoadTexture("Y 1P", Y_1P_FILEPATH);
		this->_data->assets.LoadTexture("Y 2P", Y_2P_FILEPATH);
		this->_data->assets.LoadTexture("Y 3P", Y_3P_FILEPATH);
		this->_data->assets.LoadTexture("R 1P", R_1P_FILEPATH);
		this->_data->assets.LoadTexture("R 2P", R_2P_FILEPATH);
		this->_data->assets.LoadTexture("R 3P", R_3P_FILEPATH);





		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition( this->_data->window.getSize( ).x - _pauseButton.getLocalBounds( ).width, _pauseButton.getPosition( ).y );
		_gridSprite.setPosition( (SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width /2 ), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height /2 ) );

		//Création des pions
		Piece P0("YELLOW", 1, 1, 0, '>');
		Piece P1("YELLOW", 3, 2, 0, '>');
		Piece P2("YELLOW", 2, 3, 0, '>');
		Piece P3("YELLOW", 3, 4, 0, '>');
		Piece P4("YELLOW", 1, 5, 0, '>');
		Piece P5("RED", 3, 6, 1, '^');
		Piece P6("RED", 1, 6, 2, '^');
		Piece P7("RED", 2, 6, 3, '^');
		Piece P8("RED", 1, 6, 4, '^');
		Piece P9("RED", 3, 6, 5, '^');

		Pieces = {P0,P1,P2,P3,P4,P5,P6,P7,P8,P9};

		UpdateGameGrid();

		UpdateGraphicGrid();

	}

	void GameStateAI::HandleInput()
	{

		sf::Event event;

		if (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState( StateRef( new PauseState( _data ) ), false );
			}

			if ( this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window) )
			{
				if ( gameState == STATE_PLAYER_PLAYING )
				{
					CheckAndMovePiece( );
				}
			}
		}
		if ( gameState == STATE_AI_PLAYING )
		{
			if ( this->_AIclock.getElapsedTime( ).asSeconds( ) > 0.5 )
			{
				AIMovePiece();
			}
		}
	}


	void GameStateAI::Update()
	{
		if ( gameState == STATE_YOU_WON )
		{
			if ( this->_clock.getElapsedTime( ).asSeconds( ) > TIME_BEFORE_SHOWING_GAME_OVER )
			{
				_data->machine.AddState( StateRef ( new GameOverAIState ( this->_data, STATE_YOU_WON ) ), true );
			}
		}
		else if (gameState == STATE_AI_WON )
		{
			if ( this->_clock.getElapsedTime( ).asSeconds( ) > TIME_BEFORE_SHOWING_GAME_OVER )
			{
				_data->machine.AddState( StateRef ( new GameOverAIState ( this->_data, STATE_AI_WON ) ), true );
			}
		}
	}

	void GameStateAI::Draw()
	{

		this->_data->window.clear();

		this->_data->window.draw( this->_background );

		this->_data->window.draw( this->_pauseButton );

		this->_data->window.draw( this->_gridSprite );

		for (int x = 0; x < 7; x++)
		{
    	for (int y = 0; y < 7; y++)
			{
				this->_data->window.draw( this->_gridPieces[x][y] );
			}
		}

		this->_data->window.display();
	}

	void GameStateAI::UpdateGameGrid()
	{
		for (int x = 0; x < 7; x++)
		{
    	for (int y = 0; y < 7; y++)
			{
    		gridArray[x][y] = '.';
    	}
    }

		gridArray[0][0] = 'x';
		gridArray[6][0] = 'x';
		gridArray[0][6] = 'x';
		gridArray[6][6] = 'x';

		gridArray[0][1] = 'a';
		gridArray[0][2] = 'b';
		gridArray[0][3] = 'c';
		gridArray[0][4] = 'b';
		gridArray[0][5] = 'a';

		gridArray[1][6] = 'd';
		gridArray[2][6] = 'e';
		gridArray[3][6] = 'f';
		gridArray[4][6] = 'e';
		gridArray[5][6] = 'd';

		for (int i = 0; i < 10; i++)
		{
				 gridArray[Pieces[i].y][Pieces[i].x] = Pieces[i].shape;
    }

	}

	void GameStateAI::UpdateGraphicGrid()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture( "Grid Corner" ).getSize();

		for (int x = 0; x < 7; x++)
		{
    	for (int y = 0; y < 7; y++)
			{

				if (gridArray[x][y] == 'x')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Grid Corner" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == '>')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Yellow Piece 1" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == '<')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Yellow Piece 2" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == '^')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Red Piece 1" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );
				}

				else if (gridArray[x][y] == 'v')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Red Piece 2" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'a')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Y 1P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'b')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Y 3P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'c')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Y 2P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'd')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "R 3P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'e')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "R 1P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else if (gridArray[x][y] == 'f')
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "R 2P" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}

				else
				{
					_gridPieces[x][y].setTexture( this->_data->assets.GetTexture ( "Empty" ) );

					_gridPieces[x][y].setPosition( _gridSprite.getPosition( ).x + ( tempSpriteSize.x * x*1.1 ), _gridSprite.getPosition( ).y + ( tempSpriteSize.y * y*1.1 ) );

				}
    	}
    }
	}

	void GameStateAI::GetBackPiece(int id)
	{
		if ( Pieces[id].shape == '>' )
		{
			for (int i = 5; i < 10; i++)
			{
				if ( Pieces[id].x == Pieces[i].x )
				{
					if (Pieces[id].y >= Pieces[i].y && abs(Pieces[id].y-Pieces[i].y) <= Pieces[id].power)
					{
						Pieces[i].y = Pieces[i].default_y;
						Pieces[i].x = Pieces[i].default_x;
					}
				}
			}
		}

		if ( Pieces[id].shape == '<' )
		{
			for (int i = 5; i < 10; i++)
			{
				if ( Pieces[id].x == Pieces[i].x )
				{
					if (Pieces[id].y <= Pieces[i].y && abs(Pieces[i].y-Pieces[id].y) <= Pieces[id].power)
					{
						Pieces[i].y = Pieces[i].default_y;
						Pieces[i].x = Pieces[i].default_x;
					}
				}
			}
		}

		if ( Pieces[id].shape == '^' )
		{
			for (int i = 0; i < 5; i++)
			{
				if ( Pieces[id].y == Pieces[i].y )
				{
					if (Pieces[id].x <= Pieces[i].x && abs(Pieces[i].x-Pieces[id].x) <= Pieces[id].power)
					{
						Pieces[i].y = Pieces[i].default_y;
						Pieces[i].x = Pieces[i].default_x;
					}
				}
			}
		}

		if ( Pieces[id].shape == 'v' )
		{
			for (int i = 0; i < 5; i++)
			{
				if ( Pieces[id].y == Pieces[i].y )
				{
					if (Pieces[id].x >= Pieces[i].x && abs(Pieces[id].x-Pieces[i].x) <= Pieces[id].power)
					{
						Pieces[i].y = Pieces[i].default_y;
						Pieces[i].x = Pieces[i].default_x;
					}
				}
			}
		}
	}

	void GameStateAI::RemovePiece(int id)
	{
		if(Pieces[id].color == "YELLOW")
		{
			if (Pieces[id].y == 0 and Pieces[id].default_y == 6)
			{
				Pieces[id].shape = '.';
				Pieces[id].state = 0;
				you_possible_piece.erase(std::remove(you_possible_piece.begin(), you_possible_piece.end(), (id)), you_possible_piece.end());
			}
		}

		if(Pieces[id].color == "RED")
		{
			if (Pieces[id].x == 6 and Pieces[id].default_x == 0)
			{
				Pieces[id].shape = '.';
				Pieces[id].state = 0;
				ai_possible_piece.erase(std::remove(ai_possible_piece.begin(), ai_possible_piece.end(), (id)), ai_possible_piece.end());
			}
		}
	}

	void GameStateAI::CheckForWin()
	{
		if ( you_possible_piece.size() == 1 )
		{
			gameState = STATE_YOU_WON;
			this->_clock.restart();
		}
		else if ( ai_possible_piece.size() == 1 )
		{
			gameState = STATE_AI_WON;
			this->_clock.restart();
		}
	}

	void GameStateAI::AIMovePiece()
	{
		int p = std::rand()%(9-5 + 1) + 5;

		while ( (std::find(ai_possible_piece.begin(), ai_possible_piece.end(), p) != ai_possible_piece.end()) == false )
		{
			p = std::rand()%(9-5 + 1) + 5;
		}

		for (int i = 5; i < 10; i++)
		{
			if ( Pieces[i].shape == '^' )
			{
				if ( Pieces[i].x - Pieces[i].power <= 0 )
				{
					p = i;
				}
			}
			else if ( Pieces[i].shape == 'v' )
			{
				if ( Pieces[i].x + Pieces[i].power >= 6 )
				{
					p = i;
				 }
			}
		}

		for (int i = 5; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if ( Pieces[i].y == Pieces[j].y )
				{
					if ( Pieces[i].shape == '^' )
					{
						if ( Pieces[i].x - Pieces[i].power <= Pieces[j].x )
						{
							p = i;
						}
					}
					else if ( Pieces[i].shape == 'v' )
					{
						if ( Pieces[i].x + Pieces[i].power >= Pieces[i].x )
						{
							p = i;
					   }
					}
				}
			}
		}


		if (turn%2 != 0)
		{

			Pieces[p].move();

			GetBackPiece(p);

			RemovePiece(p);

			Pieces[p].changeFeatures();

			gameState = STATE_PLAYER_PLAYING;

			CheckForWin();

			turn+=1;
		}
		UpdateGameGrid();
		UpdateGraphicGrid();
	}


	void GameStateAI::CheckAndMovePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition( this->_data->window );
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds( );
		sf::Vector2f gapOutsideOfGrif = sf::Vector2f( (SCREEN_WIDTH - gridSize.width ) / 2, (SCREEN_HEIGHT - gridSize.height ) / 2 );
		sf::Vector2f gridLocalTouchPos = sf::Vector2f( touchPoint.x - gapOutsideOfGrif.x, touchPoint.y - gapOutsideOfGrif.y );
		sf::Vector2f gridSectionSize = sf::Vector2f( gridSize.width / 7, gridSize.height / 7 );

		int column, row;

		if ( gridLocalTouchPos.x < gridSectionSize.x )
		{
			column = 0;
		}
		else if ( gridLocalTouchPos.x < gridSectionSize.x * 2 )
		{
			column = 1;
		}
		else if ( gridLocalTouchPos.x < gridSectionSize.x * 3 )
		{
			column = 2;
		}
		else if ( gridLocalTouchPos.x < gridSectionSize.x * 4 )
		{
			column = 3;
		}
		else if ( gridLocalTouchPos.x < gridSectionSize.x * 5 )
		{
			column = 4;
		}
		else if ( gridLocalTouchPos.x < gridSectionSize.x * 6 )
		{
			column = 5;
		}
		else if ( gridLocalTouchPos.x < gridSize.width )
		{
			column = 6;
		}


		if ( gridLocalTouchPos.y < gridSectionSize.y )
		{
			row = 0;
		}
		else if ( gridLocalTouchPos.y < gridSectionSize.y * 2 )
		{
			row = 1;
		}
		else if ( gridLocalTouchPos.y < gridSectionSize.y * 3 )
		{
			row = 2;
		}
		else if ( gridLocalTouchPos.y < gridSectionSize.y * 4 )
		{
			row = 3;
		}
		else if ( gridLocalTouchPos.y < gridSectionSize.y * 5 )
		{
			row = 4;
		}
		else if ( gridLocalTouchPos.y < gridSectionSize.y * 6 )
		{
			row = 5;
		}
		else if ( gridLocalTouchPos.y < gridSize.height )
		{
			row = 6;
		}

		if (turn%2 == 0)
		{
			for ( int i = 0; i < 5; i++ )
			{
				if ( Pieces[i].y == column && Pieces[i].x == row )
				{

					Pieces[i].move();

					GetBackPiece(i);

					RemovePiece(i);

					Pieces[i].changeFeatures();

					gameState = STATE_AI_PLAYING;

					CheckForWin();

					turn+=1;
				}
			}
			UpdateGameGrid();
			UpdateGraphicGrid();
			this->_AIclock.restart();
		}
	}
}
