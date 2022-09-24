class Parser{
    public:
        vector<Token> tokens;
        Token current_tok;
        int tok_idx;

        Parser(vector<Token> tokens_){
            this->tokens=tokens_;
            this->current_tok=this->tokens[0];
            this->tok_idx=0;
        }

        void advance(){
            tok_idx++;
            if (this->tok_idx >= this->tokens.size()){
                this->current_tok=Token();
            }
            this->current_tok=this->tokens[this->tok_idx];
        }

        Token get_next(){
            if (this->tok_idx+1 >= this->tokens.size()){
                Token t;
                return t;
            }
            return this->tokens[this->tok_idx+1];
        }

        Token get_last(){
            if (this->tok_idx-1 > 0){
                Token t;
                return t;
            }
            return this->tokens[this->tok_idx-1];
        }

        vector<Node> parse(){
            vector<Node> output = this->statements();
            return output;
        } 
        

        bool in_array(string value, string *array, int size){
            for (int i = 0; i < size; i++){
                if (value == array[i]){
                    return true;
                }
            }

            return false;
        }

        vector<Node> statements(){
            vector<Node> statements;
            statements.clear();

            while (this->current_tok.type==T_NEWLINE){
                this->advance();
            }

            if (this->current_tok.type==T_EOF || this->current_tok.type==T_RCURLY){
                return statements;
            }
            
            statements.push_back((*this->expr()));

            
            while (this->current_tok.type!=T_EOF){
                if (this->current_tok.type==T_RCURLY){
                    break;
                }            

                int count=0;
                bool more=true;
                while (this->current_tok.type==T_NEWLINE){
                    this->advance();
                    count++;
                }
                if (this->current_tok.type==T_EOF || this->current_tok.type==T_RCURLY){
                    break;
                }
            

                if (count==0){
                    more=false;
                }

                if (more==false){
                    break;
                }

                statements.push_back((*this->expr()));
            }

            return statements;

        }

        Node* atom(){
            //Var access
            if (this->current_tok.type==T_IDENTIFIER){
                VarAccessNode* varnode = new VarAccessNode(this->current_tok);
                Node* left = new Node(varnode, T_VarAccessNode);
                this->advance();
                while (this->current_tok.type==T_LSQUARE){
                    //Index
                    Token op=this->current_tok;
                    this->advance();
                    Node* val=this->expr();
                    BinOpNode* binopn = new BinOpNode((*left), op, (*val));
                    left = new Node(binopn, T_BinOpNode);
                    if (this->current_tok.type!=T_RSQUARE){
                        cout<<"Expected ]";
                        while (true);
                    }
                    this->advance();
                    if (this->current_tok.type==T_LPAREN){
                        Token op=this->current_tok;
                        this->advance();
                        
                        vector<Node> names;
                        names.clear();
                        
                        if (this->current_tok.type==T_RPAREN){
                            this->advance();
                        }
                        else{
                            //Start parsing args
                            names.push_back((*this->expr()));
                                
                            while (this->current_tok.type==T_COMMA){
                                this->advance();
                                names.push_back((*this->expr()));
                                if (this->current_tok.type==T_DOT){
                                    Token op=this->current_tok;
                                    this->advance();
                                    Node* dotaccess=this->expr();
                                    BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                                    Node* node=new Node(binnode, T_BinOpNode);
                                    names.pop_back();
                                    names.push_back((*node));
                                }
                            }
                            if (this->current_tok.type==T_DOT){
                                Token op=this->current_tok;
                                this->advance();
                                Node* dotaccess=this->expr();
                                BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                                Node* node=new Node(binnode, T_BinOpNode);
                                names.pop_back();
                                names.push_back((*node));
                            }
                            if (this->current_tok.type!=T_RPAREN){
                                cout<<"Expected )";
                                while (true);
                            }
                            this->advance();
                        }

                        CallNode* call = new CallNode(op, names);
                        Node* callaccess=new Node(call, T_CallNode);
                        
                        BinOpNode* binnode=new BinOpNode((*left),op,(*callaccess));
                        Node* n=new Node(binnode, T_BinOpNode);
                        return n;
                    }
                }
                if (this->current_tok.type==T_DOT){
                    Token op=this->current_tok;
                    this->advance();
                    Node* dotaccess=this->expr();
                    BinOpNode* binnode=new BinOpNode((*left),op,(*dotaccess));
                    left=new Node(binnode, T_BinOpNode);
                }
                if (this->current_tok.type==T_EQ){
                    this->advance();
                    Node* value=this->expr();
                    IndexAssignNode* varassign = new IndexAssignNode((*left), (*value));
                    Node* node = new Node(varassign, T_IndexAssignNode);
                    return node;
                }
                return left;
            }

            if (this->current_tok.type==T_LPAREN){
                this->advance();
                Node* node = new Node();
                node=this->expr();
                if (this->current_tok.type==T_RPAREN){
                    this->advance();
                    return node;
                }
                else{
                    cout<<"Expected )";
                    while (true);
                    (*node).type="";
                    return node;
                }
            }

            //INT and FLOAT
            if (this->current_tok.type==T_INT || this->current_tok.type==T_FLOAT){
                NumberNode* numnode = new NumberNode(this->current_tok);
                Node* node = new Node(numnode, T_NumberNode);
                this->advance();
                return node;
            }

            //String
            if (this->current_tok.type==T_STR){
                StringNode* numnode = new StringNode(this->current_tok);
                Node* node = new Node(numnode, T_StringNode);
                this->advance();
                return node;
            }

            //Func def
            if (this->current_tok.type==T_KWD && this->current_tok.data=="func"){
                Node* node = this->make_func_def();
                return node;
            }

            //if
            if (this->current_tok.type==T_KWD && this->current_tok.data=="if"){
                Node* node = this->make_if();
                return node;
            } 

            //return
            if (this->current_tok.type==T_KWD && this->current_tok.data=="return"){
                Node* node = this->make_return();
                return node;
            }

            //while
            if (this->current_tok.type==T_KWD && this->current_tok.data=="while"){
                Node* node = this->make_while();
                return node;
            }

            //COntinue and break
            if (this->current_tok.type==T_KWD && this->current_tok.data=="break"){
                Node* node = this->make_break();
                return node;
            }
            if (this->current_tok.type==T_KWD && this->current_tok.data=="continue"){
                Node* node = this->make_continue();
                return node;
            }

            //Class
            if (this->current_tok.type==T_KWD && this->current_tok.data=="class"){
                Node* node = this->make_class();
                return node;
            }

            //List
            if (this->current_tok.type==T_LSQUARE){
                Node* node = this->make_list();
                return node;
            }

            //Class
            if (this->current_tok.type==T_KWD && this->current_tok.data=="for"){
                Node* node = this->make_for();
                return node;
            }

            cout<<"FAILURE atom"<<this->current_tok;
            while (true);
        }
        
        Node* factor(){
            //Unary
            if (this->current_tok.type==T_PLUS || this->current_tok.type==T_MINUS){
                Token op=this->current_tok;
                this->advance();
                Node* fact=this->factor();
                UnaryOpNode* unary = new UnaryOpNode(op,(*fact));
                Node* node = new Node(unary, T_UnaryOpNode);
                return node;
            }       

            return this->power();
        }

        Node* power(){
            string op_vals[1]={T_POW};
            return this->bin_op_(&Parser::call, &Parser::factor,*this,op_vals,1);
        }

        Node* term(){
            string op_vals[2]={T_MUL,T_DIV};
            return this->bin_op(&Parser::factor,*this,op_vals,2);
        }

        Node* arith_expr(){
            string op_vals[6]={T_PLUS,T_MINUS,T_IADD,T_ISUB,T_IMUL,T_IDIV};
            return this->bin_op(&Parser::term,*this,op_vals,6);
        }

        Node* comp_expr(){
            if (this->current_tok.type==T_NOT){
                Token op=this->current_tok;
                this->advance();
                Node* node=this->expr();
                UnaryOpNode* unary=new UnaryOpNode(op, (*node));
                Node* n=new Node(unary, T_UnaryOpNode);
                return n;
            }

            string op_vals[6]={T_EE,T_NE,T_GT,T_GTE,T_LT,T_LTE};
            Node* node=this->bin_op(&Parser::arith_expr, *this, op_vals,6);
            return node;
        }

        Node* expr(){
            //Var assign - highest priority
            if (this->current_tok.type==T_IDENTIFIER){
                Token nxt=this->get_next();
                if (nxt.type.length()==0){
                    //Error
                    cout<<"ERORR expr";
                    while (true){};
                }
                if (nxt.type==T_EQ){
                    Token varname=this->current_tok;
                    this->advance();
                    this->advance();
                    Node* value=this->expr();
                    VarAssignNode* varassign = new VarAssignNode(varname, (*value));
                    Node* node = new Node(varassign, T_VarAssignNode);
                    return node; 

                }
            }

            string op_vals[2]={T_AND, T_OR};
            return this->bin_op(&Parser::comp_expr,*this,op_vals,2);
        }

        Node* call(){
            Node* atom_=this->atom();
            if (this->current_tok.type==T_LPAREN){
                this->advance();

                vector<Node> names;
                names.clear();
                
                if (this->current_tok.type==T_RPAREN){
                    this->advance();
                }
                else{
                    //Start parsing args
                    names.push_back((*this->expr()));
                        
                    while (this->current_tok.type==T_COMMA){
                        this->advance();
                        names.push_back((*this->expr()));
                        if (this->current_tok.type==T_DOT){
                            Token op=this->current_tok;
                            this->advance();
                            Node* dotaccess=this->expr();
                            BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                            Node* node=new Node(binnode, T_BinOpNode);
                            names.pop_back();
                            names.push_back((*node));
                        }
                    }
                    if (this->current_tok.type==T_DOT){
                        Token op=this->current_tok;
                        this->advance();
                        Node* dotaccess=this->expr();
                        BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                        Node* node=new Node(binnode, T_BinOpNode);
                        names.pop_back();
                        names.push_back((*node));
                    }
                    if (this->current_tok.type!=T_RPAREN){
                        cout<<"Expected )";
                        while (true);
                    }
                    this->advance();
                }

                CallNode* call = new CallNode((*(*atom_).varaccessnode).name, names);
                Node* node=new Node(call, T_CallNode);

                if (this->current_tok.type==T_DOT){
                    Token op=this->current_tok;
                    this->advance();
                    Node* dotaccess=this->expr();
                    BinOpNode* binnode=new BinOpNode((*node),op,(*dotaccess));
                    Node* node=new Node(binnode, T_BinOpNode);
                    return node;
                }

                if (this->current_tok.type==T_LPAREN){
                    Token op=this->current_tok;
                    this->advance();
                    
                    vector<Node> names;
                    names.clear();
                    
                    if (this->current_tok.type==T_RPAREN){
                        this->advance();
                    }
                    else{
                        //Start parsing args
                        names.push_back((*this->expr()));
                            
                        while (this->current_tok.type==T_COMMA){
                            this->advance();
                            names.push_back((*this->expr()));
                            if (this->current_tok.type==T_DOT){
                                Token op=this->current_tok;
                                this->advance();
                                Node* dotaccess=this->expr();
                                BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                                Node* node=new Node(binnode, T_BinOpNode);
                                names.pop_back();
                                names.push_back((*node));
                            }
                        }
                        if (this->current_tok.type==T_DOT){
                            Token op=this->current_tok;
                            this->advance();
                            Node* dotaccess=this->expr();
                            BinOpNode* binnode=new BinOpNode(names.back(),op,(*dotaccess));
                            Node* node=new Node(binnode, T_BinOpNode);
                            names.pop_back();
                            names.push_back((*node));
                        }
                        if (this->current_tok.type!=T_RPAREN){
                            cout<<"Expected )";
                            while (true);
                        }
                        this->advance();
                    }

                    CallNode* call = new CallNode(op, names);
                    Node* callaccess=new Node(call, T_CallNode);
                    
                    BinOpNode* binnode=new BinOpNode((*node),op,(*callaccess));
                    Node* n=new Node(binnode, T_BinOpNode);
                    return n;
                }

                return node;

            }
            return atom_;
        }

        Node* bin_op(Node* (Parser::*function)(), Parser& obj, string *op_vals, int size){
            Node* left = new Node();
            (*left).type="";
            Node* right = new Node();
            Token* op_tok = new Token();

            left=(obj.*function)();
            //return left;

            while (this->current_tok.type!=T_EOF && in_array(this->current_tok.type,op_vals, size)){
                (*op_tok)=this->current_tok;
                this->advance();
                right=(obj.*function)();
                BinOpNode* op=new BinOpNode((*left),(*op_tok),(*right));
                (*left).binopnode = op;
                (*left).type=T_BinOpNode;
                //this->advance(); //func should advance
            }

            return left;
        }

        Node* bin_op_(Node* (Parser::*function)(), Node* (Parser::*functionb)(), Parser& obj, string *op_vals, int size){
            Node* left = new Node();
            (*left).type="";
            Node* right = new Node();
            Token* op_tok = new Token();

            left=(obj.*function)();

            while (this->current_tok.type!=T_EOF && in_array(this->current_tok.type,op_vals, size)){
                (*op_tok)=this->current_tok;
                this->advance();
                right=(obj.*functionb)();
                BinOpNode* op=new BinOpNode((*left),(*op_tok),(*right));
                (*left).binopnode = op;
                (*left).type=T_BinOpNode;
                //this->advance(); //func should advance
            }

            return left;
        }

        Node* make_func_def(){
            this->advance();
            Token name;
            if (this->current_tok.type==T_IDENTIFIER){
                name=this->current_tok;
                this->advance();
                if (this->current_tok.type!=T_LPAREN){
                    cout<<"Expected (";
                    while (true);
                }
            }
            else{
                this->advance();
                if (this->current_tok.type!=T_LPAREN){
                    cout<<"Expected (";
                    while (true);
                }
            }

            this->advance();

            vector<Token> names;
            vector<Node> values;
            names.clear();
            values.clear();

            if (this->current_tok.type==T_IDENTIFIER){
                Token tok=this->current_tok;
                Node placehold;
                placehold.type=T_EOF;

                this->advance();
                if (this->current_tok.type==T_EQ){
                    //Default
                    this->advance();
                    names.push_back(tok);
                    values.push_back((*this->expr()));
                }
                else{
                    names.push_back(tok);
                    values.push_back(placehold);
                }
                while (this->current_tok.type==T_COMMA){
                    this->advance();
                    if (this->current_tok.type!=T_IDENTIFIER){
                        cout<<"Expected indentifier in function args";
                        while (true);
                    }

                    tok=this->current_tok;
                    this->advance();
                    if (this->current_tok.type==T_EQ){
                        //Default
                        this->advance();
                        names.push_back(tok);
                        values.push_back((*this->expr()));
                    }
                    else{
                        names.push_back(tok);
                        values.push_back(placehold);
                    }
                }
                if (this->current_tok.type!=T_RPAREN){
                    cout<<"Expected )";
                    while (true);
                }
            }
            else{
                if (this->current_tok.type!=T_RPAREN){
                    cout<<"Expected )";
                    while (true);
                }
            }

            this->advance();

            if (this->current_tok.type!=T_LCURLY){
                cout<<"Expected {";
                while (true);
            }

            this->advance();

            vector<Node> body=this->statements();  
            while (this->current_tok.type!=T_RCURLY){
                vector<Node> body_=this->statements();
                for (Node n:body_){
                    body.push_back(n);
                }
            }
            if (this->current_tok.type!=T_RCURLY){
                cout<<"Expected }";
                while (true);
            }
     
            this->advance();

            FuncDefNode* node=new FuncDefNode(name,names, values,body);
            Node* n=new Node(node,T_FuncDefNode);
            return n;
        }

        Node* make_if(){
            this->advance();
            if (this->current_tok.type!=T_LPAREN){
                cout<<"Expected (";
                while (true);
            }
            
            Node statement=(*this->expr());
            
            if (this->current_tok.type!=T_LCURLY){
                cout<<"Expected {";
                while (true);
            }
            
            this->advance();
            vector<Node> body=this->statements();
            while (this->current_tok.type!=T_RCURLY){
                vector<Node> body_=this->statements();
                for (Node n:body_){
                    body.push_back(n);
                }
            }
            if (this->current_tok.type!=T_RCURLY){
                cout<<"Expected }";
                while (true);
            }

            this->advance();

            IfNode* ifn=new IfNode(statement,body);

            while (this->current_tok.type==T_NEWLINE){
                this->advance();
            }
            if (this->current_tok.type==T_KWD && this->current_tok.data=="elif"){
                //Elif
                while (this->current_tok.type==T_KWD && this->current_tok.data=="elif"){                    
                    this->advance();
                    if (this->current_tok.type!=T_LPAREN){
                        cout<<"Expected (";
                        while (true);
                    }
                    
                    Node statement=(*this->expr());
                    
                    if (this->current_tok.type!=T_LCURLY){
                        cout<<"Expected {";
                        while (true);
                    }

                    this->advance();

                    vector<Node> body=this->statements();
                    while (this->current_tok.type!=T_RCURLY){
                        vector<Node> body_=this->statements();
                        for (Node n:body_){
                            body.push_back(n);
                        }
                    }
                    if (this->current_tok.type!=T_RCURLY){
                        cout<<"Expected }";
                        while (true);
                    }

                    this->advance();

                    ElifNode enode=(*new ElifNode(statement,body));
                    (*ifn).elif.push_back(enode);

                    while (this->current_tok.type==T_NEWLINE){
                        this->advance();
                    }

                }
            }

            while (this->current_tok.type==T_NEWLINE){
                this->advance();
            }
            
            if (this->current_tok.type==T_KWD && this->current_tok.data=="else"){
                this->advance();

                if (this->current_tok.type!=T_LCURLY){
                    cout<<"Expected {";
                    while (true);
                }

                this->advance();


                vector<Node> body=this->statements();
                while (this->current_tok.type!=T_RCURLY){
                    vector<Node> body_=this->statements();
                    for (Node n:body_){
                        body.push_back(n);
                    }
                }
                if (this->current_tok.type!=T_RCURLY){
                    cout<<"Expected }";
                    while (true);
                }

                this->advance();

                ElseNode* enode=new ElseNode(body);
                (*ifn).else_=enode;
            }
            

            Node* node=new Node(ifn, T_IfNode);
            return node;
        }

        Node* make_return(){
            this->advance();
            Node expression=(*this->expr());
            ReturnNode* ret=new ReturnNode(expression);
            Node* node=new Node(ret,T_ReturnNode);
            return node;
        }

        Node* make_while(){
            this->advance();
            if (this->current_tok.type!=T_LPAREN){
                cout<<"Expected (";
                while (true);
            }
            
            Node statement=(*this->expr());
            
            if (this->current_tok.type!=T_LCURLY){
                cout<<"Expected {";
                while (true);
            }
            
            this->advance();

            vector<Node> body=this->statements();
            while (this->current_tok.type!=T_RCURLY){
                vector<Node> body_=this->statements();
                for (Node n:body_){
                    body.push_back(n);
                }
            }
            if (this->current_tok.type!=T_RCURLY){
                cout<<"Expected }";
                while (true);
            }

            this->advance();

            WhileNode* wnode=new WhileNode(statement,body);
            Node* node=new Node(wnode,T_WhileNode);
            return node;
        }

        Node* make_break(){
            this->advance();
            BreakNode* brk=new BreakNode();
            Node* node=new Node(brk,T_BreakNode);
            while (this->current_tok.type==T_NEWLINE){
                this->advance();
            }
            return node;
        }

        Node* make_continue(){
            this->advance();
            ContinueNode* cont=new ContinueNode();
            Node* node=new Node(cont,T_ContinueNode);
            while (this->current_tok.type==T_NEWLINE){
                this->advance();
            }
            return node;
        }

        Node* make_class(){
            this->advance();
            Token name;
            vector<VarAccessNode> inherits;
            inherits.clear();

            if (this->current_tok.type==T_IDENTIFIER){
                name=this->current_tok;
                this->advance();
            }
            else{
                name.type=T_IDENTIFIER;
                name.data="";
            }

            if (this->current_tok.type==T_LPAREN){
                this->advance();
                if (this->current_tok.type!=T_RPAREN){
                    VarAccessNode n;
                    if (this->current_tok.type==T_IDENTIFIER){
                        n=VarAccessNode(this->current_tok);
                        inherits.push_back(n);
                        this->advance();
                        while (this->current_tok.type==T_COMMA){
                            this->advance();
                            n=VarAccessNode(this->current_tok);
                            inherits.push_back(n);
                            this->advance();
                        }
                    }
                }
                if (this->current_tok.type==T_RPAREN){
                    this->advance();
                }
                else{
                    cout<<"Expected )";
                    while (true);
                }
        
            }
            
            
            if (this->current_tok.type!=T_LCURLY){
                cout<<"Expected {";
                while (true);
            }

            this->advance();
            vector<Node> out=this->statements();
            while (this->current_tok.type!=T_RCURLY){
                vector<Node> body_=this->statements();
                for (Node n:body_){
                    out.push_back(n);
                }
            }
            if (this->current_tok.type!=T_RCURLY){
                cout<<"Expected }";
                while (true);
            }
            this->advance();
            
            ClassDefNode* brk=new ClassDefNode(name, inherits, out);
            Node* node=new Node(brk,T_ClassDefNode);
            return node;
        }

        Node* make_list(){
            this->advance();
            vector<Node> items;
            items.clear();
            if (this->current_tok.type!=T_LSQUARE){
                if (this->current_tok.type!=T_RSQUARE){
                    Node n=(*this->expr());
                    items.push_back(n);
                    while (this->current_tok.type==T_COMMA){
                        this->advance();
                        if (this->current_tok.type==T_RSQUARE){
                            break;
                        }
                        n=(*this->expr());
                        items.push_back(n);
                    }
                }
            }
            if (this->current_tok.type!=T_RSQUARE){
                cout<<"Expected ]";
                while (true);
            }

            this->advance();

            ListNode* list = new ListNode(items);
            Node* node=new Node(list, T_ListNode);
            return node;
        }

        Node* make_for(){
            this->advance();
            if (this->current_tok.type!=T_LPAREN){
                cout<<"Expected (";
                while (true);
            }
            this->advance();
            if (this->current_tok.type!=T_IDENTIFIER){
                cout<<"Expected identifier for variable name";
                while (true);
            }
            Token varname=this->current_tok;
            this->advance();
            if (this->current_tok.type!=T_IN){
                cout<<"Expected 'in'";
                while (true);
            }
            this->advance();
            Node iterator=(*this->expr());
            if (this->current_tok.type!=T_RPAREN){
                cout<<"Expected )";
                while (true);
            }
            this->advance();
            if (this->current_tok.type!=T_LCURLY){
                cout<<"Expected {";
                while (true);
            }
            this->advance();
            vector<Node> statements=this->statements();
            if (this->current_tok.type!=T_RCURLY){
                cout<<"Expected }";
                while (true);
            }
            this->advance();

            ForNode* f=new ForNode(varname, iterator, statements);
            Node* n=new Node(f, T_ForNode);
            return n;
        }

};