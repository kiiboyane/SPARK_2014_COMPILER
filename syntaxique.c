#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include"analyseur_lexical_v0.h"



Erreurs MES_ERR[100]={{ERR_CAR_INC,"Caractère inconnu"},
                    {ERR_FICH_VID,"Fichier vide"},
                    {ERR_ID_LONG, "Identifiant très long" },
                    {ERR_COMM,"Commentaire non correct"},
                    {ERR_AFFEC," \":=\" expected "},{ERR_COND,"COND"},
                    {ERR_CONSTS,"CONSTS"},
                    {ERR_ID_PROCEDURE,"Identifier expected"},
                    {ERR_PROCEDURE,"procedure expected"},
                    {ERR_IS,"is expected"},
                    {ERR_BEGIN,"begin expected"},
                    {ERR_END,"end expected"},
                    {ERR_PV," ';' expected"},
                    {ERR_PF," ')' expected"},
                    {ERR_ARGS," '(' expected"},
                    {ERR_SEM,"ERREUR SEMANTIQUE"},
                    {ERR_PO," '(' expected"},
                    {ERR_P," ':' expected"},
                    {ERR_P," ':' expected"},
                    {TYPE_ERR," type unknown "},
                    {MODE_ERR," mode not found "},
                    {ERR_IMP," \"=>\" not found "},
                    {SPARK_MODE_ERR," on/off expected  "},
                    {ERR_NULL," null expected  "}  ,                
                    {DEC_ERR," missing operand  "} ,
                    {ERR_CHARACTER,"  missing operand "} ,
                    {ERR_AP,"  \" \'\" expected "} ,
                    {INSTRUCTION_ERR,"  statement expected "} ,
                    {ERR_IN,"  'in' expected "} ,
                    {ERR_LOOP," 'loop' expected "} ,
                    {ERR_PT," '.' expected "} ,
                    {ERR_THEN," 'then' expected "} ,
                    {ERR_IF," 'if' expected "} ,
                    {CONDITION_ERR," condition error  "}, 
                    {ERR_FACT," erreur dans l'expression "}, 
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
void numorid(); 
void var_declaration(); 
void declarations() ; 
void declaration(); 
void constant(); 
void charorid(); 
void var_declaration_aff();
void expr(); 
void while_ins(); 
void procedure_body();
void instruction(); 
void instructions_aux(); 
void instructions ();
void range(); 
void if_ins(); 
void for_ins(); 
void symbole_con(); 
void fact(); 
void term(); 


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
void type(){
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
void typewoc (){
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

void while_ins (){
     sym_Suiv();
     condition();
     Symbole_testing(LOOP_TOKEN,ERR_LOOP);
     instructions() ; 
     Symbole_testing(END_TOKEN,ERR_END);
     Symbole_testing(LOOP_TOKEN,ERR_LOOP);


}

void aff_ins(){
     Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
     Symbole_testing(AFF_TOKEN,ERR_AFFEC);
     expr();
}

void spark_mode(){
    Symbole_testing(IMP_TOKEN,ERR_IMP);
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
    expr() ; 
    symbole_con(); 
    sym_Suiv();
    expr();
}

void expr(){
    term();
    while(sym_Cour.CODE == PLUS_TOKEN || sym_Cour.CODE == MOINS_TOKEN){
        sym_Suiv();
        term();
    }
}

void term(){
    fact();
    while(sym_Cour.CODE == MUL_TOKEN || sym_Cour.CODE == DIV_TOKEN){
        sym_Suiv();
        fact();
    }
}

void fact(){
    switch(sym_Cour.CODE){
        case ID_TOKEN :
                       sym_Suiv(); break;
        case NUM_TOKEN : sym_Suiv(); break;
        case PO_TOKEN : sym_Suiv();
                        expr();
                        Symbole_testing(PF_TOKEN,ERR_PF);
                        break;
        default : Gen_Erreur(ERR_FACT);
    }
}
void symbole_con(){
   switch(sym_Cour.CODE){
        case EG_TOKEN :
                  break; 
        case DIFF_TOKEN :
                  break; 
        case INF_TOKEN :
                  break; 
        case SUP_TOKEN :
                  break; 
        case INFEG_TOKEN :
                  break; 
        case SUPEG_TOKEN :
                  break; 
        default :Gen_Erreur(CONDITION_ERR);
                break; 
       }
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

void declarations (){
  switch(sym_Cour.CODE){
        case BEGIN_TOKEN :
                  break; 
        default : 
                declaration(); 
                declarations(); 
                break; 
       }

}
void declaration(){
  switch(sym_Cour.CODE){
     case ID_TOKEN :
                  var_declaration();
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
     case PROCEDURE_TOKEN :
                  procedure() ;
                  break; 
      default :   break; 
       }

}

void var_declaration(){
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    Symbole_testing(P_TOKEN,ERR_P);
    constant();
    var_declaration_aff(); 
}
void var_declaration_aff(){
   switch(sym_Cour.CODE){
     case CHARACTER_TOKEN :
                sym_Suiv();
                Symbole_testing(AFF_TOKEN,ERR_AFFEC);
                charorid();
                break;
      default :  
              typewoc(); 
              Symbole_testing(AFF_TOKEN,ERR_AFFEC);
              numorid();
              sym_Suiv();
              break; 
       }
}
void charorid(){
    switch(sym_Cour.CODE){
     case ID_TOKEN :
                 sym_Suiv();
                  break;
      case AP_TOKEN :
                  sym_Suiv();
                  numorid();
                  sym_Suiv();
                  Symbole_testing(AP_TOKEN,ERR_AP);
                  break;
      default :  Gen_Erreur(DEC_ERR);
              break; 
       }
}
void constant(){
   switch(sym_Cour.CODE){
     case CONSTANT_TOKEN :
                  sym_Suiv();
                  break;
      default :   break; 
       }
}

void numorid (){
     switch(sym_Cour.CODE){
     case NUM_TOKEN :
                  break;
      case ID_TOKEN :
                  break;
      default :  Gen_Erreur(DEC_ERR);
              break; 
       }
}

void procedure_body(){
  instructions(); 
}

void  instructions(){
    instruction (); 
    instructions_aux();
}

void instruction(){
  switch(sym_Cour.CODE){
    case NULL_TOKEN :
                  sym_Suiv() ;
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
    case FOR_TOKEN :
                  for_ins(); 
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
    case IF_TOKEN :
                  if_ins(); 
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
    case WHILE_TOKEN :
                  while_ins();
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
    case ID_TOKEN :
                  aff_ins(); 
                  Symbole_testing(PV_TOKEN,ERR_PV);
                  break;
    case PROCEDURE_TOKEN :
                 procedure(); 
                  break;
    default :  Gen_Erreur(INSTRUCTION_ERR);
              break; 
       }

}


void instructions_aux (){
     switch(sym_Cour.CODE){
            case END_TOKEN :
                          break;
            default : instruction(); 
                     break; 
       }   
     
}
void for_ins(){
    sym_Suiv() ;
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    Symbole_testing(IN_TOKEN,ERR_IN);
    range(); 
    Symbole_testing(LOOP_TOKEN,ERR_LOOP);
    instructions(); 
    Symbole_testing(END_TOKEN,ERR_END);
    Symbole_testing(LOOP_TOKEN,ERR_LOOP);
}
void range (){
    numorid(); 
    sym_Suiv();
    Symbole_testing(PT_TOKEN,ERR_PT);
    Symbole_testing(PT_TOKEN,ERR_PT);
    numorid(); 
    sym_Suiv();
}

void if_ins(){
    sym_Suiv() ;
    condition(); 
    Symbole_testing(THEN_TOKEN,ERR_THEN);
    instructions();
    // elseaux();
    Symbole_testing(END_TOKEN,ERR_END);
    Symbole_testing(IF_TOKEN,ERR_IF);

}


void procedure(){
    Symbole_testing(PROCEDURE_TOKEN,ERR_PROCEDURE);
    Symbole_testing(ID_TOKEN,ERR_ID_PROCEDURE);
    args(); 
    Symbole_testing(IS_TOKEN,ERR_IS);
    declarations(); 
    Symbole_testing(BEGIN_TOKEN,ERR_BEGIN);
    procedure_body();
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
  /* lireCar();
  while (car_Cour!=EOF) {
      sym_Suiv();
      afficherToken();*/
      //cleanUp();
  //}

	return 1;
}