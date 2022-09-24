#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <ostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <float.h>

using namespace std;

#include "utilities/utils.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"


string operator * (string a, unsigned int b) {
    string output = "";
    while (b--) {
        output += a;
    }
    return output;
}


void outputFuncSymblTbl(Object object, int i){
    for(auto key: (*object.function).context.sym_tbl) {
        if (key.second.name!=(*object.function).name.data){
            if (key.second.type==OBJ_FUNC){
                cout<<"  ";
                for (int x=0; x<i; x++){
                    cout<<"  ";
                }
                cout << key.second <<"\n";
                outputFuncSymblTbl(key.second, i+1);
            }
            else{
                cout<<"  ";
                for (int x=0; x<i; x++){
                    cout<<"  ";
                }
                cout << key.first<< " = "<< key.second <<"\n";
            }
        }
    } 
}

void outputClassSymblTbl(Object object, int i){
    for(auto key: (*object._class).context.sym_tbl) {
        if (key.second.name!=(*object._class).name.data){
            if (key.second.type==OBJ_CLASS){
                cout<<"  ";
                for (int x=0; x<i; x++){
                    cout<<"  ";
                }
                cout<< key.second <<"\n";
                outputClassSymblTbl(key.second, i+1);
            }
            else{
                cout<<"  ";
                for (int x=0; x<i; x++){
                    cout<<"  ";
                }
                cout << key.first<< " = "<< key.second <<"\n";
            }
        }
    } 
}

int main(int argc, char** argv) {
    string program="main.fpl";
    bool verbose=false;
    bool objdump=false;

    if (argc==2){
        if ((string)argv[1]==(string)"-h"){
            cout<<"FPL V1\n";
            cout<<"Eric Buehler 2022\n\n";
            cout<<"Standard run: fpl [PROGRAM NAME]\n";
            cout<<"Verbose run: fpl [PROGRAM NAME] -v\n";
            cout<<"Object dump run: fpl [PROGRAM NAME] -o\n";
            cout<<"Help: fpl -h\n";
        }
        program=argv[1];
    }

    if (argc==3){
        program=argv[1];
        if ((string)argv[2]==(string)"-v"){
            verbose=true;
        }
        if ((string)argv[2]==(string)"-o"){
            objdump=true;
        }
    }

    if (argc==4){
        program=argv[1];
        if ((string)argv[2]==(string)"-v" || (string)argv[3]==(string)"-v"){
            verbose=true;
        }
        if ((string)argv[2]==(string)"-o" || (string)argv[3]==(string)"-o"){
            objdump=true;
        }
    }

    string data=loadFile(program);

    vector<string> kwds;
    kwds.push_back("func");
    kwds.push_back("if");
    kwds.push_back("elif");
    kwds.push_back("else");
    kwds.push_back("return");
    kwds.push_back("while");
    kwds.push_back("break");
    kwds.push_back("continue");
    kwds.push_back("class");
    kwds.push_back("for");

    Lexer lexer(data,kwds);
    lexer.pos=Position(program);

    Position end=lexer.tokenize();

    int i=0;

    if (verbose){
        i=0;
        for (Token tok:lexer.tokens){
            cout << "Element " << i << " : ";
            cout<< tok <<"\n";
            i++;
        }
    }


    Parser parser(lexer.tokens);
    vector<Node> head=parser.parse();

    Interpreter interpreter(program,data,end);
    InitPrint(&interpreter);
    InitInput(&interpreter);
    InitLen(&interpreter);
    InitStr(&interpreter);
    InitNum(&interpreter);
    InitInt(&interpreter);
    InitFloat(&interpreter);
    InitList(&interpreter);
    InitRange(&interpreter);
    InitType(&interpreter);
    InitSuper(&interpreter);
    InitGetAttr(&interpreter);
    InitSetAttr(&interpreter);

    if (verbose){
        cout<<"-----------------------------\n";
    }

    Object* r=interpreter.run(head);

    if (verbose || objdump){
        cout<<"-----------------------------\n";
    }

    if (verbose || objdump){
        if (interpreter.context.back().sym_tbl.size()!=0){
            i=0;
            for(auto key: interpreter.context.back().sym_tbl) {
                cout << "Object " << i << endl;
                if (key.second.type==OBJ_FUNC){
                    cout<< "  "<< key.first<< ": " <<key.second <<"\n";
                    outputFuncSymblTbl(key.second, 1);
                }
                else if (key.second.type==OBJ_CLASS){
                    cout<< "  "<< key.first<< ": "<< key.second <<"\n";
                    outputClassSymblTbl(key.second, 1);
                }
                else{
                    cout<< "  "<< key.first<< " = "<< key.second <<"\n";
                }
                i++;
                cout<<"\n";
            } 
        }
    }

    return 0;
}   