%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]


DELIM {ESPACO}+
NUM (-)?{DIGITO}+
REAL (-)?{NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM})\'
ID {LETRA}({LETRA}|{NUM})*

%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"float"		{return TK_TIPO_FLOAT;}

"char"		{return TK_TIPO_CHAR;}

"bool"		{return TK_TIPO_BOOL;}

[(){}[\];,]	{ return *yytext; }

[+\-*/=\^]	{ return *yytext; }

">"         { return *yytext;}

"<"         { return *yytext;}

">="        { return TK_GTE;}

"<="        { return TK_LTE; }

"=="        { return TK_EQUAL;  }

"equals"    { return TK_EQUAL;  }

"!="        { return TK_NEQUAL;  }

"and"       { return TK_AND;  }

"or"        { return TK_OR;  }

"not"       { return TK_NOT; }



"true"      { yylval.label = yytext; return TK_BOOL;  }
"false"     { yylval.label = yytext; return TK_BOOL;  }

{NUM}		{ yylval.label = yytext; return TK_NUM;  }
{CHAR}      { yylval.label = yytext; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID;   }
{REAL}      { yylval.label = yytext; return TK_REAL; }


.			{ *yytext; }

%%
