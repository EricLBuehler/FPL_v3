class Interpreter{
    public:
        vector<Context> context;
        vector<string> builtins;
        unordered_map<string, Object> builtin_funcs;
        int looplevel=0;

        Interpreter(string name, string data, Position end_){
            Position* start=new Position(name, 0, 0, 0);
            Position* end=new Position(name, end_.index, end_.col, end_.line);
            Context* main=new Context("main",(*start), (*end));
            this->context.push_back((*main));
            this->builtins.clear();
            this->builtin_funcs.clear();
        }

        

        Object* FPLPrint(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                retval=new Object(args["obj"].function,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_CLASS){
                retval=new Object(args["obj"]._class,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_TYPE){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }

            cout<<&args["obj"]<<&args["end"];
            return retval;
        }

        Object* FPLInput(unordered_map<string,Object> args){
            Object* retval=new Object;
            string input="";
            cout<<&args["prompt"];
            getline(cin, input);
            String* s=new String(input);
            retval=new Object(s,OBJ_STR,input);
            return retval;
        }

        Object* FPLLen(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                cout<<"Invalid object type for length";
                while (true);
            }
            else if (args["obj"].type==OBJ_STR){
                Object* val=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
                retval=(*(*val).str).length();
            }
            else if (args["obj"].type==OBJ_FUNC){
                cout<<"Invalid object type for length";
                while (true);
            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__len__";
                return call_class_special_noargs_(name, &args["obj"]);
            }
            else if (args["obj"].type==OBJ_LIST){
                Object* val=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
                retval=(*(*val).list).length();
            }
            
            return retval;
        }

        Object* FPLStr(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                retval=new Object(args["obj"].function,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__str__";
                Object* val=call_class_special_noargs_(name, &args["obj"]);
                return val;
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_TYPE){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            
            std::stringstream buffer;
            buffer << retval;
            String* s=new String(buffer.str());
            Object* res=new Object(s, OBJ_STR, (*s).value);
            return res;
        }

        Object* FPLNum(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                cout<<"Cannot convert function to int";
                while (true);

            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__num__";
                return call_class_special_noargs_(name, &args["obj"]);
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
            }
            
            std::stringstream buffer;
            buffer << retval;
            string str=buffer.str();
            Number* n=new Number(str);
            Object* res=new Object(n, OBJ_NUM, (*n).value.ToString());
            return res;
        }

        Object* FPLInt(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                cout<<"Cannot convert function to int";
                while (true);

            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__int__";
                return call_class_special_noargs_(name, &args["obj"]);
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
            }
            
            std::stringstream buffer;
            buffer << retval;
            string str=buffer.str();
            Number* n=new Number(str);
            (*n).value=BigFloat((*n).value.ToString().substr(0, (*n).value.Ints()));
            Object* res=new Object(n, OBJ_NUM, (*n).value.ToString());
            return res;
        }

        Object* FPLFloat(unordered_map<string,Object> args){
            Object* retval=new Object;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                cout<<"Cannot convert function to int";
                while (true);

            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__float__";
                return call_class_special_noargs_(name, &args["obj"]);
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
            }
            
            std::stringstream buffer;
            buffer << retval;
            string str=buffer.str();
            Number* n=new Number(str);
            string s=(*n).value.ToString();
            if (count(s.begin(), s.end(), '.')==0){
                (*n).value=BigFloat((*n).value.ToString()+".0");
            }
            Object* res=new Object(n, OBJ_NUM, (*n).value.ToString());
            return res;
        }

        Object* FPLList(unordered_map<string,Object> args){
            Object* retval=new Object;
            bool none=false;
            if (args["obj"].type==OBJ_NUM){
                retval=new Object(args["obj"].number,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_STR){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_FUNC){
                retval=new Object(args["obj"].function,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_CLASS){
                string name=args["obj"].name+".__list__";
                return call_class_special_noargs_(name, &args["obj"]);
            }
            else if (args["obj"].type==OBJ_LIST){
                retval=new Object(args["obj"].list,args["obj"].type,args["obj"].name);
                return retval;
            }
            else if (args["obj"].type==OBJ_TYPE){
                retval=new Object(args["obj"].str,args["obj"].type,args["obj"].name);
            }
            else if (args["obj"].type==OBJ_NONE){
                none=true;
            }
            
            vector<Object> lst;
            lst.clear();
            List* l;
            if (!none){
                lst.push_back((*retval));
            }
            l=new List(lst);
            Object* res=new Object(l, OBJ_LIST, "LIST");
            return res;
        }

        Object* FPLRange(unordered_map<string,Object> args){
            if (args["start"].type!=OBJ_NUM || args["end"].type!=OBJ_NUM){
                cout<<"Cannot have non-number for range parameter";
                while(true);
            }

            BigFloat start=(*args["start"].number).value;
            BigFloat end=(*args["end"].number).value;

            if (end-start<0){
                cout<<"Start must be greater than end for range";
                while (true);
            }

            vector<Object> l;
            l.clear();
            
            try{
                Number* n;
                Object* o;
                for (BigFloat i=start; i<end; i++){
                    n=new Number(i);
                    cout<<sizeof(BigFloat)<<" ";
                    o=new Object(n,OBJ_NUM,(*n).value.ToString());
                    cout<<sizeof((*o))<<"   ";
                    l.push_back((*o));
                }
                

                List* list=new List(l);   
                
                
                Object* retval=new Object(list, OBJ_LIST, "LIST");
                return retval;
            }
            catch (std::bad_alloc const&) {
                cout<<"Memory error.";
                while (true);
            }
        }

        Object* FPLType(unordered_map<string,Object> args){
            String* s=new String(args["obj"].type);
            Object* res=new Object(s, OBJ_TYPE, (*s).value);
            return res;
        }

        Object* FPLSuper(unordered_map<string,Object> args){
            if (this->context.back().sym_tbl.find("this")!=this->context.back().sym_tbl.end()){
                Object parent=this->context.back().sym_tbl["this"];
                
                if ((*parent._class).mro.size()>1){
                    return &(*parent._class).mro[1];
                }

                Object* retval=new Object( OBJ_NONE);
                return retval;
            }
            Object* retval=new Object( OBJ_NONE);
            return retval;
        }

        Object* FPLGetAttr(unordered_map<string,Object> args){
            if (args["obj"].type!=OBJ_CLASS){
                cout<<"Object must be a class.";
                while (true);
            }
            if (args["name"].type!=OBJ_STR){
                cout<<"Name must be a string.";
                while (true);
            }
            
            vector<string> names=this->split(args["name"].str->value,".");
            for (string name:names){
                if (args["obj"]._class->context.sym_tbl.find(name)!=args["obj"]._class->context.sym_tbl.end()){
                    return &args["obj"]._class->context.sym_tbl[name];
                }
                else{
                    return &args["default"];
                }
            }
        }

        Object* FPLSetAttr(unordered_map<string,Object> args){
            if (args["obj"].type!=OBJ_CLASS){
                cout<<"Object must be a class.";
                while (true);
            }
            if (args["name"].type!=OBJ_STR){
                cout<<"Name must be a string.";
                while (true);
            }
            
            vector<string> names=this->split(args["obj"].name+"."+args["name"].str->value,".");
            Context* current=&this->context.back();
            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }

            (*current).sym_tbl[names.back()]=args["value"];

            Object* retval=new Object( OBJ_NONE);
            return retval;
        }

        Object* run(vector<Node> heads){
            Object* obj=new Object();
            for (Node node:heads){
                obj=this->visit(node);
                if ((*obj).isret==true){
                    if (this->context.size()==1){
                        cout<<"Return outside function";
                        while (true);
                    }
                    return obj;
                }
                if ((*obj).isbreak==true){
                    if (this->looplevel==0){
                        cout<<"Break outside loop";
                        while (true);
                    }
                    return obj;
                }
                if ((*obj).iscont==true){
                    if (this->looplevel==0){
                        cout<<"Continue outside loop";
                        while (true);
                    }
                    return obj;
                }
            }
            return obj;
        }

        Object* visit(Node n){
            if (n.type==T_BinOpNode){
                Object* res=this->visit_binop(n);
                return res;
            }

            if (n.type==T_NumberNode){
                Object* res=this->visit_numnode(n);
                return res;
            }

            if (n.type==T_VarAssignNode){
                Object* res=this->visit_varassignemnt(n);
                return res;
            }

            if (n.type==T_UnaryOpNode){
                Object* res=this->visit_unary(n);
                return res;
            }

            if (n.type==T_StringNode){
                Object* res=this->visit_string(n);
                return res;
            }

            if (n.type==T_VarAccessNode){
                Object* res=this->visit_varaccess(n);
                return res;
            }

            if (n.type==T_FuncDefNode){
                Object* res=this->visit_funcdef(n);
                return res;
            }

            if (n.type==T_CallNode){
                Object* res=this->visit_call(n);
                return res;
            }

            if (n.type==T_IfNode){
                Object* res=this->visit_if(n);
                return res;
            }

            if (n.type==T_ReturnNode){
                Object* res=this->visit_return(n);
                return res;
            }

            if (n.type==T_WhileNode){
                Object* res=this->visit_while(n);
                return res;
            }

            if (n.type==T_BreakNode){
                Object* res=this->visit_break(n);
                return res;
            }

            if (n.type==T_ContinueNode){
                Object* res=this->visit_continue(n);
                return res;
            }

            if (n.type==T_ClassDefNode){
                Object* res=this->visit_classdef(n);
                return res;
            }

            if (n.type==T_ListNode){
                Object* res=this->visit_list(n);
                return res;
            }

            if (n.type==T_IndexAssignNode){
                Object* res=this->visit_varindexassignment(n);
                return res;
            }

            if (n.type==T_ForNode){
                Object* res=this->visit_for(n);
                return res;
            }

            cout<<"ERROR visit node type is "<< n.type <<" and not found";
            while(true);
        }

        Object* visit_numnode(Node n){
            Number* nd=new Number((*n.numnode).token.data);
            Object* r=new Object(nd,OBJ_NUM,(*nd).value.ToString());
            return r;
        }

        Object* visit_list(Node n){
            ListNode nd=(*n.listnode);
            vector<Object> items;
            for (Node n:nd.items){
                items.push_back((*this->visit(n)));
            }
            List* list=new List(items);
            Object* r=new Object(list,OBJ_LIST,"LIST");
            return r;
        }

        Object* call_class_special_(string name, Object* right, Object* left){
            bool found;
            Object* object=new Object;
            Object* object_;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&(*(*left)._class).context;

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            object_=&(*current).sym_tbl[str];
                            has_obj=true;

                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
    
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }

                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else{
                cout<<"Callable "<<name<<" not found";
                while (true);
            }
            if ((*object).type==OBJ_FUNC){
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                for(auto &key: (*(*object).function).args) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }
                
                (*(*object).function).context.sym_tbl[names[0]]=(*right);

                this->context.push_back((*(*object).function).context);
                this->context.back().sym_tbl["this"]=(*left);
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                (*(*left)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                this->context.pop_back();

                return returnval;
            }
        }

        Object* call_class_special(string name, Object* right){
            bool found;
            Object* object=new Object;
            Object* object_;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&this->context.back();

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            object_=&(*current).sym_tbl[str];
                            has_obj=true;

                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
    
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }

                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else{
                cout<<"Callable "<<name<<" not found";
                while (true);
            }

            if ((*object).type==OBJ_FUNC){
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                for(auto &key: (*(*object).function).args) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                cout<<names[0];
                
                (*(*object).function).context.sym_tbl[names[0]]=(*right);

                this->context.push_back((*(*object).function).context);
                if (has_obj){
                    this->context.back().sym_tbl["this"]=(*object_);
                }
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                if (has_obj){
                    (*(*object_)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                }
                this->context.pop_back();

                return returnval;
            }
        }

        Object* call_class_special_noargs_(string name, Object* left){
            bool found;
            Object* object=new Object;
            Object* object_;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&(*(*left)._class).context;

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            object_=&(*current).sym_tbl[str];
                            has_obj=true;

                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
    
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else{
                cout<<"Callable "<<name<<" not found";
                while (true);
            }

            if ((*object).type==OBJ_FUNC){
                Token name;
                int objs=0;

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                this->context.push_back((*(*object).function).context);
                this->context.back().sym_tbl["this"]=(*left);
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                (*(*left)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                this->context.pop_back();

                return returnval;
            }
        }

        Object* call_class_special_noargs(string name){
            bool found;
            Object* object=new Object;
            Object* object_;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&this->context.back();

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            object_=&(*current).sym_tbl[str];
                            has_obj=true;

                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
    
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else{
                cout<<"Callable "<<name<<" not found";
                while (true);
            }

            if ((*object).type==OBJ_FUNC){
                Token name;
                int objs=0;

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                this->context.push_back((*(*object).function).context);
                if (has_obj){
                    this->context.back().sym_tbl["this"]=(*object_);
                }
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                if (has_obj){
                    (*(*object_)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                }
                this->context.pop_back();

                return returnval;
            }
        }

        Object* get_callable(Node n){
            CallNode call=(*n.callnode);
            string name=call.name.data;

            bool found;
            Object* object=new Object;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&this->context.back();

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
            
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else {
                //Builtin?
                if (std::find(this->builtins.begin(), this->builtins.end(), name) != this->builtins.end()) {
                    object=new Object(this->builtin_funcs[name].function,this->builtin_funcs[name].type,this->builtin_funcs[name].name);
                    Object* arg=new Object;
                    int objs=0;
                    unordered_map<string,Object> args;
                    args.clear();
                    args=(*(*object).function).context.sym_tbl;

                    vector<string> names;
                    names.clear();

                    for(auto &key: (*(*object).function).args) {
                        names.push_back(key.data);
                    }
                                    
                    for (Node n:call.names){
                        if (n.type==T_VarAssignNode){
                            this->context.push_back((*(*object).function).context);
                            arg=this->visit(n);
                            (*arg).name=(*n.varassignnode).name.data;
                            args[(*arg).name]=(*arg);
                            this->context.pop_back();
                        }
                        else{
                            arg=this->visit(n);
                            args[names[objs]]=(*arg);
                        }
                        objs++;
                    }
                    
                    if (name=="print"){
                        Object* returned= this->FPLPrint(args);
                        return returned;
                    }
                    if (name=="input"){
                        Object* returned= this->FPLInput(args);
                        return returned;
                    }
                    if (name=="len"){
                        Object* returned= this->FPLLen(args);
                        return returned;
                    }
                    if (name=="str"){
                        Object* returned= this->FPLStr(args);
                        return returned;
                    }
                    if (name=="num"){
                        Object* returned= this->FPLNum(args);
                        return returned;
                    }
                    if (name=="int"){
                        Object* returned= this->FPLInt(args);
                        return returned;
                    }
                    if (name=="float"){
                        Object* returned= this->FPLFloat(args);
                        return returned;
                    }
                    if (name=="list"){
                        Object* returned= this->FPLList(args);
                        return returned;
                    }
                    if (name=="range"){
                        Object* returned= this->FPLRange(args);
                        return returned;
                    }
                    if (name=="type"){
                        Object* returned= this->FPLType(args);
                        return returned;
                    }
                    if (name=="super"){
                        Object* returned= this->FPLSuper(args);
                        return returned;
                    }
                    if (name=="getattr"){
                        Object* returned= this->FPLGetAttr(args);
                        return returned;
                    }
                    if (name=="setattr"){
                        Object* returned= this->FPLSetAttr(args);
                        return returned;
                    }
                }
                else{
                    if (count(name.begin(), name.end(), '.')==1){
                        string varname=name.substr(0,name.find('.'));
                        string funcname=name.substr(name.find('.')+1);
                        Object var=this->context.back().sym_tbl[varname];

                        if (var.type==OBJ_LIST){
                            Object* arg=new Object;
                            int objs=0;
                            unordered_map<string,Object> args;
                            args.clear();
                            args=(*var.list).methods[funcname].context.sym_tbl;

                            vector<string> names;
                            names.clear();

                            for(auto &key: (*var.list).methods[funcname].args) {
                                names.push_back(key.data);
                            }
                                            
                            for (Node n:call.names){
                                if (n.type==T_VarAssignNode){
                                    this->context.push_back((*var.list).methods[funcname].context);
                                    arg=this->visit(n);
                                    (*arg).name=(*n.varassignnode).name.data;
                                    args[(*arg).name]=(*arg);
                                    this->context.pop_back();
                                }
                                else{
                                    arg=this->visit(n);
                                    args[names[objs]]=(*arg);
                                }
                                objs++;
                            }

                            if (funcname=="append"){
                                Object* res=(*var.list).append(args);
                                return res;
                            }
                        }
                    }
                    
                    cout<<"Callable "<<name<<" not found!";
                    while (true);
                }
            }
            return object;
        }

        Object* get_names(Object* object, CallNode call){
            //Know has args and is callable
            if ((*object).type==OBJ_FUNC){
                Object* arg=new Object;
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                for(auto &key: (*(*object).function).args) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                for (Node n:call.names){
                    if (n.type==T_VarAssignNode){
                        this->context.push_back((*(*object).function).context);
                        arg=this->visit(n);
                        (*arg).name=(*n.varassignnode).name.data;
                        (*(*object).function).context.sym_tbl[(*arg).name]=(*arg);
                        this->context.pop_back();
                    }
                    else{
                        arg=this->visit(n);
                        (*(*object).function).context.sym_tbl[names[objs]]=(*arg);
                    }
                    objs++;
                }
                return object;
            }

            else if ((*object).type==OBJ_CLASS){
                Object* arg=new Object;
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                this->context.push_back((*(*object)._class).context);
                Function callfunc = (*(*(*object)._class).context.sym_tbl["__init__"].function);
                this->context.pop_back();

                for(auto &key: callfunc.args ) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                for (Node n:call.names){
                    if (n.type==T_VarAssignNode){
                        this->context.push_back(callfunc.context);
                        arg=this->visit(n);
                        (*arg).name=(*n.varassignnode).name.data;
                        callfunc.context.sym_tbl[(*arg).name]=(*arg);
                        this->context.pop_back();
                    }
                    else{
                        arg=this->visit(n);
                        callfunc.context.sym_tbl[names[objs]]=(*arg);
                    }
                    objs++;
                }
                return object;
            }

            else{
                cout<<"Object is not a callable "<<call.name;
                while (true);
            }
        }

        Object* call_dotfunc(Object* object, bool has_obj, Object* object_, CallNode call){
            if ((*object).type==OBJ_FUNC){
                this->context.push_back((*(*object).function).context);
                if (has_obj){
                    this->context.back().sym_tbl["this"]=(*object_);
                }
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                if (has_obj){
                    (*(*object_)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                }
                this->context.pop_back();

                return returnval;
            }

            else if ((*object).type==OBJ_CLASS){
                this->context.push_back((*(*object)._class).context);
                Function callfunc = (*(*(*object)._class).context.sym_tbl["__init__"].function);
                this->context.pop_back();

                this->context.push_back((*(*object)._class).context);
                this->context.push_back(callfunc.context);
                this->context.back().sym_tbl["this"]=(*object);
                Object* returnval=this->run(callfunc.body); //CALL
                callfunc.context.sym_tbl=this->context.back().sym_tbl;
                this->context.pop_back();
                this->context.pop_back();

                return object;
            }

            else{
                cout<<"Object is not a callable "<<call.name;
                while (true);
            }
        }

        Object* visit_binop(Node n){
            BinOpNode node=(*n.binopnode);

            if (node.opr.type==T_LPAREN){

                Object* object=this->visit(node.left);
                
                CallNode call=(*node.right.callnode);
                if ((*object).type==OBJ_FUNC){
                    Object* arg=new Object;
                    Token name;
                    int objs=0;

                    std::vector<string> names;
                    names.clear();

                    for(auto &key: (*(*object).function).args) {
                        names.push_back(key.data);
                    }

                    if (this->context.size()==MAX_RECURSION){
                        cout<<"Recursion error";
                        while (true);
                    }

                    for (Node n:call.names){
                        if (n.type==T_VarAssignNode){
                            this->context.push_back((*(*object).function).context);
                            arg=this->visit(n);
                            (*arg).name=(*n.varassignnode).name.data;
                            (*(*object).function).context.sym_tbl[(*arg).name]=(*arg);
                            this->context.pop_back();
                        }
                        else{
                            arg=this->visit(n);
                            (*(*object).function).context.sym_tbl[names[objs]]=(*arg);
                        }
                        objs++;
                    }

                    this->context.push_back((*(*object).function).context);
                    
                    Object* returnval=this->run((*(*object).function).body); //CALL
                    (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                    
                    this->context.pop_back();

                    return returnval;
                }
                
                return object;
            }
            

            Object* left=this->visit(node.left);
            if (node.opr.type==T_DOT && (*left).type==OBJ_CLASS && node.right.type==T_CallNode){
                //First, get callable
                this->context.push_back((*(*left)._class).context);
                Object* callable=this->get_callable(node.right);
                this->context.pop_back();

                Object* callable_wargs=this->get_names(callable, (*node.right.callnode));
                if (this->context.size()>=3){
                    if (this->context[this->context.size()-1].sym_tbl.find("this")!=this->context[this->context.size()-1].sym_tbl.end()){
                        return this->call_dotfunc(callable_wargs, true, &this->context[this->context.size()-1].sym_tbl["this"], (*node.right.callnode));
                    }
                }

                return this->call_dotfunc(callable_wargs, false, NULL, (*node.right.callnode));


            }
            
            

            if (node.opr.type==T_DOT){
                Object* right=this->varaccess_((*node.right.varaccessnode).name.data, left);
                return right;
            }

            Object* right=this->visit(node.right);

            //i...
            if (node.opr.type==T_IADD){
                if ( ((*left).type==OBJ_STR) && ((*right).type==OBJ_STR) && node.left.type==T_VarAccessNode ){
                    String* lft=((*left).str);
                    String* rght=((*right).str);

                    Object* res= (*lft).iadd((*rght));
                    this->context.back().sym_tbl[(*node.left.varaccessnode).name.data]=(*new Object(lft, OBJ_STR, (*lft).value));
                    return res;
                }
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).iadd((*rght));
                    this->context.back().sym_tbl[(*node.left.varaccessnode).name.data]=(*new Object(lft, OBJ_NUM, (*lft).value.ToString()));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name=(*left).name+".__iadd__";
                    return this->call_class_special(name, right);
                }
            }

            if (node.opr.type==T_ISUB){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).isub((*rght));
                    this->context.back().sym_tbl[(*node.left.varaccessnode).name.data]=(*new Object(lft, OBJ_NUM, (*lft).value.ToString()));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name=(*left).name+".__isub__";
                    return this->call_class_special(name, right);
                }
            }

            if (node.opr.type==T_IMUL){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).imul((*rght));
                    this->context.back().sym_tbl[(*node.left.varaccessnode).name.data]=(*new Object(lft, OBJ_NUM, (*lft).value.ToString()));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name=(*left).name+".__imul__";
                    return this->call_class_special(name, right);
                }
            }

            if (node.opr.type==T_IDIV){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).idiv((*rght));
                    this->context.back().sym_tbl[(*node.left.varaccessnode).name.data]=(*new Object(lft, OBJ_NUM, (*lft).value.ToString()));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name=(*left).name+".__idiv__";
                    return this->call_class_special(name, right);
                }
            }
            



            //"normal"
            if (node.opr.type==T_LSQUARE){
                if ((*left).type==OBJ_STR && (*right).type==OBJ_NUM){
                    String* lft=((*left).str);
                    Number* rght=((*right).number);

                    Object* res= (*lft).get((*rght));
                    return res;
                }
                if ((*left).type==OBJ_LIST && (*right).type==OBJ_NUM){
                    List* lft=((*left).list);
                    Number* rght=((*right).number);

                    Object* res= (*lft).get((*rght));
                    return res;
                }
            }
            
            if (node.opr.type==T_PLUS){
                if ( ((*left).type==OBJ_STR) && ((*right).type==OBJ_STR) ){
                    String* lft=((*left).str);
                    String* rght=((*right).str);

                    Object* res= (*lft).add((*rght));
                    return res;
                }

                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).add((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__add__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_MINUS){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).sub((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__sub__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_MUL){
                if ( ((*left).type==OBJ_STR) && ((*right).type==OBJ_NUM) ){  
                    String* lft=((*left).str);
                    Number* rght=((*right).number);

                    Object* res= (*lft).mul((*rght));
                    return res;
                }

                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).mul((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__mul__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_DIV){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res=(*lft).div((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__div__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_POW){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res=(*lft).power((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__pow__";
                    return this->call_class_special_(name, right, left);
                }
            }


            //Comparison
            if (node.opr.type==T_EE){
                if ( ((*left).type==OBJ_STR) && ((*right).type==OBJ_STR) ){
                    String* lft=((*left).str);
                    String* rght=((*right).str);

                    Object* res= (*lft).eq((*rght));
                    return res;
                }

                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).eq((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__eq__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_NE){
                if ( ((*left).type==OBJ_STR) && ((*right).type==OBJ_STR) ){
                    String* lft=((*left).str);
                    String* rght=((*right).str);

                    Object* res= (*lft).ne((*rght));
                    return res;
                }

                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).ne((*rght));
                    return res;
                }
                if ( ((*left).type==OBJ_CLASS)){
                    string name="__ne__";
                    return this->call_class_special_(name, right, left);
                }
            }

            if (node.opr.type==T_GT){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).gt((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__gt__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type for comparison operator "<<node.opr.data;
                    while (true);
                }
            }

            if (node.opr.type==T_LT){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).lt((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__lt__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type for comparison operator "<<node.opr.data;
                    while (true);
                }
            }

            if (node.opr.type==T_LTE){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).lte((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__lte__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type for comparison operator "<<node.opr.data;
                    while (true);
                }
            }

            if (node.opr.type==T_GTE){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).gte((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__gte__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type for comparison operator "<<node.opr.data;
                    while (true);
                }
            }

            if (node.opr.type==T_AND){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).and_by((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__and__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type "<<node.opr.data<<" for and.";
                    while (true);
                }
            }

            if (node.opr.type==T_OR){
                if ( ((*left).type==OBJ_NUM) && ((*right).type==OBJ_NUM) ){                    
                    
                    Number* lft=((*left).number);
                    Number* rght=((*right).number);

                    Object* res= (*lft).or_by((*rght));
                    return res;
                }
                else if ( ((*left).type==OBJ_CLASS)){
                    string name="__or__";
                    return this->call_class_special_(name, right, left);
                }
                else{
                    cout<<"Invalid type "<<node.opr.data<<" for and.";
                    while (true);
                }
            }


            cout<<"ERROR binop";
            while(true){};
        }

        Object* index_assignment(BinOpNode n){
            Object* left;
            if (n.left.type==T_BinOpNode){
                left=this->index_assignment((*n.left.binopnode));
            }
            //Has to be var access
            else if (n.left.type==T_VarAccessNode){ 
                string name=(*n.left.varaccessnode).name.data;

                vector<string> names=this->split(name,".");
                Context* current=&this->context.back();

                if (names.size()>1){
                    int i=0;
                    for (string str: names){
                        if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                            if ((*current).sym_tbl[str].type==OBJ_CLASS){
                                current=&((*current).sym_tbl[str]._class->context);
                            }
                            if (names.size()-1!=i){
                                if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                    cout<<"Cannot . access from non-class";
                                    while (true);
                                }
                            }
                        }
                        i++;
                    }
                }

                if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                    left = &(*current).sym_tbl[names.back()];
                }
                else{
                    cout<<endl<<endl<<"Invalid variable name "<<name;
                    while (true);
                }
            }     
            else{
                cout<<"Invalid index assignment format";
                while (true);
            }

            Object* right=this->visit(n.right);

            if ((*left).type==OBJ_STR){
                cout<<"Strings are immutable";
                while (true);
            }

            else if ((*left).type==OBJ_LIST && (*right).type==OBJ_NUM){
                Object* val;
                val=&(*(*left).list).items[(*(*right).number).value.ToDouble()];
                return val;
            }

            else{
                cout<<"Incorrect types";
                while (true);
            }

        }

        Object* visit_varindexassignment(Node n){
            IndexAssignNode node=(*n.indexassignnode);
            //Know name is binopnode
            Object* var=index_assignment((*node.name.binopnode));
            Object* varval=this->visit(node.value);
            var->type=varval->type;
            var->str=varval->str;
            var->number=varval->number;
            var->function=varval->function;
            var->_class=varval->_class;
            var->list=varval->list;
            return varval;
        }

        Object* visit_varassignemnt(Node n){
            VarAssignNode node=(*n.varassignnode);
            Object* var=this->visit(node.value);
            (*var).name=node.name.data;

            vector<string> names=this->split((*var).name,".");
            Context* current=&this->context.back();

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }
            (*var).name=names.back();

            Object obj = (*var);
            Object* res;
            if (obj.type==OBJ_NUM){
                Number* val=new Number((*obj.number).value);
                res=new Object(val,obj.type,obj.name);
                (*res).refcount++;
            }
            else if (obj.type==OBJ_STR){
                String* val=new String((*obj.str).value);
                res=new Object(val,obj.type,obj.name);
                (*res).refcount++;
            }
            else if (obj.type==OBJ_FUNC){
                Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                res=new Object(val, obj.type,obj.name);
                (*res).refcount++;
            }
            else if (obj.type==OBJ_CLASS){
                Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                res=new Object(cl,obj.type,obj.name);
                (*res).refcount++;
            }
            else if (obj.type==OBJ_LIST){
                List* li=new List(obj.list->items);
                res=new Object(li,obj.type,obj.name);
                (*res).refcount++;
            }
            
            (*current).sym_tbl[names.back()]=(*res);
            return res;
        }


        Object* visit_unary(Node n){
            UnaryOpNode node = (*n.unaryopnode);
            Object* right=this->visit(node.right);
            Number num = (*(*right).number);
            if (node.opr.type==T_MINUS){
                Number* neg1=new Number(-1);
                return num.mul((*neg1));
            }
            if (node.opr.type==T_NOT){
                Number* neg1=new Number(-1);
                return num.not_();
            }

            else{
                Number* pos1=new Number(1);
                return num.mul((*pos1));
            }

        }

        Object* visit_string(Node n){
            StringNode node = (*n.stringnode);
            String* str=new String(node.token.data);
            Object* obj=new Object(str,OBJ_STR,(*str).value);
            return obj;
        }

        vector<string> split(string str, string token){
            vector<string>result;
            while(str.size()){
                int index = str.find(token);
                if(index!=string::npos){
                    result.push_back(str.substr(0,index));
                    str = str.substr(index+token.size());
                    if(str.size()==0)result.push_back(str);
                }else{
                    result.push_back(str);
                    str = "";
                }
            }
            return result;
        }

        Object* varaccess_(string name, Object* right){   
            vector<string> names=this->split(name,".");
            Context* current=&(*(*right)._class).context;

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }

            if ((*current).sym_tbl.find(name) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[name];

                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    Object* res=new Object(val,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    Object* res=new Object(val,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    Object* res=new Object(val, obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    Object* res=new Object(cl,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    Object* res=new Object(li,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
            }
            else {
                if (count(name.begin(),name.end(),'.')>0){
                    vector<string> names=this->split(name,".");
                    Context* current=&this->context.back();

                    if (names.size()>1){
                        int i=0;
                        for (string str: names){
                            if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                                if ((*current).sym_tbl[str].type==OBJ_CLASS){
                                    current=&((*current).sym_tbl[str]._class->context);
                                }
                                if (names.size()-1!=i){
                                    if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                        cout<<"Cannot . access from non-class";
                                        while (true);
                                    }
                                }
                            }
                            i++;
                        }
                    }

                    if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                        Object obj = (*current).sym_tbl[names.back()];
                        if (obj.type==OBJ_NUM){
                            Object* res=new Object(obj.number,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_STR){
                            Object* res=new Object(obj.str,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_FUNC){
                            Object* res=new Object(obj.function,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_CLASS){
                            Object* res=new Object(obj._class,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_LIST){
                            List* li=new List(obj.list->items);
                            Object* res=new Object(li,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                    }
                    else{
                        cout<<endl<<endl<<"Invalid variable name "<<name;
                        while (true);
                    }


                }
                cout<<endl<<endl<<"Invalid variable name "<<name;
                while (true);
            }

            Object* obj = new Object(OBJ_NONE);
            return obj;
        }

        Object* varaccess(string name){   
            vector<string> names=this->split(name,".");
            Context* current=&this->context.back();

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }

            if ((*current).sym_tbl.find(name) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[name];

                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    Object* res=new Object(val,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    Object* res=new Object(val,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    Object* res=new Object(val, obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    Object* res=new Object(cl,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    Object* res=new Object(li,obj.type,obj.name);
                    (*res).refcount++;
                    return res;
                }
            }
            else {
                if (count(name.begin(),name.end(),'.')>0){
                    vector<string> names=this->split(name,".");
                    Context* current=&this->context.back();

                    if (names.size()>1){
                        int i=0;
                        for (string str: names){
                            if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                                if ((*current).sym_tbl[str].type==OBJ_CLASS){
                                    current=&((*current).sym_tbl[str]._class->context);
                                }
                                if (names.size()-1!=i){
                                    if ((*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                        cout<<"Cannot . access from non-class";
                                        while (true);
                                    }
                                }
                            }
                            i++;
                        }
                    }

                    if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                        Object obj = (*current).sym_tbl[names.back()];
                        if (obj.type==OBJ_NUM){
                            Object* res=new Object(obj.number,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_STR){
                            Object* res=new Object(obj.str,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_FUNC){
                            Object* res=new Object(obj.function,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_CLASS){
                            Object* res=new Object(obj._class,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                        else if (obj.type==OBJ_LIST){
                            List* li=new List(obj.list->items);
                            Object* res=new Object(li,obj.type,obj.name);
                            (*res).refcount++;
                            return res;
                        }
                    }
                    else{
                        cout<<endl<<endl<<"Invalid variable name "<<name;
                        while (true);
                    }


                }
                cout<<endl<<endl<<"Invalid variable name "<<name;
                while (true);
            }

            Object* obj = new Object(OBJ_NONE);
            return obj;
        }

        Object* visit_varaccess(Node n){
            string name = (*n.varaccessnode).name.data;
            
            return this->varaccess(name);

        }

        Object* visit_funcdef(Node n){
            FuncDefNode fnode=(*n.funcdefnode);

            Position start=fnode.name.start;
            Position end=fnode.name.end; //fnode.args.back().end

            Context* ctxt=new Context(fnode.name.data, start,end);
            Function* func=new Function(fnode.name, fnode.names, fnode.lines, (*ctxt));
            Object* obj=new Object(func, OBJ_FUNC, fnode.name.data);
            this->context.back().sym_tbl[(*obj).name]=(*obj);

            (*func).context.sym_tbl[(*obj).name]=(*obj);
            //Add default vars
            int i=0;
            for(Token name : fnode.names){
                Node val=fnode.values[i];
                if (val.type!=T_EOF){
                    Object* obj=this->visit(val);
                    (*obj).name=name.data;
                    (*func).context.sym_tbl[name.data]=(*obj);
                }
                i++;
                
            }


            return obj;
        }


        Object* visit_call(Node n){
            CallNode call=(*n.callnode);
            string name=call.name.data;

            bool found;
            Object* object=new Object;
            Object* object_;
            bool has_obj=false;

            vector<string> names=this->split(name,".");
            Context* current=&this->context.back();

            

            if (names.size()>1){
                int i=0;
                for (string str: names){
                    if ((*current).sym_tbl.find(str) != (*current).sym_tbl.end()) {
                        if ((*current).sym_tbl[str].type==OBJ_CLASS){
                            object_=&(*current).sym_tbl[str];
                            has_obj=true;

                            current=&((*current).sym_tbl[str]._class->context);
                        }
                        if (names.size()-1!=i){
                            if ((*current).sym_tbl.find(names[i+1]) != (*current).sym_tbl.end() && (*current).sym_tbl[names[i+1]].type!=OBJ_CLASS && names.size()-1!=i+1){
                                cout<<"Cannot . access from non-class";
                                while (true);
                            }
                        }
                    }
                    i++;
                }
            }

            
            
            
            if ((*current).sym_tbl.find(names.back()) != (*current).sym_tbl.end()) {
                Object obj = (*current).sym_tbl[names.back()];
                if (obj.type==OBJ_NUM){
                    Number* val=new Number((*obj.number).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_STR){
                    String* val=new String((*obj.str).value);
                    object=new Object(val,obj.type,obj.name);
                }
                else if (obj.type==OBJ_FUNC){
                    Function* val=new Function((*obj.function).name,(*obj.function).args, (*obj.function).body, (*obj.function).context);
                    object=new Object(val, obj.type,obj.name);
                }
                else if (obj.type==OBJ_CLASS){
                    Class* cl=new Class(obj._class->name, obj._class->context, obj._class->mro);
                    object=new Object(cl,obj.type,obj.name);
                }
                else if (obj.type==OBJ_LIST){
                    List* li=new List(obj.list->items);
                    object=new Object(li,obj.type,obj.name);
                }
            }
            else {
                //Builtin?
                if (std::find(this->builtins.begin(), this->builtins.end(), name) != this->builtins.end()) {
                    object=new Object(this->builtin_funcs[name].function,this->builtin_funcs[name].type,this->builtin_funcs[name].name);
                    Object* arg=new Object;
                    int objs=0;
                    unordered_map<string,Object> args;
                    args.clear();
                    args=(*(*object).function).context.sym_tbl;

                    vector<string> names;
                    names.clear();

                    for(auto &key: (*(*object).function).args) {
                        names.push_back(key.data);
                    }
                                    
                    for (Node n:call.names){
                        if (n.type==T_VarAssignNode){
                            this->context.push_back((*(*object).function).context);
                            arg=this->visit(n);
                            (*arg).name=(*n.varassignnode).name.data;
                            args[(*arg).name]=(*arg);
                            this->context.pop_back();
                        }
                        else{
                            arg=this->visit(n);
                            args[names[objs]]=(*arg);
                        }
                        objs++;
                    }
                    
                    if (name=="print"){
                        Object* returned= this->FPLPrint(args);
                        return returned;
                    }
                    if (name=="input"){
                        Object* returned= this->FPLInput(args);
                        return returned;
                    }
                    if (name=="len"){
                        Object* returned= this->FPLLen(args);
                        return returned;
                    }
                    if (name=="str"){
                        Object* returned= this->FPLStr(args);
                        return returned;
                    }
                    if (name=="num"){
                        Object* returned= this->FPLNum(args);
                        return returned;
                    }
                    if (name=="int"){
                        Object* returned= this->FPLInt(args);
                        return returned;
                    }
                    if (name=="float"){
                        Object* returned= this->FPLFloat(args);
                        return returned;
                    }
                    if (name=="list"){
                        Object* returned= this->FPLList(args);
                        return returned;
                    }
                    if (name=="range"){
                        Object* returned= this->FPLRange(args);
                        return returned;
                    }
                    if (name=="type"){
                        Object* returned= this->FPLType(args);
                        return returned;
                    }
                    if (name=="super"){
                        Object* returned= this->FPLSuper(args);
                        return returned;
                    }
                    if (name=="getattr"){
                        Object* returned= this->FPLGetAttr(args);
                        return returned;
                    }
                    if (name=="setattr"){
                        Object* returned= this->FPLSetAttr(args);
                        return returned;
                    }
                }
                else{
                    if (count(name.begin(), name.end(), '.')==1){
                        string varname=name.substr(0,name.find('.'));
                        string funcname=name.substr(name.find('.')+1);
                        Object var=this->context.back().sym_tbl[varname];

                        if (var.type==OBJ_LIST){
                            Object* arg=new Object;
                            int objs=0;
                            unordered_map<string,Object> args;
                            args.clear();
                            args=(*var.list).methods[funcname].context.sym_tbl;

                            vector<string> names;
                            names.clear();

                            for(auto &key: (*var.list).methods[funcname].args) {
                                names.push_back(key.data);
                            }
                                            
                            for (Node n:call.names){
                                if (n.type==T_VarAssignNode){
                                    this->context.push_back((*var.list).methods[funcname].context);
                                    arg=this->visit(n);
                                    (*arg).name=(*n.varassignnode).name.data;
                                    args[(*arg).name]=(*arg);
                                    this->context.pop_back();
                                }
                                else{
                                    arg=this->visit(n);
                                    args[names[objs]]=(*arg);
                                }
                                objs++;
                            }

                            if (funcname=="append"){
                                Object* res=(*var.list).append(args);
                                return res;
                            }
                        }
                    }
                    
                    cout<<"Callable "<<name<<" not found";
                    while (true);
                }
            }
            

            //Know has args and is callable
            if ((*object).type==OBJ_FUNC){
                Object* arg=new Object;
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                for(auto &key: (*(*object).function).args) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                for (Node n:call.names){
                    if (n.type==T_VarAssignNode){
                        this->context.push_back((*(*object).function).context);
                        arg=this->visit(n);
                        (*arg).name=(*n.varassignnode).name.data;
                        (*(*object).function).context.sym_tbl[(*arg).name]=(*arg);
                        this->context.pop_back();
                    }
                    else{
                        arg=this->visit(n);
                        (*(*object).function).context.sym_tbl[names[objs]]=(*arg);
                    }
                    objs++;
                }

                this->context.push_back((*(*object).function).context);
                if (has_obj){
                    this->context.back().sym_tbl["this"]=(*object_);
                }
                Object* returnval=this->run((*(*object).function).body); //CALL
                (*(*object).function).context.sym_tbl=this->context.back().sym_tbl;
                if (has_obj){
                    (*(*object_)._class).context.sym_tbl=(*this->context.back().sym_tbl["this"]._class).context.sym_tbl;
                }
                this->context.pop_back();

                return returnval;
            }

            else if ((*object).type==OBJ_CLASS){
                Object* arg=new Object;
                Token name;
                int objs=0;

                std::vector<string> names;
                names.clear();

                this->context.push_back((*(*object)._class).context);
                Function callfunc = (*(*(*object)._class).context.sym_tbl["__init__"].function);
                this->context.pop_back();

                for(auto &key: callfunc.args ) {
                    names.push_back(key.data);
                }

                if (this->context.size()==MAX_RECURSION){
                    cout<<"Recursion error";
                    while (true);
                }

                for (Node n:call.names){
                    if (n.type==T_VarAssignNode){
                        this->context.push_back(callfunc.context);
                        arg=this->visit(n);
                        (*arg).name=(*n.varassignnode).name.data;
                        callfunc.context.sym_tbl[(*arg).name]=(*arg);
                        this->context.pop_back();
                    }
                    else{
                        arg=this->visit(n);
                        callfunc.context.sym_tbl[names[objs]]=(*arg);
                    }
                    objs++;
                }

                this->context.push_back((*(*object)._class).context);
                this->context.push_back(callfunc.context);
                this->context.back().sym_tbl["this"]=(*object);
                Object* returnval=this->run(callfunc.body); //CALL
                callfunc.context.sym_tbl=this->context.back().sym_tbl;
                this->context.pop_back();
                this->context.pop_back();

                return object;
            }

            else{
                cout<<"Object is not a callable "<<name;
                while (true);
            }



        }

        Object* visit_if(Node n){
            IfNode i=(*n.ifnode);
            bool istrue=(*(*this->visit(i.statement)).number).value.ToDouble();
            if (istrue){
                return this->run(i.lines); //Should not return
            }
            else{
                for (ElifNode elif: i.elif){
                    bool istrue=(*(*this->visit(elif.statement)).number).value.ToDouble();
                    if (istrue){
                        return this->run(elif.lines); //Should not return
                    }
                }
                //Must be else now
                if (i.else_!=NULL){
                    return this->run((*i.else_).lines);
                }
                Number* num=new Number(0);
                Object* ret=new Object(num,OBJ_NUM,"0");
                return ret;
            }

        }

        Object* visit_return(Node n){
            ReturnNode r=(*n.returnnode);
            Object* ret=this->visit(r.value);
            (*ret).isret=true;
            return ret;
        }

        Object* visit_while(Node n){
            WhileNode w=(*n.whilenode);
            this->looplevel+=1;
            while((*(*this->visit(w.statement)).number).value.ToDouble()){
                Object* obj=this->run(w.lines);
                if ((*obj).iscont){
                    continue;
                }
                if ((*obj).isbreak){
                    break;
                }
            }

            this->looplevel-=1;

            Object* none=new Object;
            (*none).type=OBJ_NONE;
            return none;

        }

        Object* visit_break(Node n){
            BreakNode r=(*n.breaknode);
            Number* num=new Number(0);
            Object* ret=new Object(num,OBJ_NUM,"0");
            (*ret).isbreak=true;
            return ret;
        }

        Object* visit_continue(Node n){
            ContinueNode r=(*n.continuenode);
            Number* num=new Number(0);
            Object* ret=new Object(num,OBJ_NUM,"0");
            (*ret).iscont=true;
            return ret;
        }

        Object* visit_classdef(Node n){
            ClassDefNode c=(*n.classdefnode);
            vector<Object> mro;
            mro.clear();

            Context* ctxt=new Context();
            //Inheritance
            Node nd;
            for (VarAccessNode node:c.inherits){
                nd=Node(&node, T_VarAccessNode);
                Object class_=(*this->visit(nd));
                if (class_.type!=OBJ_CLASS){
                    cout<<"Cannot inherit from non-class";
                    while (true);
                }
                mro.push_back(class_);
                for (auto key: (*class_._class).context.sym_tbl){
                    (*ctxt).sym_tbl[key.first]=key.second;
                }
                //(*ctxt).sym_tbl[node.name.data]=class_;
            }
            this->context.push_back((*ctxt));
            //Variables
            for (Node node:c.funcs){
                if (node.type!=T_ClassDefNode){
                    this->visit(node);
                }
            }
            Context ctx=(*new Context() );
            ctx.sym_tbl=this->context.back().sym_tbl;
            ctx.name=c.name.data;

            this->context.pop_back();

            Class* _class=new Class(c.name, ctx, mro);
            Object* obj=new Object(_class, OBJ_CLASS, c.name.data);
            
            //MRO
            (*(*obj)._class).mro.insert((*(*obj)._class).mro.begin(), (*obj));
            List* l=new List((*(*obj)._class).mro);
            Object ol=(*new Object(l, OBJ_LIST, "MRO"));
            (*(*obj)._class).context.sym_tbl["__mro__"]=ol;

            this->context.back().sym_tbl[(*obj).name]=(*obj);
            return obj;
        }

        Object* visit_for(Node n){
            ForNode w=(*n.fornode);
            
            Object* iterator=this->visit(w.iterator);

            if ((*iterator).type==OBJ_STR || (*iterator).type==OBJ_LIST){
            }
            else if ((*iterator).type==OBJ_CLASS){
                cout<<"Trying to perform for loop on class - not supported yet";
                while (true);
            }
            else{
                cout<<"Cannot perform for loop on object";
                while (true);
            }

            int length=0;
            if ((*iterator).type==OBJ_STR){
                length=(*(*(*(*iterator).str).length()).number).value.ToDouble();
            }
            else if ((*iterator).type==OBJ_LIST){
                length=(*(*(*(*iterator).list).length()).number).value.ToDouble();
            }
            
            VarAssignNode* assign;
            for (int i=0; i<length; i++){
                Object* val;
                if ((*iterator).type==OBJ_STR){
                    val=(*(*iterator).str).get(Number(i));
                }
                else if ((*iterator).type==OBJ_LIST){
                    val=(*(*iterator).list).get(Number(i));
                }
                
                this->context.back().sym_tbl[w.varname.data]=(*val);
                this->run(w.lines);
            }

            Object* none=new Object;
            (*none).type=OBJ_NONE;
            return none;

        }

};


