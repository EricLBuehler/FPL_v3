class Iterator{
    public:
        Iterator(){}

        void append(){
            this->illegal_operation("add");
        }

        void pop(){
            this->illegal_operation("add");
        }

        void set(){
            this->illegal_operation("add");
        }

        void get(){
            this->illegal_operation("add");
        }

        void illegal_operation(string op){
            cout<<"Illegal operation "<<op;
            while(true);
        }
};

class Number: Object{
    public:
        BigFloat value=0;
        vector<string> methods;
        vector<string> inherits;

        Number(string data){
            this->value=BigFloat(data);
            
            this->inherits.clear();
            this->inherits.push_back("object");
            this->inherits.push_back("iterator");

            this->methods.clear();
            this->methods.push_back("add");
            this->methods.push_back("sub");
            this->methods.push_back("div");
            this->methods.push_back("mul");
            this->methods.push_back("eq");
            this->methods.push_back("ne");
            this->methods.push_back("gt");
            this->methods.push_back("gte");
            this->methods.push_back("lt");
            this->methods.push_back("lte");
        }

        Number(double data){
            this->value=BigFloat(data);
            this->inherits.clear();
            this->inherits.push_back("object");
            this->inherits.push_back("iterator");

            this->methods.clear();
            this->methods.push_back("add");
            this->methods.push_back("sub");
            this->methods.push_back("div");
            this->methods.push_back("mul");
            this->methods.push_back("eq");
            this->methods.push_back("ne");
            this->methods.push_back("gt");
            this->methods.push_back("gte");
            this->methods.push_back("lt");
            this->methods.push_back("lte");
        }

        Number(BigFloat data){
            this->value=data;

            this->inherits.clear();
            this->inherits.push_back("object");
            this->inherits.push_back("iterator");

            this->methods.clear();
            this->methods.push_back("add");
            this->methods.push_back("sub");
            this->methods.push_back("div");
            this->methods.push_back("mul");
            this->methods.push_back("eq");
            this->methods.push_back("ne");
            this->methods.push_back("gt");
            this->methods.push_back("gte");
            this->methods.push_back("lt");
            this->methods.push_back("lte");
        }

        Object* add(Number other){
            BigFloat val=this->value;
            val=other.value+val;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* sub(Number other){
            BigFloat val=this->value;
            val=val-other.value;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* mul(Number other){
            BigFloat val=this->value;
            val=other.value*val;

            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        BigFloat strip_zeroes(string str){
            if(str.find('.') != std::string::npos){
                // Remove trailing zeroes
                str = str.substr(0, str.find_last_not_of('0')+1);
                // If the decimal point is now the last character, remove that as well
                if(str.find('.') == str.size()-1){
                    str = str.substr(0, str.size()-1);
                }
            }
            return BigFloat(str);
        }

        Object* div(Number other){
            BigFloat val=this->value;
            val.SetPrecision(STRIP_DIGITS_PRECISION);
            val=val/other.value;
            val=strip_zeroes(val.ToString());
            
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* power(Number other){
            BigFloat val=this->value;
            val=big_pow(val,other.value);
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* eq(Number other){
            int result=false;
            if (this->value==other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* ne(Number other){
            int result=false;
            if (this->value!=other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* gt(Number other){
            int result=false;
            if (this->value>other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* gte(Number other){
            int result=false;
            if (this->value>=other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* lt(Number other){
            int result=false;
            if (this->value<other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* lte(Number other){
            int result=false;
            if (this->value<=other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }


        Object* and_by(Number other){
            int result=false;
            if (this->value == other.value == true){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* or_by(Number other){
            int result=false;
            if (this->value == true || other.value == true){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* not_(){
            int result=false;
            if (this->value==false){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* iadd(Number other){
            BigFloat val=this->value;
            val=other.value+val;
            this->value=val;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* isub(Number other){
            BigFloat val=this->value;
            val=val-other.value;
            this->value=val;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* imul(Number other){
            BigFloat val=this->value;
            val=other.value*val;
            this->value=val;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

        Object* idiv(Number other){
            BigFloat val=this->value;
            val.SetPrecision(STRIP_DIGITS_PRECISION);
            val=val/other.value;
            val=strip_zeroes(val.ToString());
            this->value=val;
            Number* n=new Number(val);
            Object* r=new Object(n,OBJ_NUM,val.ToString());
            return r;
        }

};

class Function: Object{
    public:
        Token name;
        vector<Token> args;
        vector<Node> body;
        Context context;

        Function(){
            callable=true;
        }
        Function(Token nm, vector<Token> arg, vector<Node> bdy, Context ctxt){
            name=nm;
            args=arg;
            body=bdy;
            context=ctxt;
            callable=true;
        }
};

class String: Object,Iterator{
    public:
        string value;
        unordered_map<string, Function> methods;
        vector<string> inherits;

        String(string data){
            this->value=data;

            this->methods.clear();
            
            Context* ctxt=new Context;
            (*ctxt).name="append";

            Token* funcname=new Token;
            (*funcname).data="append";
            Function* func=new Function;
            (*func).name=(*funcname);
            

            Token* obj_param=new Token;
            (*obj_param).data="obj";
            (*func).args.push_back((*obj_param));

            (*func).context=(*ctxt);

            Object* obj=new Object(OBJ_NONE);
            (*obj).name="obj";
            (*func).context.sym_tbl["obj"]=(*obj);

            this->methods[(*func).name.data]=(*func);

            this->inherits.clear();
            this->inherits.push_back("object");
            this->inherits.push_back("iterator");
        }

        Object* add(String other){
            string res=this->value+other.value;
            String* s=new String(res);
            Object* r=new Object(s,OBJ_STR,res);
            return r;
        }


        Object* mul(Number other){
            string res="";
            for (BigFloat i=0; i<other.value; i++){
                res=res+this->value;
            }
            String* s=new String(res);
            Object* r=new Object(s,OBJ_STR,res);
            return r;
        }

        Object* eq(String other){
            int result=false;
            if (this->value==other.value){
                result=true;                                                                                                                            
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* ne(String other){
            int result=false;
            if (this->value!=other.value){
                result=true;
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* append(String other){
            string res=this->value+other.value;
            String* s=new String(res);
            Object* r=new Object(s,OBJ_STR,res);
            return r;
        }

        Object* pop(){
            string res="";
            res+=""+this->value.back();
            this->value.pop_back();
            String* s=new String(res);
            Object* r=new Object(s,OBJ_STR,res);
            return r;
        }

        Object* get(Number other){
            if (other.value>=BigFloat((double)this->value.length())){
                cout<<"Index too large";
                while (true);
            }
            if (other.value<0){
                other.value=BigFloat((double)this->value.length())+other.value;
                if (other.value<=0){
                    cout<<"Index too small";
                    while (true);
                }
            }
            string res="";
            res+=this->value[other.value.ToDouble()];
            String* s=new String(res);
            Object* r=new Object(s,OBJ_STR,res);
            return r;
        }

        Object* length(){
            int result=this->value.size();
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* iadd(String obj){
            this->value+=obj.value;
            String* s=new String(obj.value);
            Object* r=new Object(s, OBJ_STR, this->value);
            return r;
        }


};

class Class: Object{
    public:
        Token name;
        Context context;
        vector<Object> mro;

        Class(){
            callable=true;
            mro.clear();
        }
        Class(Token nm,  Context ctxt, vector<Object> _mro){
            name=nm;
            context=ctxt;
            callable=true;
            mro.clear();
            mro=_mro;
        }
};

class List: Object{
    public:
        vector<Object> items;
        unordered_map<string, Function> methods;
        vector<string> inherits;
        

        List(vector<Object> itms){
            this->items=itms;

            this->methods.clear();
            
            Context* ctxt=new Context;
            (*ctxt).name="append";

            Token* funcname=new Token;
            (*funcname).data="append";
            Function* func=new Function;
            (*func).name=(*funcname);
            

            Token* obj_param=new Token;
            (*obj_param).data="obj";
            (*func).args.push_back((*obj_param));

            (*func).context=(*ctxt);

            Object* obj=new Object(OBJ_NONE);
            (*obj).name="obj";
            (*func).context.sym_tbl["obj"]=(*obj);

            this->methods[(*func).name.data]=(*func);


            this->inherits.clear();
            this->inherits.push_back("object");
        }

        Object* eq(List other){
            int result=false;
            int idx=0;
            for (idx=0; idx<this->items.size(); idx++){
                Object a=this->items[idx];
                Object b=this->items[idx];
                if (a.type!=b.type){
                    break;
                }
                if (a.type==OBJ_NUM){
                    if ((*a.number).eq((*b.number))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
                else if (a.type==OBJ_STR){
                    if ((*a.str).eq((*b.str))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
                else if (a.type==OBJ_LIST){
                    if ((*a.str).eq((*b.str))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* ne(List other){
            int result=false;
            int idx=0;
            for (idx=0; idx<this->items.size(); idx++){
                Object a=this->items[idx];
                Object b=this->items[idx];
                if (a.type!=b.type){
                    break;
                }
                if (a.type==OBJ_NUM){
                    if ((*a.number).ne((*b.number))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
                else if (a.type==OBJ_STR){
                    if ((*a.str).ne((*b.str))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
                else if (a.type==OBJ_LIST){
                    if ((*a.str).ne((*b.str))){
                        result=true;
                    }
                    else{
                        result=false;
                        break;
                    }
                }
            }
            Number* n=new Number(result);
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }
        
        Object* mul(Number other){
            vector<Object> itms;
            itms.clear();
            for (BigFloat i=0; i<other.value-1; i++){
                for (Object l: this->items){
                    itms.push_back(l);
                }
            }

            this->items=itms;

            List* list=new List(this->items);
            Object* r=new Object(list,OBJ_LIST,"LIST");
            return r;

        }

        Object* get(Number other){
            //Checks for value here
            Object obj=this->items[other.value.ToDouble()];
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
            else{
                cout<<"Object type uncertain";
                while (true);
            }
        }

        Object* length(){
            int result=this->items.size();
            Number* n=new Number(to_string(result));
            Object* r=new Object(n,OBJ_NUM,to_string(result));
            return r;
        }

        Object* append(unordered_map<string,Object> args){
            Object obj=args["obj"];
            this->items.push_back(obj);

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
            else{
                cout<<"Object type uncertain";
                while (true);
            }
        }

};










std::ostream& operator<<(std::ostream &s, const Object &obj){
    if (obj.type==OBJ_NUM){
        return s<<(*obj.number).value.ToString();
    }
    if (obj.type==OBJ_STR){
        (*obj.str).value=replace_newlines((*obj.str).value);
        return s<<"'"<<(*obj.str).value<<"'";
    }
    if (obj.type==OBJ_TYPE){
        (*obj.str).value=replace_newlines((*obj.str).value);
        return s<<"'"<<(*obj.str).value<<"'";
    }
    if (obj.type==OBJ_FUNC){
        return s<<"<function "<<(*obj.function).name.data<<">";
    }
    if (obj.type==OBJ_CLASS){
        return s<<"<class "<<(*obj._class).name.data<<">";
    }
    if (obj.type==OBJ_LIST){
        s<<"[";
        int i=1;
        int size=(*obj.list).items.size();
        for (Object obj: (*obj.list).items){
            s<<obj;
            if (i==1000){
                s<<", ...";
                break;
            }
            if (i<size){
                s<<", ";
            }
            i++;
        }
        return s<<"]";
    }
    return s<<"Invalid object type";
}

std::ostream& operator<<(std::ostream &s, const Object* obj){ //This overloaded version: pass pointer object to print raw
    if ((*obj).type==OBJ_NUM){
        return s<<(*(*obj).number).value.ToString();
    }
    if ((*obj).type==OBJ_STR){
        return s<<(*(*obj).str).value;
    }
    if ((*obj).type==OBJ_TYPE){
        return s<<(*(*obj).str).value;
    }
    if ((*obj).type==OBJ_FUNC){
        return s<<"<function "<<(*(*obj).function).name.data<<">";
    }
    if ((*obj).type==OBJ_CLASS){
        return s<<"<class "<<(*(*obj)._class).name.data<<">";
    }
    if ((*obj).type==OBJ_LIST){
        s<<"[";
        int i=1;
        int size=(*(*obj).list).items.size();
        for (Object obj: (*(*obj).list).items){
            s<<obj;
            if (i==1000){
                s<<", ...";
                break;
            }
            if (i<size){
                s<<", ";
            }
            i++;
        }
        return s<<"]";
    }
    //Make an error
    return s<<"";
}