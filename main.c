#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Arbres_Bibio.h"
#include "raylib.h"
#define MAX_INPUT_CHARS     4
#include <time.h>

 //test



///Structure de button

typedef struct Button{
Rectangle rect;
Color color;
float pressTimer;
}Button;

//-----------------------------------

typedef struct noeud noeud;
typedef struct noeud
{
    int info;
    struct noeud* fd;
    struct noeud* fg;
};

//---------------------------------------

typedef noeud* arbre;

//---------------------------------------

///Verifier si un noeud est vide:
int ArbreVide(arbre a){
    if (a==NULL) return 1;
        else return 0;
}

//---------------------------------------

///Retourner le Fils_Gauche (adresse):

arbre fils_Gauche(arbre a){
    return a->fg;
}

//---------------------------------------

///Retourner le Fils_Droit (adresse):

arbre fils_Droit(arbre a){
    return a->fd;
}

//---------------------------------------

///Verfifier si un noeud a est une feuille:

int feuille (arbre a){
    if (a->fd==NULL && a->fg==NULL) return(1) ;
     else
    return(0) ;
}

//---------------------------------------

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

//---------------------------------------
//test

///Infixe (Inordre) (Fils_Gauche --> Noeud --> Fils_Droit )

void infixe(arbre a) {
    if (ArbreVide(a)==0) {
        // 1er appel recursif
        infixe(fils_Gauche(a)); // fils_Gauche
        printf("| %d |", a->info); // noeud (racine)
        // 2eme appel recursif
        infixe(fils_Droit(a)); // fils_Droit
    }
}

//---------------------------------------

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

//---------------------------------------

int nombre_de_noeuds ( arbre a ) {
if (a==NULL) return 0 ;
return ( 1 + nombre_de_noeuds ( a->fg )
+ nombre_de_noeuds (a->fd ) ) ;
}


//-----------------------------------

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

//---------------------------------------

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

//---------------------------------------

/**Insertion dans un arbre binaire ordonne**/

///Creation d'un noeud

arbre creer_noeud(int val){
  arbre p; //ptr vers le noeud
  //p=malloc(sizeof(noeud)); //Reservation d'un espace pour le noeud
  p= (arbre)malloc(sizeof(noeud));
  p->fg=NULL;
  p->fd=NULL;
  p->info=val;
  return p;
}

//---------------------------------------

///Insertion d'un noeud

///Sans Appel Recursif :

void insertion(arbre * a, int val){
     int insert; arbre r;
     insert=0;
     r=*a;

     //si la valeur existe deja on va pas l'inserer
     if (recherche(*a, val)==1){printf("Insertion impossible, La Valeur %d existe deja dans l'arbre", val);}
     //sinon, si la valeur n'existe pas :
     else {
     if ((*a)==NULL){

         (*a)=creer_noeud(val);
         insert=1;
         printf("\nRacine created");
     }

     while(insert==0){
          if (val< r->info){
              if (fils_Gauche(r)==NULL){
                 r->fg=creer_noeud(val);
                  insert=1;
                }
              else{
                 r=fils_Gauche(r);
                }
                //printf("\nWORKS1");

            }
            else{
                if (val>r->info){
                    if (fils_Droit(r)==NULL){
                     r->fd=creer_noeud(val);
                     insert=1;
                    }
                    else{
                      r=fils_Droit(r);
                    }
                }
            }
            //printf("\nWORKS2");
        }
        printf("\nWORKS ALL");
        //printf("\nla nouvelle valeur = %d \n", r->info);
     }
    }

//---------------------------------------



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


//---------------------------------------

/** Suppression d'un noeud dans un arbre :**/

///Fonction maximum qui retourne la plus grande valeur dans un arbre de recherche

int maximum(arbre a){
      if (ArbreVide(a->fd)){return a->info;}
      //car si il n'y a aucun cote droit, cela veut dire qu'il n'ya aucune valeur plus petite que la valeur de a, donc a est le max
      else {
        return maximum(fils_Droit(a));
      }
}

//---------------------------------------

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




//-----------------------------------

/**void drawNode(arbre a, float x, float y, float xOffset) {
    // Draw the node
    DrawText(TextFormat("%d", a->info), x, y, 20, MAROON);

    // Draw lines to its children
    if (a->fg != NULL) {
        DrawLine(x + 10, y + 30, x - xOffset, y + 80, BLACK);  // Left branch
        drawNode(a->fg, x - xOffset, y + 80, xOffset / 2);
    }

    if (a->fd != NULL) {
        DrawLine(x + 10, y + 30, x + xOffset, y + 80, BLACK);  // Right branch
        drawNode(a->fd, x + xOffset, y + 80, xOffset / 2);
    }
}**/



//--------------------------------------------------------------------------------

/*void drawTree(arbre a, float x, float y) {
    if (!ArbreVide(a)) {
        // Draw the root node
        DrawText(TextFormat("%d", a->info), x, y, 20, MAROON);


        // Draw lines to its children
        if (a->fg != NULL) {
            DrawLine(x + 10, y + 30, x - 50, y + 80, BLACK);  // Left branch
            drawNode(a->fg, x - 50, y + 80, 25);
        }

        if (a->fd != NULL) {
            DrawLine(x + 10, y + 30, x + 50, y + 80, BLACK);  // Right branch
            drawNode(a->fd, x + 50, y + 80, 25);
        }
    }
}*/


void drawTree(arbre a, float x, float y, float xOffset) {
    if (!ArbreVide(a)) {
        // Draw the node
        float radius = 40.0f;

        for (int i = 0; i < 36; ++i) {
            float angle = (float)i * 0.1f;
            DrawCircleLines(x , y , radius + angle, MAROON);
        }

        DrawCircle(x, y, radius, WHITE);
        DrawText(TextFormat("%d", a->info),x - MeasureText(TextFormat("%d", a->info), 20) / 2 , y - 20 / 2 , 20, MAROON);
       // DrawText(TextFormat("%d", a->info), x - 15, y - 10, 20, MAROON);

        // Draw lines to its children
        if (a->fg != NULL) {
            DrawLine(x, y, x - xOffset, y + 80, BLACK);  // Left branch
            drawTree(a->fg, x - xOffset, y + 80, xOffset / 1.5);
        }

        if (a->fd != NULL) {

            DrawLine(x, y, x + xOffset, y + 80, BLACK);  // Right branch
            drawTree(a->fd, x + xOffset, y + 80, xOffset / 1.5);
        }
    }
}


//-----------------------------------------------------------------------------------------

///Booleen pour indiquer le passage par boutton
bool mouse_over_button (Button button){
return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

//-----------------------------------

int main(void) {
  //initialiser l'arbre:
    arbre R=NULL;
    int value;

    // Window setup
    int width = 1700;
    int height = 1000;
    float tailleNoeud = 20.0;
    InitWindow(width, height, "Tree Visualizer");

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { 150, 100, 100,50 };
    bool mouseOnText = false;

    int framesCounter = 0;



    SetTargetFPS(60);

    // Button setup
    //Button button_0 = { (Rectangle){width/2-100, height/2-50, 200, 100}, RED };
     Button button_0 = { (Rectangle){250, 100, 90, 50}, RED };

    while (!WindowShouldClose()) {


        ///passage de la souris par textfield
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            ///le cursor devient celui avec la forme de "I" lorsque on approche la barre de text

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();
            ///recuperer la cle du clavier en code ASCII

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key; ///recuperer le cle en charactere
                    name[letterCount+1] = '\0'; ///ajouter le charactere de terminaison
                    letterCount++;
                }

                key = GetCharPressed();  /// Check next character in the queue
            }

            ///traitement de supression de charactere (retour)
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        ///si il y a pas un passage aux barre de text, le cursor reste lui meme ( par defaut)
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        // Button color change based on mouse position

        // Drawing operations
        BeginDrawing();

        ClearBackground(RAYWHITE);


            DrawText("Arbres Binaire",30, 50, 20, GRAY);

            ///Dessiner le textfield
            DrawRectangleRec(textBox, LIGHTGRAY);

            if (mouseOnText)
                ///si il y a un passage au barre de text, le  trait du rectangle devient rouge
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else
               ///sinon le trait du rectangle sont gris
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            ///dessiner le Contenant le nom
            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 18, 20, MAROON);


            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 200, 170, 10, DARKGRAY);
            /// "input char x/y"

            ///si la cursor sur la barre de text
            if (mouseOnText)
            {
                ///si le compteur de lettre n'a pas encore depassee le maximum :
                if (letterCount < MAX_INPUT_CHARS)
                {
                    ///dessiner une animation du character "_" pour indiquer a l'utilisateur qu'il peut inserer un text
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 20), (int)textBox.y + 24, 20, MAROON);
                }
                ///sinon, indiquer a l'utilisateur qu'il faut supprimer
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }

        DrawRectangleRec(button_0.rect, button_0.color);

        // Draw button text
        float textX = button_0.rect.x + button_0.rect.width/2 - MeasureText("Inserer", 15)/2;
        float textY = button_0.rect.y + button_0.rect.height/2 - 15/2;
        DrawText("Inserer", textX, textY,15, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        // Check if button is clicked
        if (mouse_over_button(button_0)) {
            button_0.color=BLUE;
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                button_0.color = GREEN ;
                int value = atoi(name);


                // Call the inserer function with the obtained value
                insertion(&R, value);
                printf("\nValeur inseree !\nUpdate:\n");
                infixe(R);
            }
        }else {
            button_0.color=RED;
        }

       // DrawFPS(10, 10);
        drawTree(R, GetScreenWidth() / 2, 50, 150);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();  // Close window and OpenGL context
    return 0;
}



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
