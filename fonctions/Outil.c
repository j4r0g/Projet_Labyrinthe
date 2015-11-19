#include "Outil.h"

#define kuAntiSlashZerO 1 //encombrement du caractère "\0" qui délimite les chaînes de caractères
#define kcEchappemenT1 -61
#define kcEchappemenT2 -59
#define knEcrisMaX 63
#define kuIntegerMaX INT_MAX //constante prédéfinie dans la bibliothèque <limits.h>
#define kuOctetGererMaX  255
#define kuWhileMaX 5 //nb max de while imbriqués (si des appels récursifs imbriquent un grand nombre de while, augmenter sensiblement cette valeur)
//constantes et variables:
int bEcriS[1+knEcrisMaX];//dédié routines s0,s1
int nEcriS=0;//initialisation vitale ici car OutilAmorcer n'a pas encore été appelé à l'appel de s0() en tête de main();pour s0() et s1()
int ipWhilE=0;//index de pile dédié While() et bWhile()
long zWhilE[1+kuWhileMaX];
int nOctetGereR0;
long yOctetGereR0[1+kuOctetGererMaX];
int nOctetGereR1;
long yOctetGereR1[1+kuOctetGererMaX];
int zuOctetGereR;
int bOutilAmorceR;//ie le module a bien été amorcé
const int knStopFlipFloP=7;//dédié routine FlipFlop()
//prototypes des routines privées (ie non publiques dc hors .h):
void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT0(char *sContexte,int bAssertion,int nParametre);
int bConsonnE2(char *sString,int *pnCodeCaractereRg);
int bLettrE2(char *sString,int *pnCodeCaractereRg);
void OctetGereR(char *sMalloc);
int bVoyellE2(char *sString,int *pnCodeCaractereRg);

void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	int bAssertion=bAssertion1 && bAssertion2 && bAssertion3 && bAssertion4 && bAssertion5 && bAssertion6;
	if (!bAssertion){
		AsserT0(sContexte,bAssertion1,1);
		AsserT0(sContexte,bAssertion2,2);
		AsserT0(sContexte,bAssertion3,3);
		AsserT0(sContexte,bAssertion4,4);
		AsserT0(sContexte,bAssertion5,5);
		AsserT0(sContexte,bAssertion6,6);
	}
	assert(bAssertion);
}//AsserT

void AsserT0(char *sContexte,int bAssertion,int nParametre){
	if (!bAssertion){
		printf("    *** Assertion fausse (paramètre n°%d)",nParametre);
		if (strlen(sContexte)>0)
			printf(" dans \"%s\"",sContexte,nParametre);
		printf(".\n");
	}
}//AsserT0

void assert2(int bAssertion1,int bAssertion2){
	AsserT("",bAssertion1,bAssertion2,kV,kV,kV,kV);
}//assert2

void assert3(int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//assert3

void assert4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//assert4

void assert5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//assert5

void assert6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//assert6

void Assert1(char *sContexte,int bAssertion1){
	AsserT(sContexte,bAssertion1,kV,kV,kV,kV,kV);
}//Assert1

void Assert2(char *sContexte,int bAssertion1,int bAssertion2){
	AsserT(sContexte,bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert2

void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//Assert3

void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//Assert4

void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//Assert5

void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Assert6

void b(int bBooleen){
	printf("%s\n",(bBooleen!=0)?"vrai":"faux");
}//b

void e(int iInteger){
	printf("%4d\n",iInteger);
}//e

void ee(int iInteger1,int iInteger2){
	printf("%%4d%4d\n",iInteger1,iInteger2);
}//ee

void eee(int iInteger1,int iInteger2,int iInteger3){
	printf("%4d%4d%4d\n",iInteger1,iInteger2,iInteger3);
}//eee

void s(char *sString){
	assert(sString!=0);
	printf("%s\n",sString);
}//s

void s2(char *sString1,char *sString2){
	ss(sString1,sString2);
}//s2

void s3(char *sString1,char *sString2,char *sString3){
	sss(sString1,sString2,sString3);
}//s3

void s4(char *sString1,char *sString2,char *sString3,char *sString4){
	ssss(sString1,sString2,sString3,sString4);
}//s4

void s5(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5){
	sssss(sString1,sString2,sString3,sString4,sString5);
}//s5

void sb(char *sString,int bBooleen){
	printf("%s:%s\n",sString,(bBooleen!=0)?"vrai":"faux");
}//sb

void se(char *sString,int iInteger1){
	si(sString,iInteger1);
}//se

void see(char *sString,int iInteger1,int iInteger2){
	sii(sString,iInteger1,iInteger2);
}//see

void seee(char *sString,int iInteger1,int iInteger2,int iInteger3){
	siii(sString,iInteger1,iInteger2,iInteger3);
}//seee

void si(char *sString,int iInteger1){
	printf("%s:%4d\n",sString,iInteger1);
}//si

void sii(char *sString,int iInteger1,int iInteger2){
	printf("%s:%4d%4d\n",sString,iInteger1,iInteger2);
}//sii

void siii(char *sString,int iInteger1,int iInteger2,int iInteger3){
	printf("%s:%4d%4d%4d\n",sString,iInteger1,iInteger2,iInteger3);
}//siii

void ss(char *sString1,char *sString2){
	Vrai2(sString1!=0,sString2!=0);
	printf("%s %s\n",sString1,sString2);
}//ss

void sss(char *sString1,char *sString2,char *sString3){
	Vrai3(sString1!=0,sString2!=0,sString3!=0);
	printf("%s %s %s\n",sString1,sString2,sString3);
}//sss

void ssss(char *sString1,char *sString2,char *sString3,char *sString4){
	Vrai4(sString1!=0,sString2!=0,sString3!=0,sString4!=0);
	printf("%s %s %s %s\n",sString1,sString2,sString3,sString4);
}//ssss

void sssss(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5){
	Vrai5(sString1!=0,sString2!=0,sString3!=0,sString4!=0,sString5!=0);
	printf("%s %s %s %s %s\n",sString1,sString2,sString3,sString4,sString5);
}//sssss

void Appel0(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme en cours...". Puis passe à la ligne. Vérifie le parenthésage des appels.
	Vrai2(sMessage!=0,nEcriS<knEcrisMaX);
	FlipFlop(1,&bEcriS[++nEcriS]);
	if (strlen(sMessage)==0){
		printf("Programme en cours...\n");
	} else printf("%s%s: tâche en cours...\n",sE(2*nEcriS),sMessage);
}//Appel0

void Appel1(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme terminé.". Puis passe à la ligne. Vérifie le parenthésage des appels.
	int nMessageLg=strlen(sMessage);
	Vrai2(sMessage!=0,nEcriS>0);
	FlipFlop(0,&bEcriS[nEcriS]);
	if (nMessageLg)
		printf("%s%s: tâche terminée.\n",sE(2*nEcriS),sMessage);
	else printf("Programme terminé.\n");
	nEcriS--;
	assert(nEcriS>=0);
	if (!nMessageLg){
		assert(nEcriS==0);//ie s0 et s1 sont correctt parenthésés
		assert(ipWhilE>=0);//si ok,il a bien été ajouté 1° un appel à While() avant chaque boucle while et 2° un appel à bWhile() dans ladite boucle
	}
}//Appel1

int bBit(char cCaractere){
	int bBit=(cCaractere=='0') || (cCaractere=='1');
	assert(bBit==0 || bBit==1);
	return(bBit);
}//bBit

int bBool(long yEntier){
	int bBool=(yEntier==0) || (yEntier==1);
	assert(bBool==0 || bBool==1);
	return(bBool);
}//bBool

char *sBool(long yValeur){
	//rend en clair la valeur booléenne de yValeur
	if (yValeur)
		return("vrai");
	else return("faux");
}//sBool

char *sC(char cAlphaNumeriqueOuEspace){
	//convertit cA en string;cA est censé être un caractère alphanumérique (donc non accentué) ou un espace
	char *sAccu=malloc(1+kuAntiSlashZerO);
	char sMotif[2];
	assert(isalnum(cAlphaNumeriqueOuEspace) || isspace(cAlphaNumeriqueOuEspace));//isspace: espace,saut de page,fin de ligne,retour chariot,tabulation.
	sMotif[0]=cAlphaNumeriqueOuEspace;
	sMotif[1]='\0';
	strcpy(sAccu,sMotif);
	OctetGereR(sAccu);
	return(sAccu);
}//sC

char *sC1(char *sA){
	//rend sA après avoir vérifié que son pointeur n'est pas nul
	assert(sA!=0);
	return(sA);
}//sC1

char *sC1p(char *sA){
	//concatène sA et "."
	assert(sA!=0);
	char *sAccu=sC2(sA, ".");
	return(sAccu);
}//sC1p

char *sC2(char *sA,char *sB){
	//concatène sA et sB
	int uRequis;
	Vrai2(sA!=0,sB!=0);
	uRequis=1+strlen(sA)+strlen(sB);
	char *sAccu=malloc(uRequis+kuAntiSlashZerO);
	strcpy(sAccu,sA);
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2

char *sC2b(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bBlancEnSus,nRequis;
	char *sAccu;
	Vrai2(sA!=0,sB!=0);
	nRequis=strlen(sA)+strlen(sB);
	assert(nRequis>=0);
	bBlancEnSus=(strlen(sA)>0) && (strlen(sB)>0);
	if (bBlancEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par strlen...Le 4 minimise les dégâts
	strcpy(sAccu,sA);
	if (bBlancEnSus)
		strcat(sAccu," ");
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2b

char *sC2bp(char *sA,char *sB){
	//concatène sA,sB et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC2b(sA,sB),".");//sC2b vérifie que sA et sB sont définis
	return(sAccu);
}//sC3bp

char *sC2p(char *sA,char *sB){
	//concatène sA,sB et "."
	char *sAccu=sC2(sC2(sA, sB),".");//sC2 vérifie que sA et sB sont définis
	return(sAccu);
}//sC2p

char *sC3(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC
	char *sAccu=sC2(sC2(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3

char *sC3b(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC2b(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3b

char *sC3bp(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC3b(sA,sB,sC),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3bp

char *sC3p(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "."
	char *sAccu=sC4(sA,sB,sC, ".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3p

char *sC4(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD
	char *sAccu=sC2(sC3(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4

char *sC4b(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC3b(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4b

char *sC4bp(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4bp

char *sC4p(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "."
	char *sAccu=sC2(sC4(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4p

char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE
	char *sAccu=sC2(sC4(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5

char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5b

char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC5b(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5bp

char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5p

char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6

char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC5b(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6b

char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC6b(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6bp

char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6p

char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7

char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC6b(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7b

char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC7b(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7bp

char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "."
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7p

char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8

char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC7b(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8b

char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8bp

char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "."
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8p

int nCaractere(char *sString){
	//rend le nombre de caractères de sString (et non pas le nombre de codes caractères,contrairt à strlen() qui renvoie 2 pour un seul "à")
	int nC=0;//index sur le code caractère courant de sString
	int nCaractere=0;
	int nChaineLg;
	char cCode;
	assert(sString!=0);
	for (nChaineLg=strlen(sString),nC=0;nC<nChaineLg;nC++){
		cCode=sString[nC];
		if ( isalpha(cCode) || isdigit(cCode) || bLettrE2(sString,&nC) ) //dernier terme: voyelle ou consonne avec un signe diacritique
			nCaractere++;
	}
	assert(nCaractere>=0);
	return(nCaractere);
}//nCaractere

int bChiffre(char cCaractere){
	//cCaractere est un chiffre décimal
	int bChiffre=bDecit(cCaractere);
	return(bChiffre);
}//bChiffre

char *sChoix0(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide.
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? strlen(sOption) : 0;
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	if (bOption)
		strcpy(sCopie,sOption);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix0

char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative){
	//rend sOption si bOptionSinonAlternative est vrai; sinon,rend sAlternative.
	int nRequis;
	Vrai2(sOption!=0,sAlternative!=0);
	nRequis = bOptionSinonAlternative? strlen(sOption) : strlen(sAlternative);
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	if (bOptionSinonAlternative)
		strcpy(sCopie,sOption);
	else strcpy(sCopie,sAlternative);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix

void Confirmer(char *sMessage){
	char cCar;
	printf("%s Valider SVP (touche entrée)",sMessage);
	scanf("%c",&cCar);
	printf(" Merci d'avoir validé.\n");
}//Confirmer

int bConsonnE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knConsonne1LiM 21
    #define knConsonne2LiM 04
	int nConsonne1[knConsonne1LiM]={64,65,66,67,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,89};//consonnes sans signe diacritique
	int nConsonne2[knConsonne2LiM]={79,89,111,121};//ççÑñ";
	int bConsonne2=0;
	Vrai2(sString!=0,pnCodeCaractereRg!=0);
	Croit(0,2,strlen(sString));
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bConsonne2=isalpha(cCode);//consonne ou voyelle sans signe diacritique (accents,cédille,tilde...)
	if (bConsonne2){//consonne?
		assert(0);//ie code actuellt non exécuté vu le contexte des appels à bConsonnE2()
		for (bConsonne2=0,nCar=0; nCar<knConsonne1LiM; nCar++)
			bConsonne2=bConsonne2||(cCode==-nConsonne1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sString)) {//l'accès à sString[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knConsonne2LiM; nCar++)
				bConsonne2=bConsonne2||(cCode==-nConsonne2[nCar]);
			if (bConsonne2)
				(*pnCodeCaractereRg)++;
		}
	}
	return(bConsonne2);
}//bConsonnE2

char *sCouple(int iEntierA,int iEntierB){
	//rend la chaîne (iEntierA,iEntierB)	
	char *sCouple=sP(sC3(sEntier(iEntierA),",",sEntier(iEntierB)));
	OctetGereR(sCouple);
	return(sCouple);
}//sCouple

void Croit(int iMinInclus,int iDedans,int iMaxInclus){
	if (!bCroit(iMinInclus,iDedans,iMaxInclus))
		printf("BUG ds bCroit:%d≤%d≤%d est FAUX\n",iMinInclus,iDedans,iMaxInclus);
	assert(bCroit(iMinInclus,iDedans,iMaxInclus));
}//Croit

int bCroit(int iMinInclus,int iDedans,int iMaxInclus){
	int bCroit=(iMinInclus<=iDedans) && (iDedans<=iMaxInclus);
	return(bCroit);
}//bCroit

int bCroitStrict(int iMinExclu,int iDedans,int iMaxExclu){
	int bCroitStrict=(iMinExclu<iDedans) && (iDedans<iMaxExclu);
	return(bCroitStrict);
}//bCroit

void CroitStrict(int iMinExclu,int iDedans,int iMaxExclu){
	if (!bCroitStrict(iMinExclu,iDedans,iMaxExclu))
		printf("BUG ds bCroitStrict:%d<%d<%d est FAUX\n",iMinExclu,iDedans,iMaxExclu);
	assert(bCroitStrict(iMinExclu,iDedans,iMaxExclu));
}//CroitStrict

int bDecit(char cCaractere){
	//cCaractere est un chiffre décimal;cache la fonction isdigit()
	int bDecit=isdigit(cCaractere);
	return(bDecit);
}//bDecit

void Dis(char *sString){//affiche la valeur de la chaîne;comme s()
	s(sString);
}//Dis

char *sE(int nEspace){
	//nEspace blancs juxtaposés
	char *sE=sFois(nEspace,' ');
	return(sE);
}//sE

char *sEntier(int iEntier){
	//convertit iEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%d",iEntier);//iEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntier

char *sEntierAvecSigne(int iEntier){
	//// "+5" ou "-5" ou " 0"
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%+d",iEntier);//iEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntierAvecSigne

char *sEst(int bAssertion){
	//rend "est" tel quel,ou négativé avec "n'"..."pas" si bAssertion est faux 
	#define kuEstLg 3//"est"
	#define kuNestPasLg 4//"n'est pas"
	char *sEst=malloc( kuAntiSlashZerO + (bAssertion)? kuEstLg : kuNestPasLg);
	if (bAssertion)
		strcat(sEst,"est");
	else strcpy(sEst,"n'est pas");
	OctetGereR(sEst);
	return(sEst);
}//sEst

int bFaux(int iQuelconque){
	//rend la constante entière kV (vrai) si iQuelconque==0 et la constante kF (faux) sinon
	int bFaux=(iQuelconque==0) ? 1 : 0;
	return(bFaux);
}//bFaux

void FlipFlop(int bNouvelEtat,int *pbFlipFlop){
	//bascule *pbFlipFlop après avoir vérifié que la valeur booléenne de bNouvelEtat bascule effectivt à chaque appel de FlipFlop
	/*if (bNouvelEtat==*pbFlipFlop)
		Stop(knStopFlipFloP);*/
	assert(bNouvelEtat!=*pbFlipFlop);
	*pbFlipFlop=bNouvelEtat;
}//FlipFlopdddd

char *sFois(int nFois,char cMotif){
	//juxtapose nFois cMotif
	int uF;
	char *sFwa;
	char cFwa[2];
	Vrai2(nFois>=0,isprint(cMotif));//implique 1 code caractère par caractère,dc cMotif ne peut coder un "é" car il est occupe 2 codes caractères.
	sFwa=malloc(nFois+kuAntiSlashZerO);
	cFwa[0]=cMotif;
	cFwa[1]='\0';
	strcpy(sFwa,cFwa);
	for (uF=2;uF<=nFois;uF++)
		strcat(sFwa,cFwa);
	OctetGereR(sFwa);
	return(sFwa);
}//sFois

int nHasard(int uBorneLim){
	//rend un nombre aléatoire ds [0..uBorneLim[
	int nHasard;
	Croit(1,uBorneLim,kuIntegerMaX-1);
	nHasard=rand()%uBorneLim;
	Croit(0,nHasard,uBorneLim-1);
	return(nHasard);
}//nHasard

int uHasard(int uBorneMax){
	//rend un nombre aléatoire ds [1..nBorneMax]
	int uHasard;
	Croit(1,uBorneMax,kuIntegerMaX);
	uHasard=1+rand()%uBorneMax;
	Croit(1,uHasard,uBorneMax);
	return(uHasard);
}//uHasard

int bImpair(int iEntier){
	int bImpair=bVrai(iEntier%2);
	assert(bBool(bImpair));
	return (bImpair);
}//bImpair

long yInf(long yA,long yB){
	//rend inf(yA,yB);identique à yMin(yA,yB)
	long yInf=(yA>yB)?yB:yA;
	return(yInf);
}//yInf

int bLettre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (accent,cédille,tilde...);cache la fonction isalpha()
	int bLettre=isalpha(cCaractere);
	return(bLettre);
}//bLettre

int bLettrE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	char cCode;
	int bLettrE2=0;
	assert(sString!=0);
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bLettrE2=isalpha(cCode);//vrai si consonnes ou voyelles sans signe diacritique (accent,cédille,tilde...)
	if ( !bLettrE2 && (*pnCodeCaractereRg<strlen(sString)) ) {//l'accès à sString[nCodeCaractereRg+1] est valide
		bLettrE2=bVoyellE2(sString,pnCodeCaractereRg) || bConsonnE2(sString,pnCodeCaractereRg);
	}
	return(bLettrE2);
}//bLettrE2

void Ligne(){
	printf("\n");
}//Ligne

int bLigne(){
	Ligne();
	return(1);
}//bLigne

long yMax(long yA,long yB){
	//rend max(yA,yB);identique à ySup(yA,yB)
	long yMax=(yA>yB)?yA:yB;
	return(yMax);
}//yMax

void MemIntRaz(int piMemOrigine[],int nItemEnTout){
	Vrai2(piMemOrigine!=0,nItemEnTout>=0);
	MemIntValuer(piMemOrigine,nItemEnTout,0);
}//MemIntRaz

void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur){
	int nItem;
	Vrai2(piMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		piMemOrigine[nItem]=iValeur;
	}
}//MemIntValuer

void MemLongRaz(int pyMemOrigine[],int nItemEnTout){
	Vrai2(pyMemOrigine!=0,nItemEnTout>=0);
	MemLongValuer(pyMemOrigine,nItemEnTout,0);
}//MemLongRaz

void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur){
	int nItem;
	Vrai2(pyMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		pyMemOrigine[nItem]=yValeur;
	}
}//MemLongValuer

long yMin(long yA,long yB){
	//rend min(yA,yB);identique à yInf(yA,yB)
	long yMin=(yA>yB)?yB:yA;
	return(yMin);
}//yMin

int bMajuscule(char cCaractere){
	//cCaractere est une lettre majuscule sans signe diacritique (accent,cédille,tilde...);cache la fonction isupper()
	int bMajuscule=isupper(cCaractere);
	return(bMajuscule);
}//bMajuscule

int bMinuscule(char cCaractere){
	//cCaractere est une lettre minuscule signe diacritique (accent,cédille,tilde...);cache la fonction islower()
	int bMinuscule=islower(cCaractere);
	return(bMinuscule);
}//bMinuscule

int uModulo1(int uDividende,int uDiviseur){
	//rend le modulo standard à ceci près que le résultat 0 éventuel est remplacé par uDiviseur: uModulo1(12,4)=4 
	int nModulo;
	Vrai2(uDividende>0,uDiviseur>0);
	nModulo=uDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0)//ou 1 pr que li+1 soit exécutée 
		seee("uModulo1",uDividende,uDiviseur,nModulo);
	Croit(1,nModulo,uDiviseur);
	return(nModulo);
}//uModulo1

char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation){
	//rend sVerbe suivi de sAffirmation,ou négativé avec "ne" et sNegation si bNegativer
	#define kuNegationEtBlancLgMax 4
	Vrai4(sVerbe!=0,bBool(bNegativer),sAffirmation!=0,sNegation!=0);
	char *sNie=malloc(strlen(sVerbe)+ySup(strlen(sAffirmation),strlen(sNegation))+kuNegationEtBlancLgMax);
	if (bNegativer){
		strcpy(sNie,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sNie,sVerbe);
	}
	else strcpy(sNie,sVerbe);
	strcat(sNie," ");
	if (bNegativer)
		strcat(sNie,sNegation);
	else strcat(sNie,sAffirmation);
	OctetGereR(sNie);
	return(sNie);
}//sNie

void OctetGereR(char *sMalloc){
	//prend note de l'allocation de sMalloc sur l'espace courant et libère le demi-espace le plus ancien si cette allocation sature l'espace courant
	int nAlloc;
	char *sAlloc;
	if (zuOctetGereR==0){
		yOctetGereR0[nOctetGereR0++]=(long) sMalloc;
		if (nOctetGereR0>=kuOctetGererMaX){
			Confirmer("Changement de demi-espace de chaînes de caractères (0 vers 1)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR1[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR1[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR1=0;//premier index valide sur le futur demi-espace 
		}
	} else {
		yOctetGereR1[nOctetGereR1++]=(long) sMalloc;
		if (nOctetGereR1>=kuOctetGererMaX){
			Confirmer("Changement de demi-espace de chaînes de caractères (1 vers 0)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR0[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR0[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR0=0;//premier index valide sur le futur demi-espace
		}
	}
}//OctetGereR

void OutilAMORCER(){
	//amorce le présent module une fois pour toutes
	//NB ne toucher ni à nEcriS ni à bEcriS[] utilisés avant l'amorçage;
	assert(nEcriS==1);//vu l'appel s0("") en tête du main();pour s0() et s1()
	assert(strlen("à")>1);//ATTENTION: strlen("à")==2 et strlen("a")==1. strlen() ne compte plus des caractères mais des codes caractères,d'où le 2.
	bOutilAmorceR=kV;
}//OutilAMORCER

void OutilINITIALISER(){
	//relance le présent module
	Vrai(bOutilAmorceR);
}//OutilINITIALISER

void OutilTESTER(int iTest){
	int uFois;
	int nT[1+10];
	#define kuConsonneEnTout 44
	#define kuVoyelleEnTout 47
	Appel0(sC2("OutilTESTER,test n°",sEntier(iTest)));
		char *skConsonne="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
		char *skVoyelle="ÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		char *skLettre="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		switch (iTest) {
			case 01:	printf("Le graphe %s un circuit\n",sPas("contient",1)); break;
			case 02:	printf("Le graphe %s un circuit\n",sPas("contient",0)); break;
			case 03:	printf("Il %s circuit\n",sNie("y a",1,"un","aucun")); break;
			case 04:	printf("Il %s boucle\n",sNie("y a",0,"une","aucune")); break;
			case 10:	printf("test des fonctions de concaténation:\n");
			case 11:	printf("11AVANT%sAPRES\n",sC1("a"));
			case 12:	printf("12AVANT%sAPRES\n",sC2("b","c"));
			case 13:	printf("13AVANT%sAPRES\n",sC2b("d","e"));
			case 14:	printf("14AVANT%sAPRES\n",sC2b("f",""));
			case 15:	printf("15AVANT%sAPRES\n",sC2b("","g"));
			case 16:	printf("16AVANT%sAPRES\n",sC2b("",""));
			case 17:	printf("17AVANT%sAPRES\n",sC2bp("",""));
			case 18:	printf("18AVANT%sAPRES\n",sC1p(sC2bp("h", "i")));
			case 19:	printf("19AVANT%sAPRES\n",sC7bp("1","2","3","4","5","6","7"));break;
			case 30:	assert(strlen("étagé")>6);break;//e aigu occupe 2 codes caractères,vu strlen()
			case 50:	assert(nCaractere(skVoyelle)==kuVoyelleEnTout);break;
			case 51:	assert(nCaractere(skConsonne)==kuConsonneEnTout);break;
			case 52:	assert(nCaractere(skLettre)==kuVoyelleEnTout+kuConsonneEnTout);break;
			case 60:	for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [0..3]: %d.\n",nHasard(3));
						for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [1..4]: %d.\n",uHasard(4));
						break;
			case 70:	Titrer("salut");
						Titrer("");
						Titrer("solo");
						break;
			case 80:	printf("Texte: %s.\n",sFois(4,'z'));
						break;
			case 90:	for (uFois=1;uFois<10;uFois++)
							nT[uFois]=5;
						MemIntRaz(nT,10);
						break;
			default:
				break;
		}
	Appel1(sC2("OutilTESTER,test n°",sEntier(iTest)));
}//OutilTESTER

int bPair(int iEntier){
	int bPair=bFaux(iEntier%2);
	assert(bBool(bPair));
	return (bPair);
}//bPair

char *sP(char *sEntreParenthese){
	//rend sEntreParenthese précédé de "(" et suivi de ")"
	assert(sEntreParenthese!=0);	
	char *sP=sC3("(",sEntreParenthese,")");
	OctetGereR(sP);
	return(sP);
}//sP

char *sPas(char *sVerbe,int bNegativer){
	//rend sVerbe tel quel,ou négativé avec "ne"..."pas" si bNegativer 
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sPas=malloc(kuNeLg+strlen(sVerbe)+kuPasLg+kuAntiSlashZerO);
	if (bNegativer){
		strcpy(sPas,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sPas,sVerbe);
		strcat(sPas, " pas");
	}
	else strcpy(sPas,sVerbe);
	OctetGereR(sPas);
	return(sPas);
}//sPas

char *sPluriel(int nEffectif,char *sSingulier){
	//si sSingulier est "pomme",rend "3 pommes","1 pomme" ou "0 pomme",selon nEffectif;sSingulier est supposé prendre un "s" au pluriel
	char *sPluriel;
	Vrai2(nEffectif>=0,sSingulier!=0);
	sPluriel=sC2b(sEntier(nEffectif),sSingulier);
	if (nEffectif>1)
		sPluriel=sC2(sPluriel,"s");
	return(sPluriel);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel

char *sSigne(int iEntier){
	//"+" ou "-" ou " " selon le signe de iEntier
	char *sSigne=sChoix(iEntier>=0,"+","-");
	return(sSigne);
}//sSigne

void Stop(int nMassacre){
	exit(nMassacre);//arrêt catastrophe;le paramètre de exit() étant affiché à la fin de l'exécution, vous savez que Stop(nMassacre) a été appelé
}//Stop

long ySup(long yA,long yB){
	//rend sup(yA,yB);identique à yMax(yA,yB)
	long ySup=(yA>yB)?yA:yB;
	return(ySup);
}//ySup

void Titrer(char *sTitre){
	//affiche sTitre centré sur une ligne de kuTitreLargeur caractères de type kcMotif
	const int kuTitreLargeur=60;//où ce que vous voulez
	const char kcMotif='*';//où ce que vous voulez
	assert(sTitre!=0);
	int nTitreLg=nCaractere(sTitre);
	assert(nTitreLg<kuTitreLargeur);
	int nEspace=(kuTitreLargeur-nTitreLg)/2;//quitte à perdre un caractère
	int bUnMotifEnSus=bImpair(nTitreLg);//ie un kcMotif sera ajouté pr récupérer le caractère perdu li-1
	assert(nEspace+nTitreLg+nEspace+bUnMotifEnSus==kuTitreLargeur);
	printf("%s%s%s\n",sFois(nEspace,kcMotif),sTitre,sFois(nEspace+bUnMotifEnSus,kcMotif));
}//Titrer

void VecteurVoir(char *sTitre,int piQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche piQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Vrai2(sTitre!=0,piQuelVecteur!=0);
	Croit(0,nIndexMin,nIndexMax);
	s(sTitre);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%4d",piQuelVecteur[nE]);
	s("");
}//VecteurVoir

int bVirguler(){
	//affiche une virgule et rend vrai
	printf(",");
	return(kV);
}//bVirguler

int bVoyelle(char *sString,int nCodeCaractereRg){
	//sString[nCodeCaractereRg] ou Chaine[nCodeCaractereRg..nCodeCaractereRg+1] code une voyelle
	int nRg=nCodeCaractereRg;
	Vrai2(sString!=0,nCodeCaractereRg>=0);
	int bVoyelle=bVoyellE2(sString,&nRg);
	return(bVoyelle);
}//bVoyelle

int bVoyellE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une voyelle;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knVoyelle1LiM 29
	int nVoyelle1[knVoyelle1LiM]={65,68,69,71,74,76,81,82,86,87,     88,92,93,94,96,100,101,103,106,108,      113,114,117,118,119,124,125,126,128};
    #define knVoyelle2LiM 01
	int nVoyelle2[knVoyelle2LiM]={72};//aeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã";//piqûre Haüy;nValide2[1] pour le seul Ÿ
	int bVoyellE2=0;
	assert(sString!=0);
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bVoyellE2=isalpha(cCode);
	if (bVoyellE2){//voyelle ou consonne?
		for (bVoyellE2=0,nCar=0; nCar<knVoyelle1LiM; nCar++)
			bVoyellE2=bVoyellE2||(cCode==-nVoyelle1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sString)) {//l'accès à sString[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle1LiM; nCar++)
				bVoyellE2=bVoyellE2||(cCode==-nVoyelle1[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
		else if (cCode==kcEchappemenT2) {
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle2LiM; nCar++)
				bVoyellE2= bVoyellE2 || (cCode==-nVoyelle2[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
	}
	return(bVoyellE2);
}//bVoyellE2

void Vrai(int bAssertion){
	assert(bAssertion);
}//Vrai

int bVrai(int iQuelconque){
	//rend vrai ssi iQuelconque!=0
	int bVrai=(iQuelconque!=0) ? 1 : 0;
	return(bVrai);
}//bVrai

void Vrai2(int bAssertion1,int bAssertion2){
	assert2(bAssertion1,bAssertion2);
}//Vrai2

void Vrai3(int bAssertion1,int bAssertion2,int bAssertion3){
	assert3(bAssertion1,bAssertion2,bAssertion3);
}//Vrai3

void Vrai4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	assert4(bAssertion1,bAssertion2,bAssertion3,bAssertion4);
}//Vrai4

void Vrai5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	assert5(bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5);
}//Vrai5

void Vrai6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	assert6(bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Vrai6

void While(long zIterationMax){
	//prend note du nombre maximum d'itérations acceptable dans le while qui suit immédiatement l'appel de cette routine
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return, etc.
	assert(zIterationMax>=0);
	ipWhilE++;
	assert(ipWhilE<=kuWhileMaX);
	zWhilE[ipWhilE]=zIterationMax;
}//While

int bWhile(int bExpressionBooleenne){
	//rend bExpressionBooleenne tout en gérant l'itération en cours (ie son rang ne dépasse pas zIterationMax spécifié dans l'appel à While() qui précède
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return,etc
	Croit(0,ipWhilE,kuWhileMaX);
	zWhilE[ipWhilE]--;//décrémente le nombre d'itérations de la boucle imbriquée de rang ipWhilE
	assert(zWhilE[ipWhilE]>=0);
	if (bExpressionBooleenne==0){//la sortie imminente du while courant ramène le contexte ds la boucle imbriquée englobante,de rang ipWhilE-1
		zWhilE[ipWhilE]=0;//superflu mais ce nettoyage facilite la mise au point
		ipWhilE--;//vital
		assert(ipWhilE>=0);
	}//Chaque boucle while est donc contrôlée via 1° un appel à While() avant le while et 2° un appel à bWhile() dans l'expression booléenne liée au...
	return(bExpressionBooleenne);//...while; Appel1("") à la fin du main() vérifie que le contrôle des while est bien séquencé via "assert(ipWhilE>=0)".
}//bWhile




