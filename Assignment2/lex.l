/*** Definition section ***/
%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
%}
digit [0-9]
comment "/*"|"//"|"*/"
keywords auto|else|long|switch|break|enum|register|typedef|case|extern|return|union|char|float|short|unsigned|const|for|signed|void|continue|goto|sizeof|volatile|default|if|static|while|do|int|struct|_Packed|double
identifier	[a-zA-Z][a-zA-Z0-9_]*
whitespace [ \t\n]+ 	
%%
{whitespace}
{comment}+.*{comment}*  {printf("Comments : %s  \n ",yytext);}
["].*["] {printf("String literal : %s  \n",yytext);}
['].['] {printf("Character : %s  \n",yytext);}
;|,|"."|":"
#[a-zA-Z0-9]+{whitespace}(<[a-zA-Z0-9"."]+>|[a-zA-Z0-9]*) {printf("Preprocessors : %s  \n", yytext);}
"+"+|"-"+|"*"|"/"|"%" {printf("Arithmetic opertor : %s  \n",yytext);}
"=="|">="|"<="|"!="|">"|"<" {printf("Relational operator : %s  \n",yytext);}
"&&"|"||"|"!" {printf("Logical operator : %s  \n", yytext);}
"&"|"|"|"<<"|"~"|">>"|"^" {printf("Bitwise operator : %s  \n", yytext);}
("+"|"-"|"%"|"/"){0,1}"=" {printf("Assignment operator : %s  \n", yytext);}
{keywords} {printf("Keyword : %s  \n", yytext);}
{identifier} {printf("Identifier : %s  \n", yytext);}
{digit}+ {printf("Integer constant : %d  \n", atoi(yytext));}
{digit}+.{digit}+ {printf("Float constant : %f  \n", atof(yytext));}
("{"|"}"|"["|"]"|"("|")")+ 
"/n" {yylineno++;}
%%

/*** C Code section ***/
void main(int argc, char ** argv)
{   
    if (argc==2){
        yyin=fopen(argv[1],"r");
    }
    else{
        printf("Enter expression to be evaluated : ");
    }
    yylex();
}