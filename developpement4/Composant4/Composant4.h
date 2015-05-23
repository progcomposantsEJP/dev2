// Le bloc ifdef suivant est la façon standard de créer des macros qui facilitent l'exportation 
// à partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compilés avec le symbole COMPOSANT4_EXPORTS
// défini sur la ligne de commande. Ce symbole ne doit pas être défini pour un projet
// qui utilisent cette DLL. De cette manière, les autres projets dont les fichiers sources comprennent ce fichier considèrent les fonctions 
// COMPOSANT4_API comme étant importées à partir d'une DLL, tandis que cette DLL considère les symboles
// définis avec cette macro comme étant exportés.
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

