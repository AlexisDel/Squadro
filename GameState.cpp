//Classe définie
#include "GameState.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{

		//Initialisation des variables et des tableaux
		gameState = STATE_PLAYING;
		turn = 0;
		yellow_possible_piece = {0,1,2,3,4};
		red_possible_piece = {5,6,7,8,9};

		//Charge les textures
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


		//Associe les texttures à leurs sprites
		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		//Fixe la postion des sprites
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

		//Création d'une liste contenant les pions
		Pieces = {P0,P1,P2,P3,P4,P5,P6,P7,P8,P9};

		//Créer le plateau (virtuel)
		UpdateGameGrid();

		//Créer le plateau (graphique)
		UpdateGraphicGrid();

	}

	void GameState::HandleInput()
	{
		sf::Event event;

		//Si l'utilisateur fait une action
		if (this->_data->window.pollEvent(event))
		{
			//Si l'utilisateur ferme la fenêtre
			if (sf::Event::Closed == event.type)
			{
				//Ferme la fenêtre
				this->_data->window.close();
			}

			//Si l'utilisateur click sur le bouton pause
			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				//Passe l'état "Pause" en haut de le pile -> l'état actuel devient l'état "Pause"
				this->_data->machine.AddState( StateRef( new PauseState( _data ) ), false );
			}

			//Si l'utilisateur click sur le plateau
			else if ( this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window) )
			{
				if ( gameState == STATE_PLAYING )
				{
					CheckAndMovePiece( );
				}
			}
		}
	}

	void GameState::Update()
	{
		//Si YELLOW à gagné
		if ( gameState == STATE_YELLOW_WON )
		{
			//Si le temps entre l'instant t et le dernier reset de l'horloge "_AIclock" est supérieur à "TIME_BEFORE_SHOWING_GAME_OVER"
			if ( this->_clock.getElapsedTime( ).asSeconds( ) > TIME_BEFORE_SHOWING_GAME_OVER )
			{
				//On ajoute "GameOverState" à la pile des états
				_data->machine.AddState( StateRef ( new GameOverState ( this->_data, STATE_YELLOW_WON ) ), true );
			}
		}
		//Si RED à gagné
		else if (gameState == STATE_RED_WON )
		{
			//Si le temps entre l'instant t et le dernier reset de l'horloge "_AIclock" est supérieur à "TIME_BEFORE_SHOWING_GAME_OVER"
			if ( this->_clock.getElapsedTime( ).asSeconds( ) > TIME_BEFORE_SHOWING_GAME_OVER )
			{
				//On ajoute "GameOverState" à la pile des états
				_data->machine.AddState( StateRef ( new GameOverState ( this->_data, STATE_RED_WON ) ), true );
			}
		}
	}

	void GameState::Draw()
	{

		//Clear la fenêtre
		this->_data->window.clear();

		//Dessine la fenêtre
		this->_data->window.draw( this->_background );

		//Dessine le boutton pause
		this->_data->window.draw( this->_pauseButton );

		//Dessine le plateau (grille)
		this->_data->window.draw( this->_gridSprite );

		//Dessine les pièces
		for (int x = 0; x < 7; x++)
		{
    	for (int y = 0; y < 7; y++)
			{
				this->_data->window.draw( this->_gridPieces[x][y] );
			}
		}

		//Met à jour la fenêtre
		this->_data->window.display();
	}

	void GameState::UpdateGameGrid()
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

	void GameState::UpdateGraphicGrid()
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

	void GameState::GetBackPiece(int id)
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


	void GameState::RemovePiece(int id)
	{
		if(Pieces[id].color == "YELLOW")
		{
			if (Pieces[id].y == 0 and Pieces[id].default_y == 6)
			{
				Pieces[id].shape = '.';
				Pieces[id].state = 0;
				yellow_possible_piece.erase(std::remove(yellow_possible_piece.begin(), yellow_possible_piece.end(), (id)), yellow_possible_piece.end());
			}
		}

		if(Pieces[id].color == "RED")
		{
			if (Pieces[id].x == 6 and Pieces[id].default_x == 0)
			{
				Pieces[id].shape = '.';
				Pieces[id].state = 0;
				red_possible_piece.erase(std::remove(red_possible_piece.begin(), red_possible_piece.end(), (id)), red_possible_piece.end());
			}
		}
	}

	void GameState::CheckForWin()
	{
		if ( yellow_possible_piece.size() == 1 )
		{
			gameState = STATE_YELLOW_WON;
			this->_clock.restart();
		}
		else if ( red_possible_piece.size() == 1 )
		{
			gameState = STATE_RED_WON;
			this->_clock.restart();
		}
	}




	void GameState::CheckAndMovePiece()
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

					// TEST : verifie que la piece est toujours dans la grille apres déplacement
          assert((Pieces[i].x >= 0 && Pieces[i].x <= 6 && Pieces[i].y >= 0 && Pieces[i].y <= 6) == true );

					GetBackPiece(i);

					RemovePiece(i);

					Pieces[i].changeFeatures();

					CheckForWin();

					turn+=1;
				}
			}
		}

		else
		{
			for ( int i = 5; i < 10; i++ )
			{
				if ( Pieces[i].y == column && Pieces[i].x == row )
				{
					Pieces[i].move();

					// TEST : verifie que la piece est toujours dans la grille apres déplacement
          assert((Pieces[i].x >= 0 && Pieces[i].x <= 6 && Pieces[i].y >= 0 && Pieces[i].y <= 6) == true );

					GetBackPiece(i);

					RemovePiece(i);

					Pieces[i].changeFeatures();

					CheckForWin();

					turn+=1;
				}
			}
		}
		UpdateGameGrid();
		UpdateGraphicGrid();
	}
}
