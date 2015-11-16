#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#define kF 0 //constante booléenne FALSE
#define kV 1 //constante booléenne TRUE
void assert2(int bAssertion1,int bAssertion2);//vérifie que bAssertion1 et bAssertion2 sont vrais
void assert3(int bAssertion1,int bAssertion2,int bAssertion3);
void assert4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void assert5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void assert6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void Assert1(char *sContexte,int bAssertion1);//comme assert, mais affiche sContexte si bAssertion1 est faux
void Assert2(char *sContexte,int bAssertion1,int bAssertion2);//comme assert2, mais affiche sContexte si une assertion est fausse
void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3);
void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void b(int bBooleen);//affiche la valeur du booléen
void e(int iInteger);//affiche la valeur de iInteger
void ee(int iInteger1,int iInteger2);//affiche les valeurs des 2 entiers
void eee(int iInteger1,int iInteger2,int iInteger3);//affiche les valeurs des 3 entiers
void s(char *sString);//affiche la valeur de la chaîne
void s2(char *sString1,char *sString2);//affiche les chaînes séparées par des blancs puis passe à la ligne
void s3(char *sString1,char *sString2,char *sString3);//idem
void s4(char *sString1,char *sString2,char *sString3,char *sString4);//idem
void s5(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5);//idem
void ss(char *sString1,char *sString2);//cf s2
void sss(char *sString1,char *sString2,char *sString3);//cf s3
void ssss(char *sString1,char *sString2,char *sString3,char *sString4);//cf s4
void sssss(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5);//cf s5
void sb(char *sString,int bBooleen);
void se(char *sString,int iInteger1);//affiche la valeur de sString puis celle de iInteger1: se("eA",eA) affiche eA:2 si eA vaut 2
void see(char *sString,int iInteger1,int iInteger2);
void seee(char *sString,int iInteger1,int iInteger2,int iInteger3);
void si(char *sString,int iInteger1);//affiche la valeur de sString puis celle de iInteger1: se("eA",eA) affiche eA:2 si eA vaut 2
void sii(char *sString,int iInteger1,int iInteger2);
void siii(char *sString,int iInteger1,int iInteger2,int iInteger3);
void Appel0(char *sMessage);//associer à Appel1
void Appel1(char *sQuoi);//associer à Appel0
int bBit(char cCaractere);//rend vrai ssi cCaractere est '0' ou '1'
int bBool(long yEntier);
char *sBool(long yValeur);//rend en clair la valeur booléenne de yValeur
char *sC(char cAlphaNumeriqueOuEspace);//convertit un char en string
char *sC1(char *sA);//vérifie sA!=0 puis rend sA
char *sC1p(char *sA);//complète sA par un point terminal
char *sC2(char *sA,char *sB);
char *sC2b(char *sA,char *sB);//concatène en ajoutant un blanc intercalaire
char *sC2bp(char *sA,char *sB);//blanc intercalaire et point terminal
char *sC2p(char *sA,char *sB);//point terminal
char *sC3(char *sA,char *sB,char *sC);
char *sC3b(char *sA,char *sB,char *sC);
char *sC3bp(char *sA,char *sB,char *sC);
char *sC3p(char *sA,char *sB,char *sC);
char *sC4(char *sA,char *sB,char *sC,char *sD);
char *sC4b(char *sA,char *sB,char *sC,char *sD);
char *sC4bp(char *sA,char *sB,char *sC,char *sD);
char *sC4p(char *sA,char *sB,char *sC,char *sD);
char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
int nCaractere(char *sString);//rend 1 pour un "é" alors que strlen() rend 2
int bChiffre(char cCaractere);//'0'..'9',comme bDecit
char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative);//cf (bOptionSinonAlternative)? sOption: sAlternative
char *sChoix0(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide
void Confirmer(char *sMessage);//affiche sMessage et demande à l'utilisateur de valider
char *sCouple(int iEntierA,int iEntierB);//eg "(3,5)" 
void Croit(int iMinInclus,int iDedans,int iMaxInclus);
int bCroit(int iMinInclus,int iDedans,int iMaxInclus);
void CroitStrict(int iMinExclu,int iDedans,int iMaxExclu);
int bCroitStrict(int iMinExclu,int iDedans,int iMaxExclu);
int bDecit(char cCaractere);//alias bChiffre
void Dis(char *sString);//affiche la valeur de la chaîne;comme s()
char *sE(int nEspace);//rend nEspace blancs consécutifs
char *sEntier(int iEntier);
char *sEntierAvecSigne(int iEntier);// "+5" ou "-5" ou " 0"
char *sEst(int bAssertion);//rend "est" ou "n'est pas"
int bFaux(int iQuelconque);//vrai ssi iQuelconque==0
void FlipFlop(int bNouvelEtat,int *pbFlipFlop);// "pb" pour "pointeur sur booléen"
char *sFois(int nFois,char cMotif);//rend cMotif juxtaposé nFois
int nHasard(int uBorneLim);//[0..uBorneLim[
int uHasard(int uBorneMax);//[1..uBorneMax]
int bImpair(int iEntier);
long yInf(long yA,long yB);//identique à yMin(yA,yB)
int bLettre(char cCaractere);
void Ligne();//passe à la ligne
int bLigne();//passe à la ligne et rend vrai
long yMax(long yA,long yB);//identique à ySup(yA,yB)
void MemIntRaz(int piMemOrigine[],int nItemEnTout);
void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur);
void MemLongRaz(int pyMemOrigine[],int nItemEnTout);
void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur);
int bMajuscule(char cCaractere);
long yMin(long yA,long yB);//identique à yInf(yA,yB)
int bMinuscule(char cCaractere);
int uModulo1(int uDividende,int uDiviseur);//résultat dans [1..uDiviseur];calcule un modulo classique,mais 0 est remplacé par uDiviseur
char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation);//encadre sVerbe avec "ne" et sNegation, ou complète avec sAffirmation 
void OutilAMORCER();
void OutilINITIALISER();
void OutilTESTER(int iTest);
char *sP(char *sEntreParenthese);//rend sEntreParenthese entre 2 parenthèses
int bPair(int iEntier);
char *sPas(char *sVerbe,int bNegativer);//encadre avec "ne" et "pas" si bNegativer
char *sPluriel(int nEffectif,char *sSingulier);//(3,"pomme") rend "3 pommes"
char *sSigne(int iEntier);//"+" ou "-" ou " " selon le signe de iEntier
void Stop(int nMassacre);//sortie catastrophe;l'endroit de l'appel est censé être identifié par nMassacre
long ySup(long yA,long yB);//identique à yMax(yA,yB)
void Titrer(char *sTitre);//affiche sTitre centré sur 40 caractères et passe à la ligne
void VecteurVoir(char *sQuoi,int piQuelVecteur[],int nIndexMin,int nIndexMax);
int bVirguler();//affiche une virgule et rend vrai
int bVoyelle(char *sString,int nCodeCaractereRg);
void Vrai(int bAssertion);//vrai ssi iQuelconque!=0
int bVrai(int iQuelconque);//rend 1 ssi iQuelconque est non nul;rend 0 sinon
void Vrai2(int bAssertion1,int bAssertion2);
void Vrai3(int bAssertion1,int bAssertion2,int bAssertion3);
void Vrai4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Vrai5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Vrai6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void While(long zIterationMax);//prend note du nombre maximum d'itérations acceptable dans le while qui suit l'appel de cette routine
int bWhile(int bExpressionBooleenne);//rend bExpressionBooleenne après avoir vérifié que l'itération en cours ne dépasse pas zIterationMax spécifié li-1

