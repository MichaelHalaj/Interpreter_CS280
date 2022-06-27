#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include "lex.h"
#include <string>


LexItem getNextToken(istream& in, int& linenum){
    enum TokState {START, INID, INSTRING, ININT, INREAL, INCOMMENT}
    lexstate = START;
    string lexeme;
    char ch;
  //  Token tok;
    while (in.get(ch)){
        switch(lexstate){
            case START:
                if(ch == '\n'){
                    linenum++;
                }
                if(in.peek() == EOF) {
                    LexItem done(DONE, "DONE", linenum);
                    return done;
                }
                if(isspace(ch)){
                    break;
                }

                ch = toupper(ch);
                lexeme = ch;
                if(isalpha(ch) || ch == '_'){
                    lexstate = INID;
                    break;
                }else if(ch == '.'){
                    lexstate = INREAL;
                    break;
                }else if(isdigit(ch)){
                    lexstate = ININT;
                    break;
                }else if(ch == '(' ){
                    in.get(ch);
                    if(ch == '*'){
                        lexeme += ch;
                        lexstate = INCOMMENT;
                        break;
                    }else{
                        in.putback(ch);
                        LexItem punct =  id_or_kw(lexeme, linenum);
                        return punct;

                    }
                }else if(ch == '\''){
                    lexstate = INSTRING;
                    break;
                }else{
                    if(ch == ':'){
                        in.get(ch);
                        if(ch == '='){
                            lexeme += ch;
                            LexItem punct =  id_or_kw(lexeme, linenum);
                            return punct;
                        }
                    }

                   LexItem punct =  id_or_kw(lexeme, linenum);
                    if(punct == IDENT){
                        linenum++;
                        cout << "Error in line " << linenum << " (" << lexeme << ")" << endl;
                        LexItem error(ERR, lexeme, linenum);
                        return error;
                    }
                    return punct;

                }
            case INID:
                ch = toupper(ch);
                if(isalnum(ch) || ch == '_'){
                    lexeme += ch;
                }else{
                    in.putback(ch);
                    LexItem id = id_or_kw(lexeme, linenum);
                    return id;
                }
                break;
            case INSTRING:
                if(in.peek() == EOF){
                    linenum++;
                    LexItem error (ERR, lexeme, linenum);
                    cout << "Error in line " << linenum << " (" << lexeme << ")" << endl;
                    return error;
                }
                lexeme += ch;
                if(!isalnum(ch) && !isspace(ch) && ch != '\'') {
                    linenum++;
                    LexItem error(ERR, lexeme, linenum);
                    cout << "Error in line " << linenum << " (" << lexeme << ")" << endl;
                    return error;
                }
                if(ch == '\''){
                    LexItem str (SCONST, lexeme, linenum);
                    return str;
                }


                break;
            case ININT:


                if(!isdigit(ch)){
                    if(ch == '.'){
                        lexeme += ch;
                        if(!isdigit(in.peek())){
                            linenum++;
                            LexItem error(ERR, lexeme, linenum);
                            cout << "Error in line " << linenum << " (" << lexeme << ")" << endl;
                            return error;
                        }
                            lexstate = INREAL;
                            break;
                    }
                    else{
                        in.putback(ch);
                        LexItem validInt (ICONST, lexeme, linenum);
                        return validInt;
                    }
                }
                lexeme +=ch;
               // cout << lexeme << endl;
                break;
            case INREAL:
                if(ch == '.'){
                    lexeme+=ch;
                    linenum++;
                    LexItem error(ERR, lexeme, linenum);
                    cout << "Error in line " << linenum << " (" << lexeme << ")" << endl;
                    return error;
                }else if(!isdigit(ch)){
                        in.putback(ch);
                        LexItem realNum(RCONST, lexeme, linenum);
                        return realNum;
                }
                lexeme += ch;

                break;
            case INCOMMENT:
                lexeme += ch;
                if(ch == '*'){
                    in.get(ch);
                    if(ch == ')'){
                        lexeme = "";
                        lexstate = START;
                        break;
                    }else{
                        linenum++;
                        LexItem error(ERR, "comment", linenum);

                        cout <<  endl << "Missing a comment end delimiters '*)' at line " << linenum << endl;
                        return error;
                    }
                }else if(in.peek() == EOF){
                    linenum++;
                    LexItem error(ERR, "comment", linenum);
                    cout << endl << "Missing a comment end delimiters '*)' at line " << linenum << endl;
                    return error;
                }else if(ch == '\n'){
                    linenum++;
                }
                break;
        }
    }
    LexItem done (DONE, "DONE", linenum);
    return done;
}




LexItem id_or_kw(const string& lexeme, int linenum){
    Token token; //var to initialize later
    if (lexeme == "PROGRAM"){
        token = PROGRAM;
    }else if(lexeme == "WRITELN"){
        token = WRITELN;
    }else if (lexeme == "INTEGER"){
        token = INTEGER;
    }else if (lexeme == "BEGIN"){
        token = BEGIN;
    }else if (lexeme == "END"){
        token = END;
    }else if (lexeme == "IF"){
        token = IF;
    }else if (lexeme == "REAL"){
        token = REAL;
    }else if (lexeme == "STRING"){
        token = STRING;
    }else if (lexeme == "VAR"){
        token = VAR;
    }else if (lexeme == "ELSE"){
        token = ELSE;
    }else if (lexeme == "FOR"){
        token = FOR;
    }else if (lexeme == "THEN"){
        token = THEN;
    }else if (lexeme == "DO"){
        token = DO;
    }else if (lexeme == "TO"){
        token = TO;
    }else if (lexeme == "DOWNTO"){
        token = DOWNTO;
    }else if (lexeme == "+"){
        token = PLUS;
    }else if (lexeme == "-"){
        token = MINUS;
    }else if (lexeme == "*"){
        token = MULT;
    }else if (lexeme == "/"){
        token = DIV;
    }else if (lexeme == ":="){
        token = ASSOP;
    }else if (lexeme == "("){
        token = LPAREN;
    }else if (lexeme == ")"){
        token = RPAREN;
    }else if (lexeme == ","){
        token = COMMA;
    }else if (lexeme == "="){
        token = EQUAL;
    }else if (lexeme == ">"){
        token = GTHAN;
    }else if (lexeme == "<"){
        token = LTHAN;
    }else if (lexeme == ";"){
        token = SEMICOL;
    }else if (lexeme == ":"){
        token = COLON;
    }else if (lexeme == "ERR"){
        token = ERR;
    }else if (lexeme == "DONE"){
        token = DONE;
    }else{
        token = IDENT;
    }
    LexItem rtnItem(token, lexeme, linenum);
    return rtnItem;
}


