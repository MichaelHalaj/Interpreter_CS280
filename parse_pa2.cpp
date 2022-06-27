/* Definitions and some functions implementations
 * parse.cpp to be completed
 * Programming Assignment 2
 * Spring 2022
*/

#include "parse.h"


map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;
}


//Stmt is either a WriteLnStmt, ForepeatStmt, IfStmt, or AssigStmt
//Stmt = AssigStmt | IfStmt | WriteStmt | ForStmt
bool Stmt(istream& in, int& line) {
    bool status;
    //cout << "in ContrlStmt" << endl;
    LexItem t = Parser::GetNextToken(in, line);
    switch( t.GetToken() ) {

        case WRITELN:
            status = WriteLnStmt(in, line);
            //cout << "After WriteStmet status: " << (status? true:false) <<endl;
            break;

        case IF:
            status = IfStmt(in, line);
            break;

        case IDENT:
            Parser::PushBackToken(t);
            status = AssignStmt(in, line);
            break;
        case FOR:
            status = ForStmt(in, line);
            break;

        default:
            Parser::PushBackToken(t);
            return false;
    }
    return status;
}//End of Stmt
bool ForStmt(istream& in, int& line){
    LexItem tok;
    bool status = Var(in, line);
    if(!status){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != ASSOP){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != ICONST){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != TO && tok.GetToken() != DOWNTO){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != ICONST){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != DO){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    status = Stmt(in, line);
    if(!status){
        ParseError(line, "For Statement Syntax Error");
        return false;
    }
    return status;
}

bool AssignStmt(istream& in, int& line){
    LexItem tok;
    bool status = Var(in, line);
    if(!status){
        ParseError(line, "Missing Left Hand Side Variable in Assignment Statement");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    //cout << tok << endl;
    if(tok == ASSOP){
        bool validExpr = Expr(in, line);
        //cout << validExpr << endl;
        if(!validExpr){
            ParseError(line, "Missing Expression in Assignment Statement");
            return false;
        }
    }else{
        ParseError(line, "Missing assignment operator");
        return false;
    }
    /*
        if(!defVar.find(tok.GetLexeme())->second){
            tok = Parser::GetNextToken(in, line);
            cout << "big";
            if(tok == ASSOP){
                cout << "your mother";
                bool validExpr = Expr(in, line);
                return validExpr;
            }else{
                ParseError(line, "Incorrect Declaration 12312");
                return false;
            }

        }else{
            ParseError(line, "Undeclared variable");
            return false;
        }
*/
    return status;
    }

//WriteStmt:= wi, ExpreList
bool WriteLnStmt(istream& in, int& line) {
    LexItem t;
    //cout << "in WriteStmt" << endl;

    t = Parser::GetNextToken(in, line);
    if( t != LPAREN ) {

        ParseError(line, "Missing Left Parenthesis");
        return false;
    }

    bool ex = ExprList(in, line);

    if( !ex ) {
        ParseError(line, "Missing expression after WriteLn");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if(t != RPAREN ) {

        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    //Evaluate: print out the list of expressions values

    return ex;
}


//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
    bool status = false;
    //cout << "in ExprList and before calling Expr" << endl;
    status = Expr(in, line);
    if(!status){
        ParseError(line, "Missing Expression");
        return false;
    }

    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == COMMA) {
        //cout << "before calling ExprList" << endl;
        status = ExprList(in, line);
        //cout << "after calling ExprList" << endl;
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(tok);
        return true;
    }
    return status;
}
bool Expr(istream& in, int& line) {
   // LexItem tok = Parser::GetNextToken(in, line);
   LexItem tok;
    bool t1;
   /* if(tok.GetToken() == SEMICOL){
        Parser::PushBackToken(tok);
        return true;*/
    /*}else if(tok.GetToken() == LPAREN){
        Parser::PushBackToken(tok);
        //bool t0 = Factor(in ,line ,0);
       // bool t0 = SFactor(in ,line);
       bool t0 = Term(in,line);
        cout << "Status " <<  t0 << endl;
        cout << "Left paren expr" << endl;
        if(!t0){
            //cout << "Returning false" << endl;
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        //hasLParen = true;
        */
   /* }else if(tok.GetToken() == RPAREN){
        Parser::PushBackToken(tok);
        return false;
    }else{
        cout << "Tok being pushed back inside of expr :: " << tok << endl;

        Parser::PushBackToken(tok);

    }*/
    t1 = Term(in, line);
    if( !t1 ) {
        return false;}
    tok = Parser::GetNextToken(in, line);
    //cout << tok << line << endl;

    //cout << "Tok after getting token in Term :: " << tok << endl;

//cout << "Should be moving to this position" << endl;

    //cout <<"Token that should be plus or mult " << tok  << line << endl;
    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" <<endl;
        return false;}
    while ( tok == PLUS || tok == MINUS ) {
        t1 = Term(in, line);
        if( !t1 ) {
            ParseError(line, "Missing operand after operator");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    //cout << "PUSHING BACK LAST IN EXPR :: " << tok << endl;

    Parser::PushBackToken(tok); return true;
    //THIS CODE WAS TO CHECK A MATCHING RPAREN BUT IT DOESN'T WORK HERE
    //MAYBE CHECK FOR MATCHING PAREN IN ANOTHER FUNCTION
    /*
    if(tok.GetToken() == RPAREN){
        if(hasLParen){
            Parser::PushBackToken(tok);
            return true;
        }else{
            ParseError(line, "Missing Left Parentheses");
            return false;

        }
    }*/

}
bool Term(istream& in, int& line){
    LexItem tok;
    //bool hasLParen = false;
  //  cout << "First TOKEN INSIDE OF TERM == " << tok << endl;

    bool status;
    status = SFactor(in, line);
    if(!status) return false;
    tok = Parser::GetNextToken(in, line);

    /*if(tok.GetToken() == RPAREN){
        Parser::PushBackToken(tok);
        return true;
    }*/
   /* if(tok.GetToken() == LPAREN){
        Parser::PushBackToken(tok);
        status = SFactor(in, line);
        if(!status){
            return false;
        }
        Parser::GetNextToken(in, line);
        //hasLParen = true;
    }else{
        //cout << "TOKEN BEING PUSH BACK IF NOT LPAREN :: " << tok << endl;
       // cout << tok << line << endl;
        Parser::PushBackToken(tok);
        status = SFactor(in, line);
        if(!status) return false;
        tok = Parser::GetNextToken(in, line);
    }*/

  //  cout << "Getting NEXT Tok in TERM " << tok << line << endl;

    if(tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    while(tok == MULT || tok == DIV){
        status = SFactor(in, line);
        if(!status){
            ParseError(line, "Missing operand after operator");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }/*
    if(tok.GetToken() == RPAREN && hasLParen){
        cout << "DONT PUSH BACK" << endl;
        return true;
    }*/
    //cout << "PUSHING BACK TOK :: " << tok << endl;
    Parser::PushBackToken(tok);
    return true;
}
bool SFactor(istream& in, int& line){
    LexItem tok = Parser::GetNextToken(in, line);
    //cout << "TOKen inside of FACTOR AFTER GETNEXT " << tok << endl;
    bool status;
    /*
    if(tok.GetToken() == RPAREN){
        Parser::PushBackToken(tok);
        return true;
    }
    if(tok.GetToken() == LPAREN){
        status = Factor(in, line, 0);
        if(!status) return false;
        Parser::GetNextToken(in, line);
    }*/
    if(tok.GetToken() == MINUS){
       // cout << "TOKEN IN SFACTOR " << tok << endl;
        return Factor(in, line, -1);
    }else if(tok.GetToken() == PLUS){
        return Factor(in, line, 1);
    }else{
        Parser::PushBackToken(tok);
     //   cout << "Going into factor" << endl;
        status = Factor(in, line, 0);
    }
   // cout << "Returning sFactor " << tok << endl;
  // if(!status) ParseError(line, "Using Undefined Variable");
    return status;
}

bool Var(istream& in, int& line){
    LexItem tok = Parser::GetNextToken(in, line);
 //   cout << "Token in VAR " << endl;
  //  cout << tok << endl;
    if(tok.GetToken() == IDENT){
        auto it = defVar.find(tok.GetLexeme());
        //auto it = SymTable.find(tok.GetLexeme())->second;
        if((it == defVar.end())){
            ParseError(line, "Undeclared Variable");
            return false;
        }
        it->second = true;
        return true;
    }else{
        ParseError(line, "Invalid Variable");
        return false;
    }

}
bool Prog(istream& in, int& line){
    LexItem tok;
    tok = Parser::GetNextToken(in, line);
    bool status = false;
    if(tok != PROGRAM){
        ParseError(line, "Missing PROGRAM.");
        return false;
    }else{
        tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() != IDENT){
            ParseError(line, "Missing Program Name.");
            return false;
        }
        bool noError = (tok == IDENT);
        tok = Parser::GetNextToken(in, line);
        bool hasSemiCol = (tok == SEMICOL);
        if(noError && hasSemiCol){
            bool validDeclBlock = DeclBlock(in, line);
            if(validDeclBlock){
                tok = Parser::GetNextToken(in, line);
                if(tok.GetToken() == BEGIN){
                   // cout << "Beginning" << endl;
                    bool validProgBody;
                    validProgBody = ProgBody(in, line);
                    //cout << "Valid ProgBody? == " << validProgBody << endl;
                   // cout << validProgBody << endl;
                    tok = Parser::GetNextToken(in,line);
                    if(tok.GetToken() == END && validProgBody){
                        status = true;
                    }else{
                        ParseError(line, "Incorrect Program Body.");
                        return false;
                    }
                }
            }else{
                ParseError(line, "Incorrect Declaration Section");
                return false;
            }
        }else{
            if(!noError){
                ParseError(line, "Missing Program Name.");
            }else{
                ParseError(line, "Missing semicolon");
            }
            return false;
        }
    }
    return status;
}
bool DeclBlock(istream& in, int& line){
    LexItem tok = Parser::GetNextToken(in, line);
    bool status;
    if(tok == VAR){
        bool validDeclStmt = DeclStmt(in, line);
        if(validDeclStmt){
            status = true;
        }else{
            ParseError(line, "Incorrect variable in Declaration Statement");
            ParseError(line, "Syntactic Error in Declaration Statement");
            status = false;
        }
    }else{
        ParseError(line, "Non-recognizable Declaration Block");
        status = false;
    }
    return status;
}
bool ProgBody(istream& in, int& line){
    LexItem tok;
        bool status = Stmt(in, line);
        tok = Parser::GetNextToken(in,line);
      //  cout << tok << endl;
        if(tok.GetToken() == END){
          //  cout << tok << line << endl;
         //   cout << "returning true" << endl;
            Parser::PushBackToken(tok);
            return true;
        }
        Parser::PushBackToken(tok);
        //cout << status << endl;
    if(!status){
        ParseError(line, "Syntactic Error in Program Body.");
        return false;
    }
        tok = Parser::GetNextToken(in, line);
        Token t = tok.GetToken();
    //  cout << tok << line << endl;
        if(t == SEMICOL){
            ProgBody(in, line);
        }else if(tok.GetToken() == END) {
            //cout << tok << endl;
            return true;
        }else{
           //cout << tok << endl;

            ParseError(line -1, "Missing Semicolon");
            ParseError(line -1, "Incorrect Program Body.");
            return false;
        }
    return true;

}
bool DeclStmt(istream& in, int& line){
    LexItem tok;
    tok = Parser::GetNextToken(in, line);
    //cout << tok << endl;
    bool status =true;
    if(tok.GetToken() == BEGIN){
        Parser::PushBackToken(tok);
        return true;
    }
    if(tok.GetToken() == IDENT){
        auto it = defVar.find(tok.GetLexeme());
        //auto it = SymTable.find(tok.GetLexeme())->second;
        if((it != defVar.end())){
           // cout << tok << endl;
            ParseError(line, "Variable redefinition");
           // ParseError(line, "Incorrect Variable in Declaration");
            status = false;
        }else{
            defVar.insert({tok.GetLexeme(), false}); //insert var into map
            SymTable.insert({tok.GetLexeme(), tok.GetToken()});
        }
    }
    if(!status){
        //ParseError(line, "Incorrect variable in Declaration Statement");
        return status;
    }
    tok = Parser::GetNextToken(in, line);
    //cout << tok << endl;
    if(tok.GetToken() == COMMA){
        status = DeclStmt(in, line);
       /* if(!status){
            cout << tok << endl;
            ParseError(line, "Incorrect variable in Declaration");
            return false;
        } */
    }else if(tok.GetToken() == COLON){
        tok = Parser::GetNextToken(in, line);
 //       cout << tok << endl;
        Token t = tok.GetToken();
        if(t == REAL || t == INTEGER || t == STRING){
            tok = Parser::GetNextToken(in, line);
            if(tok.GetToken() == SEMICOL){
                status = DeclStmt(in, line);
            }else{
                ParseError(line, "Missing Semicolon");
                return false;
            }
        }else{
            ParseError(line, "Incorrect Declaration Type");
            status = false;
        }
    }else{
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" <<tok.GetLexeme()<<")" << endl;
        return false;
    }
    /*
    if(!status){
        ParseError(line, "Incorrect Variable in Declaration");
    }*/
    return status;
}
/*
bool DeclStmt(istream& in, int& line){
    LexItem tok = Parser::GetNextToken(in, line);
    //this part of the code could be improved somehow since the first if statement can be redundant
    if(tok == IDENT){
        defVar.insert({tok.GetLexeme(), false});
        SymTable.insert({tok.GetLexeme(), tok.GetToken()});
    }else{
        ParseError(line, "Syntactic error in Declaration Section");
        return false;
    }
    while(tok == IDENT){ //this is for checking every line in the declstmt
        while(tok == IDENT){ //then this while statement goes through every var in stmt
            tok = Parser::GetNextToken(in, line);

            if(tok == COMMA){
                tok = Parser::GetNextToken(in, line);
                auto it = defVar.find(tok.GetLexeme());
                //auto it = SymTable.find(tok.GetLexeme())->second;
                if((it != defVar.end())){
                    ParseError(line, "Variable redefinition");
                    return false;
                }
                defVar.insert({tok.GetLexeme(), false}); //insert var into map
                continue;
            }else if(tok == COLON){
                break;
            }else if(tok == IDENT){
                ParseError(line, "Syntactic error in Declaration Section");
                return false;
            }
        }
        tok = Parser::GetNextToken(in, line);
        if(tok == INTEGER || tok == REAL || tok == STRING){
            tok = Parser::GetNextToken(in, line);
            if(tok == SEMICOL){
                tok = tok = Parser::GetNextToken(in, line);
                continue;
            }else{
                ParseError(line, "Syntactic error in Declaration Section");
                return false;
            }
        }else{
            ParseError(line, "Syntactic error in Declaration Section");
            return false;
        }
    }
    Parser::PushBackToken(tok); //push back the token that we pulled out after the semicol so that it can go to PROGBODY
    return true;
}
 */
bool Factor(istream& in, int& line, int sign){
    LexItem tok;
    tok = Parser::GetNextToken(in, line);
   // cout << "TOKEN IN FACTOR AFTER GET NEXT :: " << tok << endl;
    //LexItem tokOrig = tok;
    if(tok.GetToken() == LPAREN){
        bool status = Expr(in ,line);
        tok = Parser::GetNextToken(in,line);
    //    cout << "Getting next token in factor = " << tok << endl;
        if(tok.GetToken() == RPAREN && status){
           //cout << "L AND R: " << tokOrig << tok << endl;
            return true;
        }else{
            ParseError(line, "Missing ) after expression");
            return false;
        }

    }else{
        if(tok.GetToken() == SEMICOL){
            Parser::PushBackToken(tok);
            return true;
        }
    }
   // cout << "Tok Inside of Factor" << endl;
   // cout << tok << endl;
    Token t = tok.GetToken();
    if(t == ERR){
        ParseError(line, "Error in statement");
        return false;
    }
    if(t == IDENT){
        //cout << tok << endl;
        auto it = defVar.find(tok.GetLexeme());
        //auto it = SymTable.find(tok.GetLexeme())->second;
        if((it == defVar.end())){
            ParseError(line, "Using Undeclared Variable");
            return false;
        }
        return true;
    }
    if(t == ICONST || t == RCONST || t == SCONST){
      //  cout << "Returning true" << endl;
        return true;
    }else if(t == MULT || t == DIV){
       //cout << "TOK OPERATOR " << tok << endl;
       // ParseError(line, "Missing operand after operator");
        //Parser::PushBackToken(tok);
        return false;
    }else{
        ParseError(line, "Missing operand after operator");
        return false;
    }
}
bool IfStmt(istream& in, int& line){
    LexItem tok;
    bool status;
    tok = Parser::GetNextToken(in, line);
  //  cout << tok << endl;
    if(tok.GetToken() != LPAREN){
        ParseError(line, "Missing left parentheses");
        return false;
    }
        status = LogicExpr(in, line);
        if(!status){
            ParseError(line, "Missing Logic Expression in If-Stmt");
            return false;
        }
    tok = Parser::GetNextToken(in, line);
   // cout << "should be rparen" << endl;
  //  cout << tok << endl;
    if(tok.GetToken() != RPAREN){
        ParseError(line, "Missing right parentheses");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() == THEN){
        status = Stmt(in, line);
        if(!status){
            ParseError(line, "Missing Statement in If-Stmt Then-Part");
            return false;
        }
    }else{
        ParseError(line, "If-Stmt Syntax Error");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() == ELSE){
        status = Stmt(in, line);
    }else{
        Parser::PushBackToken(tok);
    }
    tok = Parser::GetNextToken(in, line);
    if(tok.GetToken() != SEMICOL){
        return false;
    }
    Parser::PushBackToken(tok);
    return status;
}
bool LogicExpr(istream& in, int& line){
    LexItem tok;
    bool status = Expr(in, line);
 //   cout << "CURRENT STATUS IN LOGICEXPR :: " << status << endl;
    if(!status){
        ParseError(line, "Invalid Logical Expression");
        return false;
    }
    tok = Parser::GetNextToken(in, line);
    Token t = tok.GetToken();
    if(t == EQUAL || t == GTHAN || t == LTHAN){
        tok = Parser::GetNextToken(in,line);
        t = tok.GetToken();
        if(t != IDENT && t != ICONST && t != RCONST && t != SCONST && t != MINUS && t != PLUS){
            ParseError(line, "Missing expression after relational operator");
            return false;
        }
        Parser::PushBackToken(tok);
        status = Expr(in, line);
    }else{
        ParseError(line, "Invalid Logical Symbol");
        return false;
    }
    if(!status){
        ParseError(line, "Invalid Logical Expression");
        return false;
    }
    return true;
}