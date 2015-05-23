// Le bloc ifdef suivant est la fa�on standard de cr�er des macros qui facilitent l'exportation 
// � partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compil�s avec le symbole COMPOSANT4_EXPORTS
// d�fini sur la ligne de commande. Ce symbole ne doit pas �tre d�fini pour un projet
// qui utilisent cette DLL. De cette mani�re, les autres projets dont les fichiers sources comprennent ce fichier consid�rent les fonctions 
// COMPOSANT4_API comme �tant import�es � partir d'une DLL, tandis que cette DLL consid�re les symboles
// d�finis avec cette macro comme �tant export�s.
#include <string>
using namespace std;
#ifdef COMPOSANT4_EXPORTS
#define COMPOSANT4_INTERFACE __declspec(dllexport)
#else
#define COMPOSANT4_INTERFACE __declspec(dllimport)
#endif


	COMPOSANT4_INTERFACE double findVolatility(double, double);
	COMPOSANT4_INTERFACE bool findVolatilityData(std::string);

/*
extern COMPOSANT4_API int nComposant4;

COMPOSANT4_API int fnComposant4(void);
*/

