
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"
#define MAX_INPUT_CHARS     4
#define  RADIUS     20.0f
#include <time.h>
#include <math.h>


/**********************************************************************/


/**-------------------STRUCTURES-------------------**/

///Structure de button

typedef struct Button{
Rectangle rect;
Color color;
bool pressed;
}Button;

//-----------------------------------------------------------------------------------------

///Structure du textField

typedef struct textField{
Rectangle textBox;
Color color;
char text[20];
bool mouseOn;
}textField;


///Structures de graphiques:
typedef struct Node{
Vector2 centre ;
float rayon;
Color col;
}Node;

typedef struct Branch{
Vector2 start;
Vector2 end;
}Branch;


//-----------------------------------------------------------------------------------------

typedef struct noeud noeud;
typedef struct noeud
{
    int info;
    struct noeud* fd; //fils (branch) droit
    struct noeud* fg; // fils (branch) gauche
    struct noeud* pere; //le pere
    Node noeudshape;
    Branch BrancheDroite;
    Branch BrancheGauche;
};

//-----------------------------------------------------------------------------------------


typedef noeud* arbre;

//-----------------------------------------------------------------------------------------


/**-------------------PROTOTYPES-------------------**/

///Dessiner le noeud d'un arbre
void DessinerNoeud(arbre* R, float x, float y, Color couleur, Font font);

//---------------------------------------------

///Fonction qui effectue le dessin de la branche :
void DessinerBranche(arbre* R, float Offset);

//---------------------------------------------

///Verifier si un noeud est vide:
int ArbreVide(arbre a);

//---------------------------------------------

///Retourner le fils gauche d'un noeud
arbre fils_Gauche(arbre a);

//---------------------------------------------

///Retourner le fils droit d'un noeud
arbre fils_Droit(arbre a);

//---------------------------------------------

///Retourner le pere d'un noeud
arbre Pere(arbre a);

//---------------------------------------------

///Verifier si ce noeud est une feuille
int feuille(arbre a);

//---------------------------------------------

///Affichage d'un arbre (Parcours Prefixe)
void prefixe(arbre a);

//---------------------------------------------

///Affichage d'un arbre (Parcours infixe (ordonne))
void infixe(arbre a);

//---------------------------------------------

///Affichage d'un arbre (Parcours postfixe )
void postfixe(arbre a);

//---------------------------------------------

///Retourner le nombre de noeud d'un arbre a
int nombre_de_noeuds(arbre a);

//---------------------------------------------

///Retourner l'adress d'un noeud portant une valeur a la recherche
arbre recherche_pointeur(arbre a, int val);

//---------------------------------------------

///Retourner un booelen qui indique si une valeur existe ou pas dans l'arbre
int recherche(arbre a, int val);

//---------------------------------------------

///Creation d'un noeud
arbre creer_noeud(int val);

//---------------------------------------------

///Creation d'un arbre avec des valeurs aleatoires
arbre Creer_Arbre(int max);

//---------------------------------------------

///Insertion d'une valeur dans un arbre (algorithme iteratif )
void insertion(arbre* a, int val);

//---------------------------------------------

///Insertion d'une valeur dans un arbre (algorithme recursif )
void inserer(arbre* a, int val, arbre pere);

//---------------------------------------------

///Retourner la valeur maximal existante dans un arbre
int maximum(arbre a);

//---------------------------------------------

///Suppression d'une valeur dans un arbre
void supprimer(arbre* a, int val, arbre pere);

//---------------------------------------------

///Dessin de l'arbre Binaire
void drawTree(arbre a, float x, float y, float levelHeight,Font font);

//---------------------------------------------

///Dessin d'un  boutton
void dessinerBoutton(float x, float y, float width, float height, char text[20], Font font, Button* button_0);

//---------------------------------------------

///Dessin d'une barre de texte avec tous les traitements necessaires
void DessinerBarreText(float x, float y, float width, float height, textField* Barre, int* framesCounter, int* letterCount);

//---------------------------------------------

///Dessin d'une fleche
void DrawArrow(Vector2 startPoint, Vector2 endPoint, Color col);
//---------------------------------------------



/**-------------------FONCTIONS GENERALES-------------------**/


///Verifier si un noeud est vide:
int ArbreVide(arbre a){
    if (a==NULL) return 1;
        else return 0;
}

//-----------------------------------------------------------------------------------------

///Retourner le Fils_Gauche (adresse):

arbre fils_Gauche(arbre a){
    return a->fg;
}

//-----------------------------------------------------------------------------------------

///Retourner le Fils_Droit (adresse):

arbre fils_Droit(arbre a){
    return a->fd;
}

//-----------------------------------------------------------------------------------------

///Retourner le Pere (adresse):

arbre Pere(arbre a){
    return a->pere;
}

//-----------------------------------------------------------------------------------------

///Verfifier si un noeud a est une feuille:

int feuille (arbre a){
    if (a->fd==NULL && a->fg==NULL) return(1) ;
     else
    return(0) ;
}

//-----------------------------------------------------------------------------------------

/**Les Parcours**/

///Prefixe (Preordre) ( Noeud --> fils_Gauche(R) --> fils_Droit(R) )

void prefixe (arbre a){
    if ( !ArbreVide (a)){
     printf("%d | ", a->info) ; //Noeud

      //1er appel recursif
     prefixe(fils_Gauche(a)) ;  //fils_Gauche

      //dexieme appel  recursif
     prefixe (fils_Droit(a)) ;  //fils_Droit
    }
  }

//-----------------------------------------------------------------------------------------
//test

///Infixe (Inordre) (Fils_Gauche --> Noeud --> Fils_Droit )

void infixe(arbre a) {
    if (ArbreVide(a)==0) {
        // 1er appel recursif
        infixe(fils_Gauche(a)); // fils_Gauche
        printf("\n %d |", a->info); // noeud (racine)
        //if(Pere(a)!=NULL) printf("\nLe pere de %d est %d", a->info, Pere(a)->info );
        // 2eme appel recursif
        infixe(fils_Droit(a)); // fils_Droit
    }
}

//-----------------------------------------------------------------------------------------

///Postfixe (Postordre) (Fils_Gauche --> Fils_Droit  --> Noeud)
    void postfixe (arbre a){
    if ( !ArbreVide (a)){

     //1er appel recursif
     postfixe(fils_Gauche(a)) ; //fils_Gauche

     //dexieme appel  recursif
     postfixe (fils_Droit(a)) ;  //fils_Droit

     printf(" %d | ", a->info) ; //Noeud (Racine)


    }
  }

//-----------------------------------------------------------------------------------------

int nombre_de_noeuds ( arbre a ) {
if (a==NULL) return 0 ;
return ( 1 + nombre_de_noeuds ( a->fg )
+ nombre_de_noeuds (a->fd ) ) ;
}


//-----------------------------------------------------------------------------------------

///Recherche dans un arbre binaire ordonne, Elle retourne une adresse ( le pointeur qui contient var)

arbre recherche_pointeur(arbre a, int val){
  if (ArbreVide(a)==1) return NULL;

  if (a->info==val){
     return a;
  }

  else {
     if (a->info>val) return  recherche(fils_Gauche(a),val);
       else return  recherche(fils_Droit(a),val);
    }
}

//-----------------------------------------------------------------------------------------

///Recherche dans un arbre binaire ordonne, Elle retourne un booleen

int recherche(arbre a, int val){
  if (ArbreVide(a)==1) return 0;

  if (a->info==val){
     return 1;
  }

  else {
     if (a->info>val) return  recherche(fils_Gauche(a),val);
       else return  recherche(fils_Droit(a),val);
    }
}

//-----------------------------------------------------------------------------------------

/**Insertion dans un arbre binaire ordonne**/

///Creation d'un noeud

arbre creer_noeud(int val){
  arbre p; //ptr vers le noeud
  //p=malloc(sizeof(noeud)); //Reservation d'un espace pour le noeud
  p= (arbre)malloc(sizeof(noeud));
  p->fg=NULL;
  p->fd=NULL;
  p->pere=NULL;
  p->info=val;
  return p;
}

//-----------------------------------------------------------------------------------------

///Creation

arbre Creer_Arbre(int max){
    int i, val;
    arbre r=NULL;

    srand(time(NULL));   // Initialization, should only be called once.

    for (i=1; i<=max ; i++ ){

        val = rand() % 100 + 1;
        insertion(& r, val);
    }

    return r;
}

//-----------------------------------------------------------------------------------------


///Insertion d'un noeud

///Sans Appel Recursif :

void insertion(arbre * a, int val){
     int insert; arbre r; //father=NULL;
     insert=0;
     r=*a;

     //si la valeur existe deja on va pas l'inserer
     if (recherche(*a, val)==1){printf("Insertion impossible, La Valeur %d existe deja dans l'arbre", val);}
     //sinon, si la valeur n'existe pas :
     else {
     //si l'arbre est vide
     if ((*a)==NULL){

         (*a)=creer_noeud(val);
         insert=1;
         //printf("\nRacine created");

     }

     while(insert==0){
          if (val< r->info){
              if (fils_Gauche(r)==NULL){
                 r->fg=creer_noeud(val);
                 fils_Gauche(r)->pere=r;
                  insert=1;
                }
              else{
                 //father=r;
                 r=fils_Gauche(r);
                }
                //printf("\nWORKS1");

            }
            else{
                if (val>r->info){
                    if (fils_Droit(r)==NULL){
                     r->fd=creer_noeud(val);
                     fils_Droit(r)->pere=r;
                     insert=1;
                    }
                    else{
                      r=fils_Droit(r);
                    }
                }
            }
            //printf("\nWORKS2");
        }
        //printf("\nla nouvelle valeur = %d \n", r->info);
       // r->pere=father;
        //printf("\nWORKS ALL");
     }

    }

//-----------------------------------------------------------------------------------------



///Avec appel recursif :

  void inserer(arbre* a, int val, arbre pere) {
    // dans le cas o� l'arbre n'est pas vide
    if (!ArbreVide(*a)) {
        // si la valeur existe d�j� on ne va pas l'ins�rer car on est dans un arbre de recherche
        if ((*a)->info == val)
            printf("\nLa valeur existe D�j�\n");
        // si la valeur n'existe pas dans l'arbre de recherche, on va l'ins�rer
        else {
            // si elle est inf�rieure � la racine, l'insertion est � gauche
            if ((*a)->info>val){
                inserer(&((*a)->fg), val, *a);
            }
            // si elle est sup�rieure � la racine, l'insertion est � droite
            else {
                 inserer(&((*a)->fd), val, *a);
            }
        }
    }
    // dans le cas o� l'arbre est vide
    else {
        // si le p�re qui est en entr�e (input) n'existe pas (nul)
        if (ArbreVide(pere)) {
            *a = creer_noeud(val);
            //racine
        }
        // sinon si le p�re qui est en entr�e (input) existe
        else {
            if (pere->info > val) {
                pere->fg = creer_noeud(val);
            } else {
                pere->fd = creer_noeud(val);
            }
        }
    }
}


//-----------------------------------------------------------------------------------------

/** Suppression d'un noeud dans un arbre :**/

///Fonction maximum qui retourne la plus grande valeur dans un arbre de recherche

int maximum(arbre a){
      if (ArbreVide(a->fd)){return a->info;}
      //car si il n'y a aucun cote droit, cela veut dire qu'il n'ya aucune valeur plus petite que la valeur de a, donc a est le max
      else {
        return maximum(fils_Droit(a));
      }
}

//-----------------------------------------------------------------------------------------

///Supression d'un noeud

void supprimer (arbre * a, int val, arbre pere){
      int max;

     if (ArbreVide(*a)==0){

         //si la valeur a supprimer n'est pas dans la racine a:
         if (((*a)->info)!=val){

             //cas de suppression a gauche
             if ((*a)->info>val){
                supprimer ((*a)->fg,val,*a);
                //supprimer(&(fils_Gauche(*a)),val,*a);
             }

             //cas de suppression a droite
             else{
                supprimer((*a)->fd,val,*a);
                //supprimer(&(fils_Droit(*a)),val,*a);
               }

            }


            //si la valeur a supprimer est dans la racine a:
            else{
             ///cas 1 : noeud est une feuille ( fils_droit et fils_gauche = nill)
              if (ArbreVide(fils_Gauche(*a))&&(ArbreVide(fils_Droit(*a)))){
                 if (pere->fg==*a){pere->fg=NULL; free(*a);}
                 else {pere->fd=NULL; free(*a);}
              }

             ///cas2 : noeud poss�de un seul fils : fils droit, ie: le fils droit est vide
              if (ArbreVide(fils_Gauche(*a))){
                  if(pere->fg==*a)
                    {pere->fg=fils_Droit(*a); free(*a);}
                  else
                    {pere->fd=fils_Droit(*a);free(a);}
              }


             ///cas3 : noeud poss�de un seul fils : fils gauche,  ie: le fils gauc est vide
             if (ArbreVide(fils_Droit(*a))){
                 if (pere->fg==*a){pere->fg=fils_Gauche(*a); free(*a);}
                 else {pere->fd=fils_Gauche(*a); free(*a);}
                }

             ///cas4 : Le neoud possede les deux fils :


             else { max=maximum(fils_Gauche(*a));
             (*a)->info=max;
             supprimer(fils_Gauche(*a), max, *a);
             //supprimer un noeud qui est soit une feuille soit un noeud avec un seul fils
             }

            }//end of else


        }



    }

//-----------------------------------------------------------------------------------------

/**-------------------FONCTIONS DESSIN SEULEMENT-------------------**/

void DrawArrow(Vector2 startPoint, Vector2 endPoint, Color col){

   // Dessin de la ligne
    DrawLineEx(startPoint, endPoint, 4, col);

    // Coordonnees des pointeur de fleches qui sont de cette forme ">":
    float angle = atan2f(endPoint.y - startPoint.y, endPoint.x - startPoint.x);
    Vector2 arrowhead1 = {
        endPoint.x - 20 * cosf(angle + PI/6),
        endPoint.y - 20 * sinf(angle + PI/6)
    };

    Vector2 arrowhead2 = {
        endPoint.x - 20 * cosf(angle - PI/6),
        endPoint.y - 20 * sinf(angle - PI/6)
    };

    // dessin de la forme ">":
    DrawLineEx(arrowhead1, endPoint, 3, col);
    DrawLineEx(arrowhead2, endPoint, 3, col);
}

//-----------------------------------------------------------------------------------------


///Dessiner le noeud d'un arbre
void DessinerNoeud(arbre * R, float x, float y, Color couleur, Font font ){

Vector2 point={x,y};

    //Affecter les valeurs / coordonnees necessaires
    (*R)->noeudshape.col=couleur;
    (*R)->noeudshape.rayon=RADIUS; ///this is a constant
    (*R)->noeudshape.centre=point;

    //Dessiner le circle:
    /*DrawCircle(int centerX, int centerY, float radius, Color color);*/
    DrawCircle(x, y, RADIUS, couleur );

    //dessiner le text:
    /*On dessine le texte de telle sorte qu'il soit au milieu du circle*/
    /*pour cela , voila en general l'appel de la fonction*/
    /*DrawText(text,Center_x - MeasureText(text, taillePolice) / 2 , y - taillePolice / 2 , taillePolice, MAROON);*/
    /*TextFormat est pour obtenir cette variable "a->info" en format textuel*/

    for (int i = 0; i < 15; ++i) {
            float angle = (float)i * 0.1f;
            DrawCircleLines(x , y , RADIUS + angle, MAROON);
        }
      DrawTextEx(font,TextFormat("%d", (*R)->info), (Vector2){x - MeasureText(TextFormat("%d", (*R)->info), 20) / 2 , y - 20 / 2} , 20,2, MAROON);

}

//-----------------------------------------------------------------------------------------


///Fonction qui effectue le dessin de la branche :

void DessinerBranche(arbre* R, float Offset){

    Vector2 startpoint, endpoint;

   float  x=(*R)->noeudshape.centre.x;
    float y=(*R)->noeudshape.centre.y;

    startpoint=(Vector2) {x, y};

       if ((*R)->fg!=NULL) {
        endpoint=(Vector2){ x - Offset, y + 80};
        DrawArrow(startpoint, endpoint, BLACK) ;
        }

      if ((*R)->fd!=NULL) {
        endpoint=(Vector2){ x + Offset, y + 80};
        DrawArrow(startpoint, endpoint, BLACK) ;
        }

}


//-----------------------------------------------------------------------------------------


///Fontion du dessin arbre sans changement dynamique des fleches

/**void drawTree(arbre a, float x, float y, float xOffset) {
    Vector2 startpoint, endpoint;
    if (!ArbreVide(a)) {
        // Draw the node
        float radius = 30.0f;

        // Draw lines to its children
        if (a->fg != NULL) {
                startpoint=(Vector2) {x, y};
                endpoint=(Vector2){ x - xOffset, y + 80};
               DrawArrow(startpoint, endpoint, BLACK) ;
              //DrawLine(x, y+radius, x - xOffset, y + 80, BLACK);  // Left branch
              drawTree(a->fg, x - xOffset, y + 80, xOffset );
        }

        if (a->fd != NULL) {
                startpoint=(Vector2){x, y};
                endpoint=(Vector2){ x + xOffset, y + 80};
                DrawArrow(startpoint, endpoint, BLACK) ;
            //DrawLine(x, y+radius, x + xOffset, y + 80, BLACK);  // Right branch
            drawTree(a->fd, x + xOffset, y + 80, xOffset );
        }

          DessinerNoeud(&a, x,y, WHITE);
    }
}*/

//-----------------------------------------------------------------------------------------


///Calculer la largeur de l'arbre avec une echelle pour les graphics (*30f) (enhanced for making the tree more spacy and more orgamized )

float calculateSubtreeWidth(arbre a) {
    if (ArbreVide(a)) return 0.0f;



    float leftWidth = calculateSubtreeWidth(a->fg);
    float rightWidth = calculateSubtreeWidth(a->fd);

    // Calculate width based on the sum of subtree widths and some padding
    return leftWidth + rightWidth + 20.0f;
}

//-----------------------------------------------------------------------------------------

///Fonction qui calcule la largeur d'un sous arbre a partir d'un noeud
/*
float calculateSubtreeWidth(arbre a) {

    if (ArbreVide(a)) return 0.0f;

    // Recursively calculate the graphical width of left and right subtrees
    float leftWidth = calculateSubtreeWidth(a->fg);
    float rightWidth = calculateSubtreeWidth(a->fd);

    // Include the current node's width
    return leftWidth + rightWidth + 1.0f;
}*/


//-----------------------------------------------------------------------------------------

///Fonction qui calcule la largeur d'un sous arbre a partir d'un noeud

int calculateSubtreeHeight(arbre a) {
    if (ArbreVide(a)) return 0;

    int leftHeight = calculateSubtreeHeight(a->fg);
    int rightHeight = calculateSubtreeHeight(a->fd);

    // Include the current node's height
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//-----------------------------------------------------------------------------------------




///Fontion qui dessine un arbre binaire de sorte que la largeur est traite
/*

void drawTree(arbre a, float x, float y, float levelHeight) {

    //cette variable "xOffseta" represente le deplacement des branche sur l'axe (ox),
    //chaque fois un nouveau noeud est ajoute, il faut regler ce deplacement pour eviter la collision entre les noeuds
    float xOffset=30.0f;

    if (!ArbreVide(a)) {

        // Calculate le nombre de noeud d'un sous-arbre
        int leftWidth = calculateSubtreeWidth(a->fg);
        int rightWidth = calculateSubtreeWidth(a->fd);

        // Calculate the total width of the subtree
        int totalWidth = leftWidth + rightWidth + 1;

        // Le deplacement est en fonction  de la moyenne entre l'hauteur et le nombre de noeuds
         xOffset = 20.0f * (calculateSubtreeHeight(a) +( nombre_de_noeuds(a)/2));


        // Dessin de la branche gauche
        if (a->fg != NULL) {
            Vector2 startpoint = { x, y };

            //le noeud est a droite du noeud de centre (x,y) donc le deplacement est negative sur l'axe de (ox)
            //le deplacement dans l'axe (oy) est constant et il est en fonction de l'hauteur de larbre courrant
            //et le point d'arrive est en dessus du noeud c'est pour cette raison en fait " -Radius "
            Vector2 endpoint = { x - xOffset, y + levelHeight };

            //dessin de la fleche
            DrawArrow(startpoint, endpoint, MAROON);
            //appel recursif pour le dessin du sous arbre'
            drawTree(a->fg, x - xOffset, y + levelHeight, levelHeight);
        }

        // Dessin de la branche droite

        if (a->fd != NULL) {
            Vector2 startpoint = { x, y };

            //le noeud est a gauche du noeud de centre (x,y) donc le deplacement est positif sur l'axe de (ox)
            Vector2 endpoint = { x + xOffset, y + levelHeight };
            DrawArrow(startpoint, endpoint, MAROON);
            drawTree(a->fd, x + xOffset, y + levelHeight, levelHeight);
        }

        // Dessiner le noeud a la fin pour que les fleches restent en dernier
        DessinerNoeud(&a, x, y, WHITE);
    }
}*/


//-----------------------------------------------------------------------------------------

///Fontion qui dessine un arbre binaire de sorte que la largeur est traite (ENHANCED)


void drawTree(arbre a, float x, float y, float levelHeight, Font font) {
    if (ArbreVide(a)) return;

   // Calculate la largeur d'un sous-arbre
    float totalWidth = calculateSubtreeWidth(a);

    //cette variable "xOffseta" represente le deplacement des branche sur l'axe (ox),
    //chaque fois un nouveau noeud est ajoute, il faut regler ce deplacement pour eviter la collision entre les noeuds

    // Le deplacement est en fonction  de la largeur/2
    float xOffset = totalWidth / 2.0f;

   // Dessin de la branche gauche
    if (a->fg != NULL) {

        //le noeud est a droite du noeud de centre (x,y) donc le deplacement est negative sur l'axe de (ox)
        //le deplacement dans l'axe (oy) est constant et il est en fonction de l'hauteur de larbre courrant
        //et le point d'arrive est en dessus du noeud c'est pour cette raison en fait " -Radius "

        Vector2 startpoint = { x, y };
        Vector2 endpoint = { x - xOffset, y + levelHeight };

        //dessin de la fleche
        DrawArrow(startpoint, endpoint, MAROON);
        //appel recursif pour le dessin du sous arbre'
        drawTree(a->fg, x - xOffset, y + levelHeight, levelHeight, font);
    }

    // Dessin de la branche droite
    if (a->fd != NULL) {
        Vector2 startpoint = { x, y };

        //le noeud est a gauche du noeud de centre (x,y) donc le deplacement est positif sur l'axe de (ox)
        Vector2 endpoint = { x + xOffset, y + levelHeight };
        DrawArrow(startpoint, endpoint, MAROON);
        drawTree(a->fd, x + xOffset, y + levelHeight, levelHeight, font);
    }

   // Dessiner le noeud a la fin pour que les fleches restent en dernier
    DessinerNoeud(&a, x, y, WHITE, font);
}


//-----------------------------------------------------------------------------------------


///Dessin du boutton avec les control necessaire
void dessinerBoutton(float x, float y, float width, float height, char text[20], Font font, Button * button_0){

        * button_0 = (Button){ (Rectangle){x, y, width, height}, RED, false };
        float textX = (*button_0).rect.x + (*button_0).rect.width/2 - MeasureText(text, font.baseSize)/2;
        float textY = (*button_0).rect.y +(* button_0).rect.height/2 - font.baseSize/2;
        bool mouse_over_button = CheckCollisionPointRec(GetMousePosition(), (*button_0).rect);



        // Check if button is clicked
        if (mouse_over_button) {
            (*button_0).color=BLUE;
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                (*button_0).color = GREEN ;
                (*button_0).pressed= true;
                }

            }
        else
        (*button_0).color=RED;

        //Dessin du rectangle
        DrawRectangleRec((*button_0).rect, (*button_0).color);
        // Dessin du text
        DrawTextEx(font, text, (Vector2){textX, textY},font.baseSize, 2, WHITE);
    }



//-----------------------------------------------------------------------------------------


///Dessin de Barre de text :

void DessinerBarreText(float x, float y, float width, float height,  textField * Barre, int * framesCounter, int * letterCount ){

    //text field setup\



    char text[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
   // int (letterCount) = 0;

/*width =100;
height = 50;*/
    (*Barre).textBox = (Rectangle) { x,y, width,height };
    (*Barre).color= LIGHTGRAY;
    bool mouseOnText = false;

   // int (framesCounter) = 0;


     ///passage de la souris par textfield
        if (CheckCollisionPointRec(GetMousePosition(), (*Barre).textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {

            //SetMouseCursor(MOUSE_CURSOR_IBEAM);
            (*Barre).mouseOn=true;
            ///le cursor devient celui avec la forme de "I" (I-Beam) lorsque on approche la (*Barre) de text


            int key = GetCharPressed();
            ///recuperer la cle du clavier en code ASCII

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && ((*letterCount) < MAX_INPUT_CHARS))
                {
                    (*Barre).text[(*letterCount)] = (char)key; ///recuperer le cle en charactere
                    (*Barre).text[(*letterCount)+1] = '\0'; ///ajouter le charactere de terminaison
                    (*letterCount)++;
                }

                key = GetCharPressed();  /// Check next character in the queue
            }

            ///traitement de supression de charactere (retour)
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                (*letterCount)--;
                if ((*letterCount) < 0) (*letterCount) = 0;
                (*Barre).text[(*letterCount)] = '\0';
            }
        }

        ///si il y a pas un passage aux (*Barre) de text, le cursor reste lui meme ( par defaut)
        else  //SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        (*Barre).mouseOn=false;

        if (mouseOnText) (*framesCounter)++;
        else (*framesCounter) = 0;
        //----------------------------------------------------------------------------------

        ///Dessins

        //DrawText("Arbres Binaire",30, 50, 20, GRAY);

            ///Dessiner le textfield
            DrawRectangleRec((*Barre).textBox, (*Barre).color);

            if (mouseOnText)
                ///si il y a un passage au (*Barre) de text, le  trait du rectangle devient rouge
                DrawRectangleLines((*Barre).textBox.x, (*Barre).textBox.y, (*Barre).textBox.width, (*Barre).textBox.height, RED);
            else
               ///sinon le trait du rectangle sont gris
               DrawRectangleLines((*Barre).textBox.x, (*Barre).textBox.y, (*Barre).textBox.width, (*Barre).textBox.height, RED);


            ///dessiner le Contenant le nom
            DrawText((*Barre).text, (*Barre).textBox.x + 5, (*Barre).textBox.y + 18, 20, MAROON);


            DrawText(TextFormat("INPUT CHARS: %i/%i", (*letterCount), MAX_INPUT_CHARS), 200, 170, 10, DARKGRAY);
            /// "input char x/y"

            ///si la cursor sur la (*Barre) de text
            if (mouseOnText)
            {
                ///si le compteur de lettre n'a pas encore depassee le maximum :
                if ((*letterCount) < MAX_INPUT_CHARS)
                {
                    ///dessiner une animation du character "_" pour indiquer a l'utilisateur qu'il peut inserer un text
                    // Draw blinking underscore char
                    if ((((*framesCounter)/20)%2) == 0) DrawText("_", (*Barre).textBox.x + 8 + MeasureText((*Barre).text, 20), (*Barre).textBox.y + 24, 20, MAROON);
                }
                ///sinon, indiquer a l'utilisateur qu'il faut supprimer
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
        if (CheckCollisionPointRec(GetMousePosition(),(*Barre).textBox)) mouseOnText = true;
        else mouseOnText = false;

}

//-----------------------------------------------------------------------------------------


///Main (Consol)

/*int main() {
    int n, x, i;

    //initialiser l'arbre:
    arbre R=NULL;

    //on aura besoin du pere si on utilise la fonction insertion avec appel recursif :
    //arbre pere;


    printf("\nDonnez le nombre de valeurs a inserer: ");
    scanf("%d", &n);



    //si on fait l'insertion recursif, il faut creer la racine separement , et le i commence de '2' dans la boucle for
    /*printf("\nDonnez la premiere valeur: ");
    scanf("%d", &x);*/


  /*  for (i = 1; i <= n; i++) {
        printf("\nDonnez la valeur %d: ", i);
        scanf("%d", &x);
        insertion(&R,x);
        //insertion iteratif (pas recursive)

        //en cas ou on fait l'insertion recursive :
       /* pere=NULL;
        inserer(&R, x, pere);*/
  //  }

   /* printf("\n--------\nResultat:\n ");

    printf("\nParcours infixe ( en ordre ) :\n");
    infixe(R);

    /*printf("\nDonner la valeur a supprimer : ");
    scanf("%d", &x);
    supprimer(&R,x,NULL);
    infixe(R);*/
/*
    return 0;
}*/


//-----------------------------------------------------------------------------------------


///Main GUI

int main(void) {



   ///Declarations necessaires
    int width=800 ;
    int height=450;
    int letterCount = 0;
    int framesCounter = 0;
    int letterCount1 = 0;
    int framesCounter1= 0;

    int letterCount2 = 0;
    int framesCounter2 = 0;

    int letterCount3 = 0;
    int framesCounter3= 0;

    ///Barres de text
    textField BarreInsere;
    textField BarreRechercher;
    textField BarreSupprimer;
    textField BarreCreer;


    ///Bouttons:
    Button button_inserer;
    Button button_rechercher;
    Button button_creer;
    Button button_supprimer;

    float levelHeight;
    int value;
    int max;
    arbre R;


    ///Initialisations necessaires

    //Fentetre
    /*width = GetScreenWidth;
    height = GetScreenHeight;*/
    framesCounter = 0;
    letterCount = 0;

    //Initilalisation de l'arbre:
    R=NULL;
    //Initialisation du text dans la barre de text concernant l'insertion:
    strcpy(BarreInsere.text, "");
     strcpy(BarreCreer.text, "");
      strcpy(BarreSupprimer.text, "");
       strcpy(BarreRechercher.text, "");
    //Initalisation de la fenetre:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Tree Visualizer");

    //Initialisation de l'echelle de l'hauteur d'arbre
    levelHeight= 50.0f;

    SetTargetFPS(60);

    Font customFont = LoadFontEx("Poppins-Black.ttf", 50, 0,0);
    Font font =  LoadFontEx("Poppins-Medium.ttf", 20, 0, 0);
     Font fontbot =  LoadFontEx("Poppins-Medium.ttf", 18, 0, 0);
    while (!WindowShouldClose()) {


      ClearBackground(RAYWHITE);
      BeginDrawing();

        DrawTextEx(customFont,"Arbres Binaires", (Vector2){10, 10}, 50,2, BLACK);



        DessinerBarreText(150, 100, 100,50, &BarreInsere, &framesCounter, &letterCount);

        dessinerBoutton(250,100,90,50,"Inserer",fontbot,&button_inserer);


        DessinerBarreText(150, 200, 100,50 ,&BarreCreer, &framesCounter1, &letterCount1);

        dessinerBoutton(250,200,90,50,"Creer",fontbot, &button_creer);


        DessinerBarreText(150, 300,100,50, &BarreRechercher, &framesCounter2, &letterCount2);

        dessinerBoutton(250,300,90,50," Recherche",fontbot, &button_rechercher);


        DessinerBarreText(150,400, 100, 50, &BarreSupprimer ,&framesCounter3, &letterCount3);

        dessinerBoutton(250,400,90,50, "Supprimer",fontbot, &button_supprimer);


       if (BarreCreer.mouseOn || BarreInsere.mouseOn || BarreRechercher.mouseOn || BarreSupprimer.mouseOn)
       SetMouseCursor(MOUSE_CURSOR_IBEAM);
       else SetMouseCursor(MOUSE_CURSOR_DEFAULT);




        // Draw button text
        if(button_inserer.pressed){

                int value = atoi(BarreInsere.text);


                // Call the inserer function with the obtained value
                insertion(&R, value);
                printf("\nValeur inseree !\nUpdate:\n");
                infixe(R);
                levelHeight = calculateSubtreeHeight(R) * 20.0f; // Adjust the factor as needed
            }



       // Draw button text
        if(button_creer.pressed){

                int max = atoi(BarreCreer.text);


                // Call the inserer function with the obtained value
                R= Creer_Arbre(max);
               // printf("\nValeur inseree !\nUpdate:\n");
                infixe(R);
                levelHeight = calculateSubtreeHeight(R) * 20.0f; // Adjust the factor as needed
            }

       // DrawFPS(10, 10);
       drawTree(R, GetScreenWidth() / 2, 50, levelHeight, font);

       EndDrawing();
    }

    // UnloadFont(customFont);

    // De-Initialization
    CloseWindow();  // Close window and OpenGL context

    return 0;
}



//------------------------------------------------------------------------------------
// Fin du programme
//------------------------------------------------------------------------------------

