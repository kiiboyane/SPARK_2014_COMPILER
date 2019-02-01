#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef enum TOKENS
{

PROCEDURE_TOKEN  = 1000,
IN_TOKEN          = 1001,
OUT_TOKEN        = 1002,
WITH_TOKEN       = 1003,
GLOBAL_TOKEN     = 1004,
DEPENDS_TOKEN   = 1005,
NUM_TOKEN = 1006,
PRE_TOKEN  = 1007,
POST_TOKEN = 1008,
INTEGER_TOKEN = 1009,
BEGIN_TOKEN = 1010,
END_TOKEN = 1011,
OLD_TOKEN = 1012,
PV_TOKEN  = 1013,
LAST_TOKEN = 1014,
RETURN_TOKEN = 1015,
FUNCTION_TOKEN = 1016,
IS_TOKEN = 1017,
CONSTANT_TOKEN = 1018,
PLUS_TOKEN = 1019,
AFF_TOKEN = 1020,
EG_TOKEN = 1021,
PO_TOKEN = 1022,
PF_TOKEN = 1023,
P_TOKEN  = 1024,
PT_TOKEN = 1025,
NULL_TOKEN = 1026,
PACKAGE_TOKEN = 1027,
BODY_TOKEN  = 1028,
COMS_TOKEN = 1029,
NATURAL_TOKEN = 1030,
AND_TOKEN  = 1031,
OR_TOKEN  = 1032,
SPARK_MODE_TOKEN = 1033,
PRAGMA_TOKEN  = 1034,
ASSERT_TOKEN = 1035,
TYPF_TOKEN = 1036,
NEW_TOKEN =1037,
PRIVATE_TOEKN = 1038,
ARRAY_TOKEN = 1039,
OF_TOEKN = 1040,
OFF_TOKEN = 1041,
POSITIVE_TOKEN = 1042,
RECORD_TOKEN = 1043,
FIRST_TOKEN = 1044,
RANGE_TOKEN = 1045,
SUBTYPE = 1046,
RAISE_TOKEN = 1047,
LOOP_TOKEN = 1048,
THEN_TOKEN = 1049,
IF_TOKEN = 1050,
EXCEPTION_TOKEN = 1051,
V_TOKEN = 1052,
STRING_TOKEN = 1053,
CHARACTER_TOKEN = 1054,
INF_TOKEN = 1055,
SUP_TOKEN = 1056,
DIFF_TOKEN =1057,
IMP_TOKEN =1058,
FOR_TOKEN  =1059,
ERREUR_TOKEN =1060,
REVERSE_TOKEN =1061,
INFEG_TOKEN =1062,
SUPEG_TOKEN =1063,
WHILE_TOKEN =1064,
PUT_TOKEN =1065,
GET_TOKEN =1066



}TOKENS;


/////////////STRUCT TOKEN ///////////
typedef  struct {

    TOKENS CODE; char NOM[100];

}Token_sym_Cour;



typedef enum{
	ERR_CAR_INC,ERR_FICH_VID,
    ERR_ID_LONG,ERR_COMM
}CODES_ERREURS;

typedef  struct{
    CODES_ERREURS CODE_ERR; char message[40];
}Erreurs;


Erreurs	MES_ERR[100]={{ERR_CAR_INC,"Caractère inconnu"},{ERR_FICH_VID,"Fichier vide"},{ERR_ID_LONG, "Identifiant très long" },{ERR_COMM,"Commentaire non correct"}};

// Variables Globales

char car_Cour; 					//caractère courant
Token_sym_Cour sym_Cour; 				//symbole courant
FILE* fichier;


void Gen_Erreur(CODES_ERREURS  ERR){
	int  ind=ERR;
	printf( "Erreur numéro %d : %s \n", ind, MES_ERR[ind].message);
	exit(1);
}

void lireCar(){
         car_Cour=fgetc(fichier);
}


void lireMot(){
    sym_Cour.NOM[0]=car_Cour;
    int i =1;
    lireCar();
    while((car_Cour>='a' && car_Cour<='z')||(car_Cour>='A' && car_Cour<='Z')||(car_Cour>=48 && car_Cour<=57)){ // a-z A-Z 0-9
        sym_Cour.NOM[i]=car_Cour;
        i++;
        lireCar();
    }
    if(strlen(sym_Cour.NOM)>20){
        sym_Cour.CODE = ERREUR_TOKEN;
        Erreur(ERR_ID_LONG);
    }
    else if (strcmpi(sym_Cour.NOM,"procedure")==0){
        sym_Cour.CODE = PROCEDURE_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"in")==0){
        sym_Cour.CODE = IN_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"out")==0){
        sym_Cour.CODE = OUT_TOKEN;
    }

    else if (strcmpi(sym_Cour.NOM,"begin")==0){
        sym_Cour.CODE = BEGIN_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"end")==0){
        sym_Cour.CODE = END_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"if")==0){
        sym_Cour.CODE = IF_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"then")==0){
        sym_Cour.CODE = THEN_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"while")==0){
        sym_Cour.CODE = WHILE_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"put")==0){
        sym_Cour.CODE = PUT_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"get")==0){
        sym_Cour.CODE = GET_TOKEN;
    }
    else{
        sym_Cour.CODE = ID_TOKEN;
        //strcpy(sym_Cour.NOM,sym_Cour.NOM);
    }
}


void main(){


}
