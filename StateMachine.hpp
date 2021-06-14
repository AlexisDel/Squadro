//Définition unique de la classe
#pragma once

//Bibliothèques nécessaires
#include <memory>
#include <stack>

//Classe nécessaire
#include "State.hpp"

//Espace de nom : Squadro
namespace Squadro
{
	//Poiteur "StateRef" qui pointe vers la classe parent "State"
	typedef std::unique_ptr<State> StateRef;

	//Classe "StateMachine" dérivée de "State"
	class StateMachine
	{
	public:
		StateMachine() { } //Constructeur
		~StateMachine() { } //Destructeur

		/** Ajoute un état e haut de la pile, l'état actuel
 		* @param newState une classe dérivée de "State" : le nouvel état
 		* @param isReplacing un booléan : indique si on doit supprimer ou juste "mettre en pause" l'état précédent
 		**/
		void AddState(StateRef newState, bool isReplacing = true);

		//Supprime l'état actuel
		void RemoveState();

		//Applique les changements que l'on a effectuer avec "AddState" et "RemoveState"
		void ProcessStateChanges();

		//@return une référence de l'état en haut de la pile
		StateRef &GetActiveState();

	private:
		//pile des états
		std::stack<StateRef> _states;
		//état à ajouter à la pile
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}
