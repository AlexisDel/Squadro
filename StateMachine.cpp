//Classe définie
#include "StateMachine.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		//On "deplace" "newState" vers "_newState" via une référance à "newState"
		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		//Si _isRemoving est true et que la liste n'est pas vide
		if (this->_isRemoving && !this->_states.empty())
		{
			//Supprime l'état en haut de la pile
			this->_states.pop();

			if (!this->_states.empty())
			{
				//l'état "Resume" devient l'élément en haut de la pile
				this->_states.top()->Resume();
			}

			this->_isRemoving = false;
		}

		if (this->_isAdding)
		{
			//Si la liste n'est pas vide
			if (!this->_states.empty())
			{
				//Si _isReplacing est true
				if (this->_isReplacing)
				{
					//Supprime l'état en haut de la pille
					this->_states.pop();
				}
				else
				{
          //l'état "Pause" devient l'élément en haut de la pile
					this->_states.top()->Pause();
				}
			}

			//Ajoute l'état "_newState" en haut de la pile
			this->_states.push(std::move(this->_newState));
			//Initialise l'état en haut de la pile
			this->_states.top()->Init();
			this->_isAdding = false;
		}
	}

	StateRef &StateMachine::GetActiveState()
	{
		//return l'état en haut de la pile
		return this->_states.top();
	}
}
