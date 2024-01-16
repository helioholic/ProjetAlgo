#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"
#define MAX_INPUT_CHARS     4
#define  RADIUS     20.0f
#include <time.h> //pour le random


/**********************************************************************/


/**-------------------STRUCTURES-------------------**/

///Structure de button

typedef struct Button{
Rectangle rect;
Color color;
bool pressed;
bool mouseOn;
}Button;

//-----------------------------------------------------------------------------------------

///Structure du textField

typedef struct textField{
Rectangle textBox;
Color color;
char text[20];
bool mouseOn;
}textField;

//-----------------------------------------------------------------------------------------

///Structures de graphiques:

typedef struct Node{
Vector2 centre ;
float rayon;
Color col;
Color infoCol;
}Node;

typedef struct Branch{
Vector2 start;
Vector2 end;
}Branch;


//-----------------------------------------------------------------------------------------

///Structure de l'arbre

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

///Retourner l'adress d'un noeud portant une valeur a la recherche
arbre recherche_pointeur(arbre a, int val);

//---------------------------------------------

///Retourner la largeur d'un arbre
float calculateSubtreeWidth(arbre a);

//---------------------------------------------

///Retourner l'hauteur de l'arbre Binaire
int calculateSubtreeHeight(arbre a);

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

///Retourner la valeur maximal existante dans un arbre
int maximum(arbre a);

//---------------------------------------------

///Suppression d'une valeur dans un arbre
arbre supprimer(arbre a, int val);

//---------------------------------------------

///Mis a jour des coordonnees des noeuds :
void updateNodes(arbre*a, float x, float y, float levelheight);

//---------------------------------------------

/**dessins**/

///Dessin de l'arbre Binaire
void drawTreeUpdates(arbre a, Font font);

//---------------------------------------------

///Dessin d'un  boutton
void dessinerBoutton(float x, float y, float width, float height, char text[20], Font font, Button* button_0, Color color);

//---------------------------------------------

///Dessin d'une barre de texte avec tous les traitements necessaires
void DessinerBarreText(float x, float y, float width, float height, textField* Barre, int* framesCounter, int* letterCount);

//---------------------------------------------

///Dessin d'une fleche
void DrawArrow(Vector2 startPoint, Vector2 endPoint, Color col);
//---------------------------------------------

///Dessiner le noeud d'un arbre
void DessinerNoeud(arbre R, Font font);

//---------------------------------------------

///Fonction qui effectue le dessin de la branche :
void DessinerBranche(arbre R);

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

///Infixe (Inordre) (Fils_Gauche --> Noeud --> Fils_Droit )

void infixe(arbre a) {
    if (ArbreVide(a)==0) {
        // 1er appel recursif
        infixe(fils_Gauche(a)); // fils_Gauche
        printf(" %d |", a->info); // noeud (racine)
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

///Recherche dans un arbre binaire ordonne, Elle retourne une adresse ( le pointeur qui contient var)

arbre recherche_pointeur(arbre r, int val) {
    if (r == NULL || r->info == val) {
        return r;
    }


    if (val > r->info) {
        return recherche_pointeur(r->fd, val);
    }

    // If the value is smaller than the root's value, search in the left subtree
    return recherche_pointeur(r->fg, val);
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
  Color gray = {52, 52, 51, 255};
  arbre p; //ptr vers le noeud
  //p=malloc(sizeof(noeud)); //Reservation d'un espace pour le noeud
  p= (arbre)malloc(sizeof(noeud));
  p->fg=NULL;
  p->fd=NULL;
  p->pere=NULL;
  p->info=val;
  p->noeudshape.col=gray;
  p->noeudshape.infoCol=RAYWHITE;
  p->noeudshape.rayon=RADIUS;
  return p;
}

//-----------------------------------------------------------------------------------------

///Creation

arbre Creer_Arbre(int max){
    int i, val;
    arbre r=NULL;

    srand(time(NULL));   // Initialization, should only be called once.

    for (i=1; i<=max ; i++ ){
     do {
        val = rand() % 100 + 1;
       } while (recherche(r, val));
        insertion(& r, val);
    }

    return r;
}

//-----------------------------------------------------------------------------------------


///Insertion d'un noeud

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
     //printf("\nValeur inserer");

    }

//-----------------------------------------------------------------------------------------

///Mettre a jour les coordonees des noeuds des arbres avec leurs branches

void updateNodes(arbre *a, float x, float y, float levelHeight) {
      if (ArbreVide(*a)) return;

      // Calculer la largeur d'un sous-arbre
      float totalWidth = calculateSubtreeWidth(*a);

      //cette variable "xOffseta" represente le deplacement des branche sur l'axe (ox),
      //chaque fois un nouveau noeud est ajoute, il faut regler ce deplacement pour eviter la collision entre les noeuds

      // Le deplacement est en fonction  de la largeur/2
     float xOffset = totalWidth / 1.5f;


     // Mis a jour des branches gauche
      if ((*a)->fg != NULL) {

         //le noeud est a droite du noeud de centre (x,y) donc le deplacement est negative sur l'axe de (ox)
         //le deplacement dans l'axe (oy) est constant et il est en fonction de l'hauteur de larbre courrant
         //et le point d'arrive est en dessus du noeud c'est pour cette raison en fait " -Radius "

         Vector2 startpoint = { x, y };
         Vector2 endpoint = { x - xOffset, y + levelHeight };
         (*a)->BrancheGauche=(Branch){startpoint, endpoint};
         updateNodes(&(*a)->fg, x - xOffset, y + levelHeight, levelHeight);
       }

      // Mis a jour des branches droites
      if ((*a)->fd != NULL) {
         Vector2 startpoint = { x, y };
         Vector2 endpoint = { x + xOffset, y + levelHeight };
         (*a)->BrancheDroite=(Branch){startpoint, endpoint};
         updateNodes(&(*a)->fd, x + xOffset, y + levelHeight, levelHeight);
    }

   // Mis a jour du centre de noeud

   (*a)->noeudshape.centre=(Vector2){x,y};   //printf("\nUPDATED");
}

//-----------------------------------------------------------------------------------------

/** Suppression d'un noeud dans un arbre :**/

arbre supprimer(arbre a, int val)
{

    if (a == NULL)
        return a;

    // appel recursif des fils de
    // pour pointer au noeud a
    //supprimer

    if (a->info > val) {
        a->fg = supprimer(a->fg, val);
        return a;
    }
    else if (a->info < val) {
        a->fd = supprimer(a->fd, val);
        return a;
    }

    /**on arrive ici ou c'est la
    racine qu'on va supprimer**/

    // L'un des fils =NULL
    if (a->fg == NULL) {
        arbre temp = a->fd;
        free(a);
        return temp;
    }
    else if (a->fd == NULL) {
        arbre temp = a->fg;
        free(a);
        return temp;
    }

    // si les deux fils existent
    else {
        // Find successor
        arbre succ = a->fd;
        while (succ->fg != NULL) {
            succ = succ->fg;
        }

        arbre succParent = succ->pere;

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right

        if (succParent != a)
            succParent->fg = succ->fd;
        else
            succParent->fd = succ->fd;

        // Copy Successor Data to root
        a->info = succ->info;

        // Delete Successor and return root
        free(succ);
        return a;
    }
}


//-----------------------------------------------------------------------------------------


///Calculer la largeur de l'arbre avec une echelle pour les graphics (*20f) (enhanced for making the tree more spacy and more orgamized )

float calculateSubtreeWidth(arbre a) {
    if (ArbreVide(a)) return 0.0f;



    float leftWidth = calculateSubtreeWidth(a->fg);
    float rightWidth = calculateSubtreeWidth(a->fd);

    // Calculate width based on the sum of subtree widths and some padding
    return leftWidth + rightWidth + 20.0f;
}

//-----------------------------------------------------------------------------------------

///Fonction qui calcule l'hauteur d'un sous arbre a partir d'un noeud

int calculateSubtreeHeight(arbre a) {
    if (ArbreVide(a)) return 0;

    int leftHeight = calculateSubtreeHeight(a->fg);
    int rightHeight = calculateSubtreeHeight(a->fd);

    // Include the current node's height
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//-----------------------------------------------------------------------------------------


/// Liberer l'arbre a entierement
void LibererArbre(arbre a) {
    if (a != NULL) {

        LibererArbre(a->fg);
        LibererArbre(a->fd);
        LibererArbre(a);
    }
}


/**-------------------FONCTIONS DESSIN SEULEMENT-------------------**/

void DrawArrow(Vector2 startPoint, Vector2 endPoint, Color col){

   // Dessin de la ligne
    DrawLineEx(startPoint, endPoint, 4, col);

}

//-----------------------------------------------------------------------------------------


///Dessiner le noeud d'un arbre
void DessinerNoeud(arbre  r , Font font ){

Color Lavender = {155, 117, 218, 255};
Color gray= {52, 52, 51, 255};


float x=r->noeudshape.centre.x;
float y=r->noeudshape.centre.y;
Vector2 point={x,y};



    //Dessiner le circle:
    DrawCircle(x, y, RADIUS,  r->noeudshape.col);

    //dessiner le text:
    /*On dessine le texte de telle sorte qu'il soit au milieu du circle*/
    /*pour cela , voila en general l'appel de la fonction*/
    /*DrawText(text,Center_x - MeasureText(text, taillePolice) / 2 , y - taillePolice / 2 , taillePolice, MAROON);*/
    /*TextFormat est pour obtenir cette variable "a->info" en format textuel*/

      DrawTextEx(font,TextFormat("%d", (r)->info), (Vector2){x - MeasureText(TextFormat("%d", (r)->info), 20) / 2 , y - 20 / 2} , 20,2,r->noeudshape.infoCol);

}

//-----------------------------------------------------------------------------------------


///Fonction qui effectue le dessin de la branche :

void DessinerBranche(arbre r) {
    Vector2 startpoint, endpoint;
    Color lavender = {155, 117, 218, 255};

    if (r->fd != NULL) {
        startpoint = r->BrancheDroite.start;
        endpoint = r->BrancheDroite.end;
        DrawArrow(startpoint, endpoint, lavender);
    }

    if (r->fg != NULL) {
        startpoint = r->BrancheGauche.start;
        endpoint = r->BrancheGauche.end;
        DrawArrow(startpoint, endpoint, lavender);
    }
}


//-----------------------------------------------------------------------------------------


///Dessiner l'abre (Version avec updates)

void drawTreeUpdates(arbre a, Font font) {

    if (ArbreVide(a)) return;

     DessinerBranche(a);
     DessinerNoeud(a, font);

     // Dessiner l'arbre gauche
     if (a->fg != NULL) {
         drawTreeUpdates(a->fg, font);
      }

     // Dessiner l'arbre droit
     if (a->fd != NULL) {
         drawTreeUpdates(a->fd, font);
       }
   }


//-----------------------------------------------------------------------------------------


///Dessin du boutton avec les control necessaire
void dessinerBoutton(float x, float y, float width, float height, char text[20], Font font, Button * button_0, Color color){

        * button_0 = (Button){ (Rectangle){x, y, width, height}, RED, false };
        float textX = (*button_0).rect.x + (*button_0).rect.width/2 - MeasureText(text, font.baseSize)/2;
        float textY = (*button_0).rect.y +(* button_0).rect.height/2 - font.baseSize/2;
        bool mouse_over_button = CheckCollisionPointRec(GetMousePosition(), (*button_0).rect);



        // Check if button is clicked
        if (mouse_over_button) {

            (*button_0).mouseOn=true;
            (*button_0).color=PURPLE;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                (*button_0).color = GREEN ;
                (*button_0).pressed= true;
                }

            }
        else
       {
           (*button_0).color=color; (*button_0).mouseOn=false;
       }

        //Dessin du rectangle
        DrawRectangleRec((*button_0).rect, (*button_0).color);
        // Dessin du text
        DrawTextEx(font, text, (Vector2){textX, textY},font.baseSize, 2, WHITE);
    }



//-----------------------------------------------------------------------------------------


///Dessin de Barre de text :

void DessinerBarreText(float x, float y, float width, float height,  textField * Barre, int * framesCounter, int * letterCount ){
Color lavender = {155, 117, 218, 255};

Color orange= {244, 120, 66, 255};
    char text[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'

    (*Barre).textBox = (Rectangle) { x,y, width,height };
    (*Barre).color= DARKGRAY;
    bool mouseOnText = false;


     ///passage de la souris par textfield
        if (CheckCollisionPointRec(GetMousePosition(), (*Barre).textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {


            (*Barre).mouseOn=true;
            ///le cursor devient celui avec la forme de "I" (I-Beam) lorsque on approche la (*Barre) de text


            int key = GetCharPressed();
            ///recuperer la cle du clavier en code ASCII

            // verifier si plusieurs characters sont introduite
            while (key > 0)
            {
                //autoriser les cle  qui appartienennt au interval : [32..125]
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

       //****//

        ///Dessins

        //DrawText("Arbres Binaire",30, 50, 20, GRAY);

            ///Dessiner le textfield
            DrawRectangleRec((*Barre).textBox, (*Barre).color);

            if (mouseOnText)
                ///si il y a un passage au (*Barre) de text, le  trait du rectangle devient rouge
                DrawRectangleLines((*Barre).textBox.x, (*Barre).textBox.y, (*Barre).textBox.width, (*Barre).textBox.height,orange);
            else
               ///sinon le trait du rectangle sont gris
               DrawRectangleLines((*Barre).textBox.x, (*Barre).textBox.y, (*Barre).textBox.width, (*Barre).textBox.height, DARKGRAY);


            ///dessiner le Contenant le nom
            DrawText((*Barre).text, (*Barre).textBox.x + 5, (*Barre).textBox.y + 18, 20, orange);


            DrawText(TextFormat("%i/%i", (*letterCount), MAX_INPUT_CHARS), (*Barre).textBox.x + (*Barre).textBox.width-MeasureText(TextFormat("%i/%i", (*letterCount), MAX_INPUT_CHARS), 4)-5, (*Barre).textBox.y + (*Barre).textBox.height+4, 4, orange);
            /// "input char x/y"

            ///si la cursor sur la (*Barre) de text
            if (mouseOnText)
            {
                ///si le compteur de lettre n'a pas encore depassee le maximum :
                if ((*letterCount) < MAX_INPUT_CHARS)
                {
                    ///dessiner une animation du character "_" pour indiquer a l'utilisateur qu'il peut inserer un text
                    // Draw blinking underscore char
                    if ((((*framesCounter)/20)%2) == 0) DrawText("_", (*Barre).textBox.x + 8 + MeasureText((*Barre).text, 20), (*Barre).textBox.y + 24, 20,orange);
                }
            }
        if (CheckCollisionPointRec(GetMousePosition(),(*Barre).textBox)) mouseOnText = true;
        else mouseOnText = false;

}

//-----------------------------------------------------------------------------------------


/**-------------------MAIN-------------------**/


///Main GUI

int main(void) {



   ///Declarations necessaires
    int width ; //largeur de la fenetre
    int height; //longueur de la fenetre
    int letterCount = 0;   //compteur de lettre pour la barre de text pour l'insertion
    int framesCounter = 0; //compteur de frame pour l'animation du "_" dans la barre de text de l'insertion
    int letterCount1 = 0;  //compteur de lettre pour la barre de text pour la creation
    int framesCounter1= 0; //compteur de frame pour l'animation du "_" dans la barre de text de la creation
    int letterCount2 = 0;  //compteur de lettre pour la barre de text pour la recherche
    int framesCounter2 = 0;//compteur de frame pour l'animation du "_" dans la barre de text de la recherche
    int letterCount3 = 0;  //compteur de lettre pour la barre de text pour la suppression
    int framesCounter3= 0; //compteur de frame pour l'animation du "_" dans la barre de text de la suppression

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


    ///Booleens pour les cursors :
    //Traitement des cursors :
    bool MouseOnBarreText;
    bool MouseOnButton;

    ///Autre
    float levelHeight; //une sorte d'echelle pour l'hauteur de l'arbre
    int value; //variable utilise dans le cas de: valeur qu'on va inserer dans l'arbre
    int max; //nombre de noeuds dans l'arbre qu'on va creer
    arbre R; //l'arbre qu'on est entrain de manipuler en cours de ce programme
    arbre trouv; //un pointeur qu'on va utiliser l'ors de la recherche d'une valeur dans un arbre
    bool arbreMisAjour; //on aura besoin de cette variable lors de la recherche d'une valeur dans un arbre
    char erreur_message[100];

    ///Couleurs
    Color Charcoal = {32, 32, 31, 255};
    Color Lavender = {155, 117, 218, 255};
    Color orange= {244, 120, 66, 255};
    Color gray = {52, 52, 51, 255};


    ///Initialisations necessaires

    //cette instruction sert a rendre les formes plus lisses (for more smoothnes )
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    //Fentetre
    width = 1000; //GetScreenWidth();
    height = 1000; //GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Tree Visualizer");



    //Initilalisation de l'arbre:
    R=NULL;

    //Initialisation du text dans la barre de text concernant l'insertion:
    strcpy(BarreInsere.text, "");
    strcpy(BarreCreer.text, "");
    strcpy(BarreSupprimer.text, "");
    strcpy(BarreRechercher.text, "");



    //Initialisation de l'echelle de l'hauteur d'arbre
    levelHeight= 50.0f;


    //frames  par second : 60
    SetTargetFPS(60);

    //Polices et images utilise :
    Font font =  LoadFontEx("Poppins-Medium.ttf", 20, 0, 0); //size : 20
    Font fontbot =  LoadFontEx("Poppins-Medium.ttf", 18, 0, 0); //size : 18
    Font aestheticTitle= LoadFontEx("roygendisplay-regular.ttf", 80,0,0);
    Image WelcomeImage = LoadImage("welcomeImage.png");
    Texture2D ImageTexture = LoadTextureFromImage(WelcomeImage);
    //intialisation du message d'erreur:
    strcpy(erreur_message,"");

   ///Welcome Page
   while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(ImageTexture, 0, 0, WHITE);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) {
            break; // Exit the welcome loop if Enter is pressed
        }
    }

    while (!WindowShouldClose()) {


      ClearBackground((Color){14, 14, 14, 255});


        BeginDrawing();



        Rectangle buttonsRec = {100, 150, 300,600 };

        Rectangle recarbre = {350, 120, GetScreenWidth()-350-30,GetScreenHeight()-120-30 };

        DrawRectangleLinesEx(recarbre, 4, Lavender);

        Rectangle bonusRec = {80, 700, 240, 100 };

        DrawTextEx(aestheticTitle,"OUTPUT", (Vector2){950,30}, 80,2, Lavender);
        DrawTextEx(aestheticTitle,"INPUT", (Vector2){100, 120}, 80,2, orange);


        DessinerBarreText(100, 275, 100,50, &BarreInsere, &framesCounter, &letterCount);

        dessinerBoutton(200,275,90,50,"Inserer",fontbot,&button_inserer, orange);


        DessinerBarreText(100, 375, 100,50 ,&BarreCreer, &framesCounter1, &letterCount1);

        dessinerBoutton(200,375,90,50,"Creer",fontbot, &button_creer, orange);


        DessinerBarreText(100, 475,100,50, &BarreRechercher, &framesCounter2, &letterCount2);

        dessinerBoutton(200,475,90,50," Recherche",fontbot, &button_rechercher, orange);


        DessinerBarreText(100,575, 100, 50, &BarreSupprimer ,&framesCounter3, &letterCount3);

        dessinerBoutton(200,575,90,50, "Supprimer",fontbot, &button_supprimer, orange);


        arbreMisAjour=false;

       if ((BarreCreer.mouseOn || BarreInsere.mouseOn || BarreRechercher.mouseOn || BarreSupprimer.mouseOn) && (!(MouseOnButton))){
        MouseOnBarreText=true;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
       }

       else {
        if (!(MouseOnButton)){
        MouseOnBarreText=false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
      }

        if ((button_creer.mouseOn || button_inserer.mouseOn || button_rechercher.mouseOn || button_supprimer.mouseOn) && (!(MouseOnBarreText))){
        MouseOnButton=true;
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }

       else {
        if (!(MouseOnBarreText)){
        MouseOnButton=false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
      }


        /**Remarque :
        Sans ces conditions le cursor va se mettre dans un etat infinie de changement entre IBM et POINTING HAND et DEFAULT
        **/


      ///Action Listeners :
        ///Boutton Insertion

        if ((button_inserer.pressed || (IsKeyPressed(KEY_ENTER)&& (BarreInsere.mouseOn) )) && letterCount > 0) {

           int value = atoi(BarreInsere.text);
           arbreMisAjour=true;


            ///Echec de l'insertion
            if (recherche(R, value)) {
               strcpy(erreur_message,"    Cette valeur existe deja");

              /* DrawText(
             "Cette valeur existe deja", bonusRec.x +(bonusRec.width/2)- (MeasureText("Cette valeur n'existe pax",10)/2),
                bonusRec.y+(bonusRec.height/2)+5,10, orange);*/
            }
                else{
                strcpy(erreur_message,"");
                insertion(&R, value);
                printf("\nValeur inseree !\nUpdate:\n");
                infixe(R);


                levelHeight = calculateSubtreeHeight(R) * 17.0f;
                updateNodes(&R,  (recarbre.width/ 2 + recarbre.x) , 200, levelHeight);
            }
        }

       ///Boutton Creation
        if (  (button_creer.pressed || (IsKeyPressed(KEY_ENTER)&& (BarreCreer.mouseOn) ) ) && letterCount1 > 0){

           arbreMisAjour=true;
            int max = atoi(BarreCreer.text);


            // Call the inserer function with the obtained value
             if (max<0) {
                strcpy(erreur_message,"        Entree non valide");
            }
            else {
             strcpy(erreur_message,"");
             R= Creer_Arbre(max);
             // printf("\nValeur inseree !\nUpdate:\n");
             infixe(R);
             levelHeight = calculateSubtreeHeight(R) * 17.0f;

             ///Mettre a jour les coordonnees de l'arbre :
             updateNodes(&R,  (recarbre.width/ 2 + recarbre.x) , 200, levelHeight);
            }

        }

        ///button recherche
        if ((button_rechercher.pressed || (IsKeyPressed(KEY_ENTER)&& (BarreRechercher.mouseOn) )) && letterCount2 > 0) {
          int val = atoi(BarreRechercher.text);

          //si une recherche qui a ete deja effectue : restaurer la couleur
          if (trouv!=NULL){
              trouv->noeudshape.col=gray;
              trouv->noeudshape.infoCol=RAYWHITE;
          }

          // Appel de la fonction recherche
          trouv = recherche_pointeur(R, val);
          //si trouv existe, on va le stocker dans trouvTemp pour le colorer comme un noeud independant

          if (trouv != NULL) {
              trouv->noeudshape.col=orange;
              trouv->noeudshape.infoCol=WHITE;
              strcpy(erreur_message,"");
            }
            else {
               strcpy(erreur_message,"   Cette valeur n'existe pas");
            }
        }


        if (  (button_supprimer.pressed || (IsKeyPressed(KEY_ENTER)&& (BarreSupprimer.mouseOn) ) ) && letterCount3 > 0){

           arbreMisAjour=true;
            int value = atoi(BarreSupprimer.text);


            // Call the inserer function with the obtained value
            if (!recherche(R, value)){
               strcpy(erreur_message,"Cette valeur n'existe pas");
             }
             else{
             strcpy(erreur_message,"");
             R=supprimer(R, value);
             // printf("\nValeur inseree !\nUpdate:\n");
             infixe(R);
             levelHeight = calculateSubtreeHeight(R) * 17.0f;

             ///Mettre a jour les coordonnees de l'arbre :
             updateNodes(&R,  (recarbre.width/ 2 + recarbre.x) , 200, levelHeight);
             }

        }

        ///Apres la recherche ( restaurer les couleurs precedentes )

           //si on efface le text de la barre de recherche ou bien on a effectue une operation sur notre arbre apres une operation de recherche (trouv !=NULL)
           //alors il faut que les couleurs redevient comme

           if(  (( arbreMisAjour) || (strcmp(BarreRechercher.text, "")==0)) && (trouv!=NULL) ){
              trouv->noeudshape.col=gray;
              trouv->noeudshape.infoCol=RAYWHITE;
              trouv=NULL;
            }
       ///
       if (strcmp(erreur_message,"")!=0){
          DrawTextEx(font, erreur_message, (Vector2){bonusRec.x,bonusRec.y+43}, 20, 2, orange);
            DrawRectangleLinesEx(bonusRec, 4, orange);
       }

        drawTreeUpdates(R, font);
        EndDrawing();
    }

    // De-Initialisation
    CloseWindow();

    ///Liberation & Unloadings
    LibererArbre(R);
    LibererArbre(trouv);

    UnloadFont(font);
    UnloadFont(fontbot);
    UnloadFont(aestheticTitle);
    UnloadTexture(ImageTexture);
    UnloadImage(WelcomeImage);

    return 0;
}

//------------------------------------------------------------------------------------
// Fin du programme
//------------------------------------------------------------------------------------

