# Example: a Connect Four engine

In this section I will show an example of two Connect Four engines:
* One uses 2D array data structure
* The second uses a Bitboard data structure

### Structures and methods

Only two structures will be useful:
* `Move`: represent a move of the game
* `State`: represent a state of the game (player to play and board representation)

The methods we will need to write are:
* `void play(State * state, Move move)`: plays a move by directly modifying the state
* `EndGame isEnd(State state)`: to know if the game is finished or not and what is the result
* `vector<Move*> getMoves(State state)`: return the available moves for current player

And now let's code !

# First version: 2D vectors engine

::: Just give me the code
```C++ runnable
#include "moteur.h"

// Copier un état
Etat * copieEtat( Etat * src ) {
	Etat * etat = (Etat *)malloc(sizeof(Etat));
  etat->joueur = etat->joueur;
	uint i,j;
	for (i=0; i< HAUTEUR; i++)
		for (j=0; j<LARGEUR; j++)
			etat->plateau[CELL(j,i)] = src->plateau[CELL(j,i)];
	return etat;
}

// Etat initial
Etat * etatInitial( void ) {
	Etat * etat = (Etat *)malloc(sizeof(Etat));
	uint i,j;
	for (i=0; i< HAUTEUR; i++)
		for (j=0; j<LARGEUR; j++)
			etat->plateau[CELL(j,i)] = -1;
	return etat;
}

void afficheJeu(Etat * etat) {
	uint i,j;
	char symbs[3] = ".OX";
	printf("   |");
	for ( j = 0; j < LARGEUR; j++)
		printf(" %d |", j);
	printf("\n");
	printf("--------------------------------");
	printf("\n");

	for(j=0; j < HAUTEUR; j++) {
		printf(" %d |", j);
		for ( i = 0; i < LARGEUR; i++)
			printf(" %c |", symbs[etat->plateau[CELL(i,j)]+1]);
		printf("\n");
		printf("--------------------------------");
		printf("\n");
	}
}

// Demander à l'humain quel coup jouer
uint demanderCoup() {
	uint coup;
	printf(" quelle colonne ? ") ;
	scanf("%u",&coup);
	return coup;
}

// Modifier l'état en jouant un coup
// retourne 0 si le coup n'est pas possible
uint jouerCoup(Etat* etat, uint col) {
	// printf("test: %d\n", etat->plateau[CELL(col, HAUTEUR-1)] != -1);
  if (etat->plateau[CELL(col, HAUTEUR-1)] != -1)
    return 0;
	// printf("ok\n");
  for (int i=0; i<HAUTEUR; i++) {
		if (etat->plateau[CELL(col, i)] == -1) {
			etat->plateau[CELL(col, i)] = etat->joueur;
			break;
		}
	}
	etat->joueur = AUTRE_JOUEUR(etat->joueur);
  return 1;
}

// Retourne une liste de coups possibles à partir d'un etat
// (tableau de pointeurs de coups se terminant par NULL)
int * coupsPossibles( Etat * etat ) {
	uint k = 0, col;
	int *coups;
	coups = (int *)malloc(sizeof(int)*(LARGEUR+1));
	for (col=0; col<LARGEUR; col++) {
	// printf("x %d, y %d, exp %d, cell %d\n", col, HAUTEUR-1, (HAUTEUR-1)*LARGEUR+col, CELL(col, HAUTEUR-1));
		if (etat->plateau[CELL(col, HAUTEUR-1)] == -1) {
			coups[k] = col;
			k++;
		}
	}
	coups[k] = -1;
	return coups;
}

bool estGagnant(Etat * etat, uint joueur) {
	uint i,j;

	// horizontalCheck
  for (j=0; j<HAUTEUR-3 ; j++ ){
      for (i=0; i<LARGEUR; i++){
          if (etat->plateau[CELL(i,j)] == (int)joueur && etat->plateau[CELL(i,j+1)] == (int)joueur && etat->plateau[CELL(i,j+2)] == (int)joueur && etat->plateau[CELL(i,j+3)] == (int)joueur){
              return true;
          }
      }
  }
  // verticalCheck
  for (i=0; i<LARGEUR-3 ; i++){
      for (j=0; j<HAUTEUR; j++){
          if (etat->plateau[CELL(i,j)] == (int)joueur && etat->plateau[CELL(i+1,j)] == (int)joueur && etat->plateau[CELL(i+2,j)] == (int)joueur && etat->plateau[CELL(i+3,j)] == (int)joueur){
              return true;
          }
      }
  }
  // ascendingDiagonalCheck
  for (i=3; i<LARGEUR; i++){
      for (j=0; j<HAUTEUR-3; j++){
          if (etat->plateau[CELL(i,j)] == (int)joueur && etat->plateau[CELL(i-1,j+1)] == (int)joueur && etat->plateau[CELL(i-2,j+2)] == (int)joueur && etat->plateau[CELL(i-3,j+3)] == (int)joueur)
              return true;
      }
  }
  // descendingDiagonalCheck
  for (i=3; i<LARGEUR; i++){
      for (j=3; j<HAUTEUR; j++){
          if (etat->plateau[CELL(i,j)] == (int)joueur && etat->plateau[CELL(i-1,j-1)] == (int)joueur && etat->plateau[CELL(i-2,j-2)] == (int)joueur && etat->plateau[CELL(i-3,j-3)] == (int)joueur)
              return true;
      }
  }
  return false;

}

bool estPartieNulle(Etat * etat) {
	uint cell;
	for (cell=0; cell<LARGEUR*HAUTEUR; cell++) {
		if (etat->plateau[cell] == -1)
			return false;
	}
	return true;
}
// Test si l'état est un état terminal
// et retourne NON, MATCHNUL, ORDI_GAGNE ou HUMAIN_GAGNE

FinDePartie testFin(Etat * etat) {
	if (estGagnant(etat, 1))
    return ORDI_GAGNE;
  else if (estGagnant(etat, 0))
    return HUMAIN_GAGNE;
  else if (estPartieNulle(etat))
    return MATCHNUL;
  return NON;
}
```
:::

# Second version: Bitboard engine
