const string OBJ_NUM="num";
const string OBJ_STR="str";
const string OBJ_FUNC="func";
const string OBJ_NONE="none";
const string OBJ_CLASS="class";
const string OBJ_LIST="list";
const string OBJ_TYPE="type";

class Number;
class String;
class Function;
class Class;
class List;
class Object{
    friend std::ostream& operator<<(std::ostream &s, const Object &obj);

    public:
        string type="";
        Number* number;
        String* str;
        Function* function;
        Class* _class;
        List* list;

        string name="";
        int refcount=0;
        bool callable=false;
        bool isret=false;
        bool isbreak=false;
        bool iscont=false;

        Object(){}

        Object(string ty){
            type=ty;
        }

        Object(Number* num, string ty, string nm){
            number=num;
            type=ty;
            name=nm;
        }

        Object(String* str_, string ty, string nm){
            str=str_;
            type=ty;
            name=nm;
        }

        Object(Function* func, string ty, string nm){
            function=func;
            type=ty;
            name=nm;
        }

        Object(Class* cl, string ty, string nm){
            _class=cl;
            type=ty;
            name=nm;
        }

        Object(List* li, string ty, string nm){
            list=li;
            type=ty;
            name=nm;
        }

};

class Context{
    public:
        string name;
        Position start;
        Position end;
        unordered_map<string, Object> sym_tbl;
        
        Context(){};
        Context(string n, Position strt, Position en){
            name=n;
            start=strt;
            end=en;
            sym_tbl.clear();
        }
};