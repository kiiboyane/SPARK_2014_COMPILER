#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void program () ; 
void procedure () ; 
void args () ; 
void args_dec (); 
void args_dec_aux ();
void arg_dec (); 
void id_tokens (); 
void id_tokens_aux ();
void type (); 
void contract (); 
void modes (); 
void mode_aux (); 
void mode (); 
void spark_mode (); 
void global_mode (); 
void depends_mode (); 
void pre_mode (); 
void post_mode (); 
void declarations (); 
void declaration (); 
void var_declaration (); 
void procedure_body (); 
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
void while_ins (); 


typedef enum CODES_ERREURS{
	ERR_CAR_INC,ERR_FICH_VID, 
    ERR_ID_LONG,ERR_COMM,
    ERR_AFFEC,ERR_COND,
    ERR_CONSTS,ERR_ECRIRE,
    ERR_FACT,ERR_INST,
    ERR_INSTS,ERR_LIRE,
    ERR_PROGRAM,ERR_SI,
    ERR_TANTQUE,ERR_VARS,ERR_SEM,ERR_PROCEDURE,
    ERR_ID_PROCEDURE,ERR_IS,ERR_BEGIN,ERR_END,
    ERR_PV
}CODES_ERREURS;


typedef  struct Erreurs{
    CODES_ERREURS CODE_ERR; char mes[100];
}Erreurs;


Erreurs	MES_ERR[100]={{ERR_CAR_INC,"Caractère inconnu"},
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
                    {ERR_SI,"SI"},
                    {ERR_TANTQUE,"TANTQUE"},
                    {ERR_VARS,"VARS"},
                    {ERR_SEM,"ERREUR SEMANTIQUE"}};



void procedure(){
    testSymbole(PROCEDURE_TOKEN,ERR_PROCEDURE);
  	testSymbole(ID_TOKEN,ERR_ID_PROCEDURE);
  	args(); 
  	contract(); 
  	testSymbole(IS_TOKEN,ERR_IS);
  	declarations(); 
  	testSymbole(BEGIN_TOKEN,ERR_BEGIN);
  	procedure_body();
  	testSymbole(END_TOKEN,ERR_END);
  	testSymbole(ID_TOKEN,ERR_ID_PROCEDURE);
  	testSymbole(PV_TOKEN_TOKEN,ERR_PV);

    //ajouter et look up le ID
    //ajouterTIDF(CH,TPROG); // 
}

void args(){
	
}



int main(int argc, char const *argv[])
{
    //fichier = fopen("test1.txt","r");
   /* PREMIER_SYM();
    procedure();
    printf("\n");*/
    //debugSemantique();
    //printf("%d \n",OFFSET);
    /*if(symCour.CODE == EOF_TOKEN){
        printf("BRAVO : le programme est correcte !!!");
    }
    else printf("PAS BRAVO : fin de programme erronee !!!!");
*/
	return 1;
}