/***
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 * 
 * @Autheur: RACHEL SYSTEME
 * DATE : 22/06/2022
 * 
 * @tester sur la carte arduino uno et méga
 * 
 * Ce programme permet d'écrire sur un écran LCD I2C 16x2 à partir d'un clavier
 * de taille 4x4 constitué des boutons poussoir.
 * 
 * Caractères possible : A à Z, de 0 à 9 et le caractère espacé.
 * Options : Supprimer, changement de ligne, changement de clavier(numérique ou pas)
 * 
 * Contrainte : l'appui simultané de deux boutons peut ou ne pas être lu
 * correctement seul un bouton est lu à la fois.
***/
#include<LiquidCrystal_I2C.h> 		// Insertion de la bibliothèque lcd i2c

LiquidCrystal_I2C lcd(0x27,16,2);   // Objet de type LiquidCrystal_I2C
const uint8_t LIGNE[4]	={6,7,8,9}; //tableau pour stocker les pins des lignes
const uint8_t COLONNE[4]={2,3,4,5}; //tableau pour stocker les pins des colonnes

// Variable contenant les messages à afficher sur chaque ligne de l'écran lcd 16x2
String msgLigne_1 = "";
String msgLigne_2 = "";
bool mode = false; // false(alphabet); true(numérique)

// Prototypes des fonctions
char saisie(void);
char traitementAppuie(uint8_t ligne, uint8_t colonne);
void affiche(char Char);

// Pogramme initial
void setup() {
	lcd.init(); 		// Initialisation de l'écran lcd
	lcd.backlight();	// Retro éclairage de l'écran lcd
	lcd.clear(); 		// Néttoyage de l'écran
	lcd.setCursor(0,0);	// position du curseur 
	lcd.cursor();  		// affiche le curseur
	lcd.blink();
	/*
		Mise en OUTPUT(sortie) et HIGH(haut) des lignes et INPUT_PULLUP(entrée)
		des colonnes : entrée avec activation de la résistance interne de l'arduino.
	*/ 
	for (int i=0;i<4;i++){
		pinMode(LIGNE[i], OUTPUT);
		digitalWrite(LIGNE[i],HIGH);
		pinMode(COLONNE[i], INPUT_PULLUP);
	}
}

// Programme initial
void loop() {
	char Char = saisie(); //appel de la fonction saisie
	affiche(Char); 		  //appel de la fonction affiche
	delay(100);			  //petite attente
}

/**
 * Fonction de lecture du bouton appuyer.
 * Ne lit qu'un seul bouton appuyer. Si '2' boutons appuyé à la fois,
 * Seul le bouton à l'indice inférieur sera lu. 
 * 
 * type : char
 * paramètre: void
 * retour : caractère correspondant au bouton appuyer
 * retour par défaut: '\0'
**/
char saisie(){
	char Char='\0';							
	for (int l = 0; l < 4; l++){ 				// boucle qui parcourt le tableau des lignes
		digitalWrite(LIGNE[l], LOW); 			// On place la LIGNE en LOW (active)
		for (int c = 0; c < 4; c++) { 			// boucle qui parcourt le tableau des colonnes
			bool etat=!digitalRead(COLONNE[c]); // On lit le bouton appuyé
			if(etat==true){
				Char = traitementAppuie(l,c);	//appel de la fonction traitementAppuie	
				digitalWrite(LIGNE[l], HIGH); 
				return Char; 					// fin de la fonction
			}
		}
		digitalWrite(LIGNE[l], HIGH); 			// On place la LIGNE en HIGH (désactive)
	}
	return Char; // fin de la fonction
}

/**
 * Fonction de sélection du caractère correspondant au bouton appuyé
 * Utiliser dans la fonction "saisie()"
 * type : char
 * paramètre : 
 * 		uint8_t ligne  : ligne sur laquelle se trouve le bouton 
 * 		uint8_t colonne: colonne sur laquelle se trouve le bouton 
 * retour : caractère correspondant au bouton appuyer
 **/
char traitementAppuie(uint8_t ligne, uint8_t colonne){
	static char caractere='\0';	
	// Ligne 1
	if(ligne==0 and colonne==0){
		if(mode==false){
			if (caractere=='A'){caractere='B';}
			else if(caractere=='B'){caractere='A';}
			else{caractere='A';}
		}
		else
			caractere='1';
		return caractere; // fin de la fonction
	}
	else if(ligne==0 and colonne==1){
		if(mode==false){
			if (caractere=='C'){caractere='D';}
			else if(caractere=='D'){caractere='C';}
			else{caractere='C';}
		}
		else
			caractere='2';
		return caractere; // fin de la fonction
	}
	else if(ligne==0 and colonne==2){
		if(mode==false){
			if (caractere=='E'){caractere='F';}
			else if(caractere=='F'){caractere='E';}
			else{caractere='E';}
		}
		else
			caractere='3';
		return caractere; // fin de la fonction
	}
	else if(ligne==0 and colonne==3){
		// '-' Permet la suppression du caractère	
		return '-'; // fin de la fonction
	}
	// Ligne 2
	else if(ligne==1 and colonne==0){
		if(mode==false){
			if (caractere=='G'){caractere='H';}
			else if(caractere=='H'){caractere='G';}
			else{caractere='G';}
		}
		else
			caractere='4';
		return caractere; // fin de la fonction
	}
	else if(ligne==1 and colonne==1){
		if(mode==false){
			if (caractere=='I'){caractere='J';}
			else if(caractere=='J'){caractere='I';}
			else{caractere='I';}
		}
		else
			caractere='5';
		return caractere; // fin de la fonction
	}
	else if(ligne==1 and colonne==2){
		if(mode==false){
			if (caractere=='K'){caractere='L';}
			else if(caractere=='L'){caractere='K';}
			else{caractere='K';}
		}
		else
			caractere='6';
		return caractere; // fin de la fonction
	}
	else if (ligne==1 and colonne==3){
		// '_' Permet le changement de ligne
		return '_'; // fin de la fonction
	}
	// Ligne 3
	else if(ligne==2 and colonne==0){
		if(mode==false){
			if (caractere=='M'){caractere='N';}
			else if(caractere=='N'){caractere='M';}
			else{caractere='M';}
		}
		else
			caractere='7';
		return caractere; // fin de la fonction
	}
	else if(ligne==2 and colonne==1){
		if(mode==false){
			if (caractere=='O'){caractere='P';}
			else if(caractere=='P'){caractere='O';}
			else{caractere='O';}
		}
		else
			caractere='8';
		return caractere; // fin de la fonction
	}
	else if(ligne==2 and colonne==2){
		if (mode==false){
			if (caractere=='Q'){caractere='R';}
			else if(caractere=='R'){caractere='Q';}
			else{caractere='Q';}
		}
		else
			caractere='9';
		return caractere; // fin de la fonction
	}
	else if(ligne==2 and colonne==3){
		caractere = ' ';
		return caractere; // fin de la fonction
	}
	// Ligne 4
	else if(ligne==3 and colonne==0){
		if(mode==false){
			if (caractere=='S'){caractere='T';}
			else if(caractere=='T'){caractere='S';}
			else{caractere='S';}
		}
		else
			caractere='0';
		return caractere; // fin de la fonction
	}
	else if(ligne==3 and colonne==1){
		if(mode==false){
			if (caractere=='U'){caractere='V';}
			else if(caractere=='V'){caractere='W';}
			else if(caractere=='W'){caractere='U';}
			else{caractere='U';}
			return caractere; // fin de la fonction
		}
	}
	else if(ligne==3 and colonne==2){
		if(mode==false){
			if (caractere=='X'){caractere='Y';}
			else if(caractere=='Y'){caractere='Z';}
			else if(caractere=='Z'){caractere='X';}
			else{caractere='X';}
			return caractere; // fin de la fonction
		}
	}
	else if(ligne==3 and colonne==3){
		// Permet de selectionner le mode numérique ou alphabet
		mode = not mode;
		return '\0';
	}
}

/**
 * Fonction d'affichage des caractères sur l'écran lcd i2c
 * 
 * type : void
 * paramètre: caractère à afficher
**/
void affiche(char Char){
	// position curseur de l'ecran
	static uint8_t posCol_ligne_1 = 0;  // position du curseur sur la ligne 1
	static uint8_t posCol_ligne_2 = 0;  // position du curseur sur la ligne 2
	static bool posLine = 0;// Ligne se trouvant le curseur(0=row1, 1=row2)

	// Si le caractère est différent de NULL on affiche
	if (Char != '\0'){
		//-------------------Suppression des caractères sur l'écran lcd
		if (Char=='-'){
			// Supression ligne 1
			if (posCol_ligne_1 > 0 and posCol_ligne_1 <= 16 and posLine == 0){
				posCol_ligne_1--;
				//----------- Mise à jour des caractères à afficher
				if (posCol_ligne_1 == 0){msgLigne_1="";}
				else{msgLigne_1 = msgLigne_1.substring(0,posCol_ligne_1);}
			}
			// Supression ligne 2
			if (posCol_ligne_2 > 0 and posCol_ligne_2 <= 16 and posLine == 1){
				posCol_ligne_2--;
				//----------- Mise à jour des caractères à afficher
				if (posCol_ligne_2 == 0){msgLigne_2="";}
				else{msgLigne_2 = msgLigne_2.substring(0,posCol_ligne_2);}
			}
		}
		//-------------------Changement de ligne du curseur
		if (Char=='_')
			posLine = not posLine; // Inversement de l'état de lecture

		//------------------- Affichage sur la première ligne
		if(posCol_ligne_1 <= 16 and posLine == 0){
			if(Char=='-' or Char=='_');  // on ne fait rien
			else if(posCol_ligne_1==16); // on ne fait rien
			else{// Mise à jour des caractères à afficher
				msgLigne_1 += Char;
				posCol_ligne_1++; 	// Incrémentation
			 }
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print(msgLigne_1);
			lcd.setCursor(0,1);
			lcd.print(msgLigne_2);
			// remise curseur sur la ligne 1
			lcd.setCursor((int)msgLigne_1.length(),0); 
		}
		//------------------- Affichage sur la deuxième ligne
		if(posCol_ligne_2 < 16 and posLine == 1){
			if (Char=='-' or Char=='_');// on ne fait rien
			else{// Mise à jour des caractères à afficher
				msgLigne_2 += Char;
				posCol_ligne_2++; 	// Incrémentation
			}
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print(msgLigne_1);
			lcd.setCursor(0,1);
			lcd.print(msgLigne_2); 								
		}
	}// Fin condition non null ('\0')
}