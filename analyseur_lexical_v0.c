#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"analyseur_lexical_v0.h"




/////////////STRUCT TOKEN ///////////






void Gen_Erreur(CODES_ERREURS  ERR){
    int  ind=ERR;
    printf( "Erreur numéro %d : %s \n", ind, MES_ERR[ind+1].message);
    exit(1);
}

void lireCar(){
         car_Cour=fgetc(fichier);
}


void lireMot(){
    memset(sym_Cour.NOM , '\0' , 100); 
    sym_Cour.NOM[0]=car_Cour;
    int i =1;
    lireCar();
    while((car_Cour>='a' && car_Cour<='z')||(car_Cour>='A' && car_Cour<='Z')||(car_Cour>=48 && car_Cour<=57) || car_Cour==95){ // a-z A-Z 0-9
        sym_Cour.NOM[i]=car_Cour;
        i++;
        lireCar();
    }
    if(strlen(sym_Cour.NOM)>20){
        sym_Cour.CODE = ERREUR_TOKEN;
        Gen_Erreur(ERR_ID_LONG);
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

     else if (strcmpi(sym_Cour.NOM,"with")==0){
        sym_Cour.CODE = WITH_TOKEN;
    }

     else if (strcmpi(sym_Cour.NOM,"global")==0){
        sym_Cour.CODE = GLOBAL_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"depends")==0){
        sym_Cour.CODE = DEPENDS_TOKEN;
    }
      else if (strcmpi(sym_Cour.NOM,"pre")==0){
        sym_Cour.CODE = PRE_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"post")==0){
        sym_Cour.CODE = POST_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"integer")==0){
        sym_Cour.CODE = INTEGER_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"GET")==0){
        sym_Cour.CODE = GET_TOKEN;
    }

     else if (strcmpi(sym_Cour.NOM,"is")==0){
        sym_Cour.CODE = IS_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"constant")==0){
        sym_Cour.CODE = CONSTANT_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"null")==0){
        sym_Cour.CODE = NULL_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"natural")==0){
        sym_Cour.CODE = NATURAL_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"and")==0){
        sym_Cour.CODE = AND_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"or")==0){
        sym_Cour.CODE = OR_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"SPARK_MODE")==0){
        sym_Cour.CODE = SPARK_MODE_TOKEN;
    }
     else if (strcmpi(sym_Cour.NOM,"of")==0){
        sym_Cour.CODE = OF_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"off")==0){
        sym_Cour.CODE = OFF_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"positive")==0){
        sym_Cour.CODE = POSITIVE_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"loop")==0){
        sym_Cour.CODE = LOOP_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"string")==0){
        sym_Cour.CODE = STRING_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"CHARACTER")==0){
        sym_Cour.CODE = CHARACTER_TOKEN;
    }
    else if (strcmpi(sym_Cour.NOM,"reverse")==0){
        sym_Cour.CODE = REVERSE_TOKEN;
    }
     else  {
        sym_Cour.CODE = ID_TOKEN;
        //strcpy(sym_Cour.NOM,sym_Cour.NOM);
    }

}

void lireNombre(){
    memset(sym_Cour.NOM , '\0' , 100); 
    sym_Cour.NOM[0] = car_Cour;
    int i =1;
    lireCar();
    while(car_Cour>=48 && car_Cour<=57){ // 0-9
        sym_Cour.NOM[i]=car_Cour;
        i++;
        lireCar();
    }
    sym_Cour.CODE = NUM_TOKEN;
}

void lireCommentaire(){
    if(car_Cour =='-'){
        lireCar();
        while(!feof(fichier) && car_Cour!='\n' && car_Cour!='\r'){
            //printf("%c", car_Cour);
            lireCar();
        }
        sym_Cour.CODE = COMMENTAIRE_TOKEN;
    }
    else{
        sym_Cour.CODE=ERREUR_TOKEN;
    }
}

void afficherToken(){
    switch(sym_Cour.CODE){
        case 1000 : printf("PROCEDURE_TOKEN"); break;
        case 1001 : printf("IN_TOKEN "); break;
        case 1002 : printf("OUT_TOKEN "); break;
        case 1003 : printf("WITH_TOKEN "); break;
        case 1004 : printf("GLOBAL_TOKEN "); break;
        case 1005 : printf("DEPENDS_TOKEN "); break;
        case 1006 : printf("NUM_TOKEN "); break;
        case 1007 : printf("PRE_TOKEN "); break;
        case 1008 : printf("POST_TOKEN "); break;
        case 1009 : printf("INTEGER_TOKEN"); break;
        case 1010 : printf("BEGIN_TOKEN"); break;
        case 1011 : printf("END_TOKEN "); break;
        case 1013 : printf("PV_TOKEN "); break;
        case 1052 : printf("V_TOKEN "); break;
        case 1017 : printf("IS_TOKEN "); break;
        case 1018 : printf("CONSTANT_TOKEN "); break;
        case 1019 : printf("PLUS_TOKEN"); break;
        case 1020 : printf("AFF_TOKEN "); break;
        case 1021 : printf("EG_TOKEN "); break;
        case 1022 : printf("PO_TOKEN "); break;
        case 1023 : printf("PF_TOKEN "); break;
        case 1024 : printf("P_TOKEN "); break;
        case 1025 : printf("PT_TOKEN "); break;
        case 1026 : printf("NULL_TOKEN "); break;
        case 1027 : printf("PACKAGE_TOKEN "); break;
        case 1028 : printf("NUM_TOKEN "); break;
        case 1029 : printf("ERREUR_TOKEN "); break;
        case 1030 : printf("NATURAL_TOKEN ");break;
        case 1031 : printf("AND_TOKEN ");break;
        case 1032 : printf("OR_TOKEN"); break;
        case 1033 : printf("SPARK_MODE_TOKEN"); break;
        case 1040 : printf("OF_TOKEN"); break;
        case 1041 : printf("OFF_TOKEN"); break;
        case 1048 : printf("LOOP_TOKEN"); break;
        case 1042 : printf("POSITIVE_TOKEN"); break;
        case 1049 : printf("THEN_TOKEN"); break;
        case 1050 : printf("IF_TOKEN"); break;
        case 1054 : printf("CHARACTER_TOKEN"); break;
        case 1055 : printf("INF_TOKEN"); break;
        case 1056 : printf("SUP_TOKEN"); break;
        case 1057 : printf("DIFF_TOKEN"); break;
        case 1058 : printf("IMP_TOKEN"); break;
        case 1059 : printf("FOR_TOKEN"); break;
        case 1064 : printf("WHILE_TOKEN"); break;
        case 1065 : printf("PUT_TOKEN"); break;
        case 1066 : printf("GET_TOKEN"); break;
        case 1067 : printf("ID_TOKEN"); break;
        case 1070 : printf("MOINS_TOKEN"); break;
        case 1071 : printf("MUL_TOKEN"); break;
        case 1072 : printf("DIV_TOKEN"); break;
        case 1062 : printf("INFEG_TOKEN"); break;
        case 1063 : printf("SUPEG_TOKEN"); break;
        case 1068 : printf("COMMENTAIRE_TOKEN"); break;
        case 1074 : printf("AP_TOKEN"); break;




    }
    printf("\n");
    printf("\t %s \n",sym_Cour.NOM);
}

void sym_Suiv(){
    //cleanUp();

    while(car_Cour == 32 || car_Cour==9 || car_Cour == 10 || car_Cour == 13){ // espace tabulation retour chariot
        lireCar();
    }
    if((car_Cour>=97 && car_Cour<=122)||(car_Cour>=65 && car_Cour<=90)){ // a-z A-Z
        lireMot();
    }
    else if(car_Cour>=48 && car_Cour<=57){ // 0-9
        lireNombre();
    }
    else if(car_Cour == EOF){
        sym_Cour.CODE = EOF_TOKEN;
    }
    else{
        memset(sym_Cour.NOM , '\0' , 100); 
        sym_Cour.NOM[0]=car_Cour;
        switch(car_Cour){
            case '+' : sym_Cour.CODE = PLUS_TOKEN; lireCar();break;//+
            case '\'' : sym_Cour.CODE = AP_TOKEN; lireCar();break;// '\''
            case '*' : sym_Cour.CODE = MUL_TOKEN; lireCar();break;//*
            case ',' : sym_Cour.CODE = V_TOKEN;lireCar();break;//,
           // case '-' : sym_Cour.CODE = MOINS_TOKEN; lireCar();break;//-
            case '(' : sym_Cour.CODE = PO_TOKEN; lireCar();break;//(
            case ')' : sym_Cour.CODE = PF_TOKEN; lireCar();break;//)
            case '.' : sym_Cour.CODE = PT_TOKEN; lireCar();break;//.
            case '/' : sym_Cour.CODE = DIV_TOKEN; lireCar();break;// /
            case ';' : sym_Cour.CODE = PV_TOKEN; lireCar();break;// ;
            case '<' :
                lireCar();
                if (car_Cour =='=') {sym_Cour.CODE= INFEG_TOKEN;sym_Cour.NOM[1]='=';lireCar();}
                else if (car_Cour =='>') {sym_Cour.CODE = DIFF_TOKEN;sym_Cour.NOM[1]='>';lireCar();}
                else {sym_Cour.CODE = INF_TOKEN;}
                break;
            case '>' :
                lireCar();
                if (car_Cour == '=') {sym_Cour.CODE = SUPEG_TOKEN;sym_Cour.NOM[1]='=';lireCar();}
                else {sym_Cour.CODE = SUP_TOKEN;}
                break;
            case ':' : // :
                lireCar();
                if (car_Cour == '=') {sym_Cour.CODE = AFF_TOKEN;sym_Cour.NOM[1]='=';lireCar();}
                else {
                    sym_Cour.CODE = P_TOKEN;
                }
                break;
            case '-' :
                lireCar();
                if (car_Cour == '-'){sym_Cour.CODE = COMMENTAIRE_TOKEN; lireCommentaire();}
                else {
                    sym_Cour.CODE = MOINS_TOKEN;
                }
                break;
            case '=' :
                lireCar();
                if (car_Cour == '>') {sym_Cour.CODE = IMP_TOKEN;sym_Cour.NOM[1]='>';lireCar();}
                else {
                    sym_Cour.CODE = EG_TOKEN;
                }
                break;
            default : // car inconnu
                sym_Cour.CODE = ERREUR_TOKEN;
                Gen_Erreur(ERR_CAR_INC);
                //lireCar();
        }
    }
}


void testSymbole (TOKENS cl, CODES_ERREURS err){
    if (sym_Cour.CODE == cl)
    {
        afficherToken();
        sym_Suiv();
    }
    else
        Gen_Erreur(err);
}






