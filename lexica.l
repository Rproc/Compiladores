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
STRING	\"[^\"]*\"

%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"		{return TK_TIPO_INT;}

"float"		{return TK_TIPO_FLOAT;}

"char"		{return TK_TIPO_CHAR;}

"bool"		{return TK_TIPO_BOOL;}

"string"	{return TK_TIPO_STRING;}

"global"    { return TK_GLOBAL; }

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

"if"        { return TK_IF; }

"else"      { return TK_ELSE; }

"while"     { return TK_WHILE; }

"do"        { return TK_DO; }

"for"       {return TK_FOR;}

"break"     { return TK_BREAK; }

"break all"     { return TK_BREAK_ALL; }

"break"[(]{DIGITO}+[)]  	{ yylval.label = yytext; return TK_BREAK_FUNC;  }

"continue"  {return TK_CONTINUE; }

"print"     { return TK_PRINT; }

"read"      { return TK_READ; }

"++"        { return TK_PP; }

"--"        { return TK_MM; }


"true"      { yylval.label = "1"; return TK_BOOL;  }
"false"     { yylval.label = "0"; return TK_BOOL;  }

{NUM}		{ yylval.label = yytext; return TK_NUM;  }
{CHAR}      { yylval.label = yytext; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID;   }
{REAL}      { yylval.label = yytext; return TK_REAL; }
{STRING}    { yylval.label = yytext; return TK_STRING; }

.			{ *yytext; }

%%
