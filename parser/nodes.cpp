//#include "node.cpp"

const string T_NumberNode="NumberNode";
const string T_BinOpNode="BinOpNode";
const string T_VarAssignNode="VarAssignNode";
const string T_UnaryOpNode="UnaryOpNode";
const string T_StringNode="StringNode";
const string T_VarAccessNode="VarAccessNode";
const string T_FuncDefNode="FuncDefNode";
const string T_CallNode="CallNode";
const string T_IfNode="IfNode";
const string T_ReturnNode="ReturnNode";
const string T_WhileNode="WhileNode";
const string T_BreakNode="BreakNode";
const string T_ContinueNode="ContinueNode";
const string T_ClassDefNode="ClassDefNode";
const string T_ListNode="ListNode";
const string T_IndexAssignNode="IndexAssignNode";
const string T_ForNode="ForNode";


class NumberNode;
class BinOpNode;
class VarAssignNode;
class UnaryOpNode;
class StringNode;
class VarAccessNode;
class FuncDefNode;
class CallNode;
class IfNode;
class ReturnNode;
class WhileNode;
class BreakNode;
class ContinueNode;
class ClassDefNode;
class ListNode;
class IndexAssignNode;
class ForNode;

class Node{
    public:
        NumberNode* numnode;
        BinOpNode* binopnode;
        VarAssignNode* varassignnode;
        UnaryOpNode* unaryopnode;
        StringNode* stringnode;
        VarAccessNode* varaccessnode;
        FuncDefNode* funcdefnode;
        CallNode* callnode;
        IfNode* ifnode;
        ReturnNode* returnnode;
        WhileNode* whilenode;
        BreakNode* breaknode;
        ContinueNode* continuenode;
        ClassDefNode* classdefnode;
        ListNode* listnode;
        IndexAssignNode* indexassignnode;
        ForNode* fornode;

        string type="";
        Node(){}
        Node(NumberNode* num, string type_){
            numnode=num;
            type=type_;
        }

        Node(BinOpNode* bin, string type_){
            binopnode=bin;
            type=type_;
        }

        Node(VarAssignNode* var, string type_){
            varassignnode=var;
            type=type_;
        }

        Node(UnaryOpNode* unary, string type_){
            unaryopnode=unary;
            type=type_;
        }

        Node(StringNode* str, string type_){
            stringnode=str;
            type=type_;
        }

        Node(VarAccessNode* var, string type_){
            varaccessnode=var;
            type=type_;
        }

        Node(FuncDefNode* var, string type_){
            funcdefnode=var;
            type=type_;
        }

        Node(CallNode* var, string type_){
            callnode=var;
            type=type_;
        }

        Node(IfNode* ifn, string type_){
            ifnode=ifn;
            type=type_;
        }

        Node(ReturnNode* ret, string type_){
            returnnode=ret;
            type=type_;
        }

        Node(WhileNode* wh, string type_){
            whilenode=wh;
            type=type_;
        }

        Node(BreakNode* brk, string type_){
            breaknode=brk;
            type=type_;
        }

        Node(ContinueNode* cont, string type_){
            continuenode=cont;
            type=type_;
        }

        Node(ClassDefNode* cl, string type_){
            classdefnode=cl;
            type=type_;
        }

        Node(ListNode* list, string type_){
            listnode=list;
            type=type_;
        }

        Node(IndexAssignNode* indx, string type_){
            indexassignnode=indx;
            type=type_;
        }

        Node(ForNode* f, string type_){
            fornode=f;
            type=type_;
        }
        

};



class NumberNode {
    public:
        Position start;
        Position end;
        Token token;
        NumberNode(){}
        NumberNode(Token tok){
            this->token=tok;
            this->start=tok.start;
            this->end=tok.end;
        }
};

class BinOpNode{
    public:
        Node left;
        Node right;
        Token opr;
        BinOpNode(){}
        BinOpNode(Node lft,Token op,Node rght){
            this->left=lft;
            this->right=rght;
            this->opr=op;
        }
};

class UnaryOpNode{
    public:
        Node right;
        Token opr;
        UnaryOpNode(){}
        UnaryOpNode(Token op,Node rght){
            this->right=rght;
            this->opr=op;
        }
};

class VarAssignNode{
    public:
        Token name;
        Node value;
        VarAssignNode(){}
        VarAssignNode(Token nm,Node val){
            this->name=nm;
            this->value=val;
        }
};

class StringNode {
    public:
        Position start;
        Position end;
        Token token;
        StringNode(){}
        StringNode(Token tok){
            this->token=tok;
            this->start=tok.start;
            this->end=tok.end;
        }
};


class VarAccessNode{
    public:
        Token name;
        VarAccessNode(){}
        VarAccessNode(Token nm){
            this->name=nm;
        }
};

class FuncDefNode{
    public:
        Token name;
        vector<Token> names;
        vector<Node> values;
        vector<Node> lines;
        FuncDefNode(){}
        FuncDefNode(Token n, vector<Token> names_, vector<Node> vals, vector<Node> l){
            this->name=n;
            this->names=names_;
            this->values=vals;
            this->lines=l;
        }
};

class CallNode{
    public:
    Token name;
    vector<Node> names;
    CallNode(){}
    CallNode(Token n, vector<Node> name_){
        name=n;
        names=name_;
    }
};


class ElifNode;
class ElseNode;
class IfNode{
    public:
        Node statement;
        vector<ElifNode> elif;
        ElseNode* else_=NULL;
        vector<Node> lines;
        
        IfNode(){
            elif.clear();
        }
        IfNode(Node state, vector<Node> l){
            this->statement=state;
            this->lines=l;
            elif.clear();
        }
};

class ElifNode{
    public:
        Node statement;
        vector<Node> lines;
        ElifNode(){}
        ElifNode(Node state, vector<Node> l){
            statement=state;
            lines=l;
        }
};

class ElseNode{
    public:
        vector<Node> lines;
        ElseNode(){}
        ElseNode(vector<Node> l){
            this->lines=l;
        }
};


class ReturnNode{
    public:
        Node value;
        ReturnNode(){}
        ReturnNode(Node val){
            this->value=val;
        }
};

class WhileNode{
    public:
        Node statement;
        vector<Node> lines;
        WhileNode(){}
        WhileNode(Node state, vector<Node> l){
            statement=state;
            lines=l;
        }
};

class BreakNode{
    public:
        BreakNode(){}
};

class ContinueNode{
    public:
        ContinueNode(){}
};

class ClassDefNode{
    public:
        Token name;
        vector<VarAccessNode> inherits;
        vector<Node> funcs;
        ClassDefNode(){}
        ClassDefNode(Token n, vector<VarAccessNode> inher, vector<Node> func){
            this->name=n;
            this->inherits=inher;
            this->funcs=func;
        }
};

class ListNode{
    public:
        vector<Node> items;
        ListNode(){}
        ListNode(vector<Node> itm){
            items=itm;
        }
};

class IndexAssignNode{
    public:
        Node name;
        Node value;
        IndexAssignNode(){}
        IndexAssignNode(Node nm,Node val){
            this->name=nm;
            this->value=val;
        }
};

class ForNode{
    public:
        Token varname;
        Node iterator;
        vector<Node> lines;
        ForNode(){}
        ForNode(Token var, Node it, vector<Node> l){
            varname=var;
            iterator=it;
            lines=l;
        }
};
