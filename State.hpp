//Définition unique de la classe
#pragma once

//Espace de nom : Squadro
namespace Squadro
{
	//Classe parent "State"
	class State
	{

	public:
		//Charge et positionne les textures nécessaire à un état (propre à chaque classe dérivée)
		virtual void Init() = 0;

		//Vérifie si l'utilisateur click sur un sprite (propre à chaque classe dérivée)
		virtual void HandleInput() = 0;

		//Passe à l'état suivant (propre à chaque classe dérivée)
		virtual void Update() = 0;

		//Dessine les sprites de l'état (propre à chaque classe dérivée)
		virtual void Draw() = 0;

		//Met en pause l'état (commun à toute les classes dérivées)
		virtual void Pause() { }

		//Reprend l'état avant pause (commun à toute les classes dérivées)
		virtual void Resume() { }
	};
}
