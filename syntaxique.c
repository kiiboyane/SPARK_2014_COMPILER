#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include"analyseur_lexical_v0.h"



Erreurs MES_ERR[100]={{ERR_CAR_INC,"Caractère inconnu"},
                    {ERR_FICH_VID,"Fichier vide"},
                    {ERR_ID_LONG, "Identifiant très long" },
                    {ERR_COMM,"Commentaire non correct"},
                    {ERR_AFFEC,"AFFEC"},{ERR_COND,"COND"},
                    {ERR_CONSTS,"CONSTS"},
                    {ERR_ECRIRE,"ECRIRE"},
                    {ERR_FACT,"FACT"},
                    {ERR_INST,"INST"},
                    {ERR_INSTS,"INSTS"},
                    {ERR_LIRE,"LIRE"},
                    {ERR_PROGRAM,"PROGRAM"},
                    {ERR_ID_PROCEDURE,"Identifier expected"},
                    {ERR_PROCEDURE,"procedure expected"},
                    {ERR_IS,"is expected"},
                    {ERR_BEGIN,"begin expected"},
                    {ERR_END,"end expected"},
                    {ERR_PV," ';' expected"},
                    {ERR_PF," ')' expected"},
                    {ERR_ARGS," '(' expected"},
                    {ERR_VARS,"VARS"},
                    {ERR_SEM,"ERREUR SEMANTIQUE"},
                    {ERR_PO," '(' expected"},
                    {ERR_P," ':' expected"},
                    {ERR_P," ':' expected"},
                    {TYPE_ERR," type unknown "},
                    {MODE_ERR," mode not found "},
                    {ERR_IMP," \"=>\" not found "},
                    {SPARK_MODE_ERR," on/off expected  "},
                    {ERR_NULL," null expected  "}
                  };



/*void program () ; */
void procedure () ; 
void args () ; 
void args_dec (); 
void arg_dec (); 
void id_tokens (); 
void id_tokens_aux (); 
void out (); 
void type (); 
void arg_dec_aux (); 
void modes (); 
void mode_aux (); 
void mode (); 
void spark_mode (); 
void global_mode (); 
void depends_mode (); 
void pre_mode (); 
void post_mode (); 
void declarations (); 
void procedure_body ();
void condition() ; 


/*void args_dec_aux ();
void arg_dec ();
void id_tokens (); 
void id_tokens_aux ();
void type (); 
void contract (); 


void declaration (); 
void var_declaration (); 
void instructions (); 
void instruction_aux (); 
void instruction (); 
void aff_ins (); 
void for_ins (); 
void range (); 
void exp (); 
void termaux (); 
void term (); 
void factaux (); 
void fact (); 
void if_ins (); 
void elseaux (); 
void condition (); 
void while_ins (); */




void Symbole_testing  (TOKENS cl, CODES_ERREURS err){
  if (sym_Cour.CODE == cl)
  {
    afficherToken();
    sym_Suiv();
  }
  else
    Gen_Erreur(err);
}

void args(){
  switch(sym_Cour.CODE){
        case PO_TOKEN :
                  args_dec();
                  Symbole_testing(PF_TOKEN,ERR_PF);
                  modes();
                  break; 
        case WITH_TOKEN :
                  modes();
                  break; 
        case IS_TOKEN :
                  break; 
       }
}

void args_dec(){
  printf("in args_dec \n");
  arg_dec(); 
  arg_dec_aux();
}

void arg_dec_aux(){
  switch(sym_Cour.CODE){
        case PV_TOKEN :
                  arg_dec();
                  arg_dec_aux();
                  break;  
        default : break; 
       }
     
}
void arg_dec (){
   id_tokens(); 
   Symbole_testing(P_TOKEN,ERR_P);
   switch(sym_Cour.CODE){
        case IN_TOKEN :
                  sym_Suiv();
                  out();
                  break; 
        case OUT_TOKEN :
                  sym_Suiv();
                  type();
                  break; 
        default : type();
                  break; 
       }
   
}
void out(){
  switch(sym_Cour.CODE){
        case OUT_TOKEN :
                  sym_Suiv();
                  type();
                  break;  
        default : type();
                  break; 
       }
}
void type (){
  switch(sym_Cour.CODE){
        case NATURAL_TOKEN :
                  sym_Suiv();
                  break; 
        case INTEGER_TOKEN :
                  sym_Suiv();
                  break; 
        case POSITIVE_TOKEN :
                  sym_Suiv();
                  break; 
        case CHARACTER_TOKEN :
                  sym_Suiv();
                  break;  
        default : 
                  Gen_Erreur(TYPE_ERR);
                  break; 
       }

}
void id_tokens(){
   sym_Suiv();
   Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
   id_tokens_aux() ;
} 

void id_tokens_aux(){
   switch(sym_Cour.CODE){
        case V_TOKEN :
                  sym_Suiv();
                  Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
                  id_tokens_aux();
                  break; 
       }
}

void modes (){
  if(sym_Cour.CODE != WITH_TOKEN) return ; 
  sym_Suiv();
  mode(); 
  mode_aux(); 
}

void mode (){
  switch(sym_Cour.CODE){
        case SPARK_MODE_TOKEN :
                  sym_Suiv();
                  spark_mode();
                  break; 
        case DEPENDS_TOKEN :
                  sym_Suiv();
                  depends_mode();
                  break; 
        case GLOBAL_TOKEN :
                  sym_Suiv();
                  global_mode();
                  break; 
        case PRE_TOKEN : 
                  sym_Suiv();
                  pre_mode();
                  break; 
        case POST_TOKEN :
                  sym_Suiv();
                  post_mode();
                  break; 
        default :Gen_Erreur(MODE_ERR);
                break; 
       }
}

void spark_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    sym_Suiv();
    switch(sym_Cour.CODE){
        case ON_TOKEN :
                  sym_Suiv();
                  break; 
        case OFF_TOKEN :
                  sym_Suiv();
                  break; 
        default :Gen_Erreur(SPARK_MODE_ERR);
                break; 
       }
} 
void depends_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    Symbole_testing(PO_TOKEN,ERR_PO);
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    Symbole_testing(PF_TOKEN,ERR_PF);
}

void global_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    Symbole_testing(NULL_TOKEN,ERR_NULL);
}

void pre_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    condition();
}
void condition (){
    Symbole_testing(NULL_TOKEN,ERR_NULL);
}
void post_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
    condition();
}
void mode_aux(){
  switch(sym_Cour.CODE){
        case V_TOKEN :
                  sym_Suiv();
                  mode();
                  mode_aux();
                  break; 
        default : break; 
       }

}
/*void contract(){
  switch(sym_Cour.CODE){
        case WITH_TOKEN :
                  modes();
                  break; 
       }
}*/
/*void modes (){
  printf("in modes \n");
  sym_Suiv();
  if(sym_Cour.CODE !=  MODE_SPARK_TOKEN ) return ; 
}
void declarations (){
   printf("in declarations");

}*/
/*void procedure_body(){

}*/

void procedure(){
    Symbole_testing(PROCEDURE_TOKEN,ERR_PROCEDURE);
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    args(); 
   // modes(); 
    Symbole_testing(IS_TOKEN,ERR_IS);
    //declarations(); 
    Symbole_testing(BEGIN_TOKEN,ERR_BEGIN);
   // procedure_body();
    Symbole_testing(END_TOKEN,ERR_END);
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    Symbole_testing(PV_TOKEN,ERR_PV);
    
    //ajouter et look up le ID
    //ajouterTIDF(CH,TPROG); // 
}






void first_sym(){
    lireCar();
    sym_Suiv();
}

int main(int argc, char const *argv[])
{
   /* PREMIER_SYM();
    */
    //debugSemantique();
    //printf("%d \n",OFFSET);
    /*if(symCour.CODE == EOF_TOKEN){
        printf("BRAVO : le programme est correcte !!!");
    }
    else printf("PAS BRAVO : fin de programme erronee !!!!");
*/
  fichier = fopen("test.txt","r");
  first_sym();
  procedure();
  printf(" success \n");
  /*lireCar();
  while (car_Cour!=EOF) {
      sym_Suiv();
      afficherToken();
      //cleanUp();
  }*/

	return 1;
}