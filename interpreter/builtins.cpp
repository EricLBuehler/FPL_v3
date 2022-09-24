class Interpreter;

void InitPrint(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="print";

    Token* funcname=new Token;
    (*funcname).data="print";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));
    Token* end_param=new Token;
    (*end_param).data="end";
    (*func).args.push_back((*end_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "print");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    String* str=new String("\n");
    obj=new Object(str, OBJ_STR, "\n");
    (*obj).name="end";
    (*func).context.sym_tbl["end"]=(*obj);

    str=new String("");
    obj=new Object(str, OBJ_STR, "");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("print");

}


void InitInput(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="input";

    Token* funcname=new Token;
    (*funcname).data="input";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="prompt";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "input");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    String* str=new String("");
    obj=new Object(str, OBJ_STR, "");
    (*obj).name="prompt";
    (*func).context.sym_tbl["prompt"]=(*obj);

    (*interpreter).builtins.push_back("input");

}

void InitLen(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="len";

    Token* funcname=new Token;
    (*funcname).data="len";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "len");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    String* str=new String("");
    obj=new Object(str, OBJ_STR, "");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("len");

}

void InitStr(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="str";

    Token* funcname=new Token;
    (*funcname).data="str";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "str");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    String* str=new String("");
    obj=new Object(str, OBJ_STR, "");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("str");

}

void InitNum(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="num";

    Token* funcname=new Token;
    (*funcname).data="num";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "num");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    Number* str=new Number(BigFloat("0"));
    obj=new Object(str, OBJ_NUM, "0");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("num");

}

void InitInt(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="int";

    Token* funcname=new Token;
    (*funcname).data="int";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "int");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    Number* str=new Number(BigFloat("0"));
    obj=new Object(str, OBJ_NUM, "0");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("int");

}

void InitFloat(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="float";

    Token* funcname=new Token;
    (*funcname).data="float";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "float");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    Number* str=new Number(BigFloat("0.0"));
    obj=new Object(str, OBJ_NUM, "0.0");
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("float");

}

void InitList(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="list";

    Token* funcname=new Token;
    (*funcname).data="list";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "list");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("list");

}

void InitRange(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="range";

    Token* funcname=new Token;
    (*funcname).data="range";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="start";
    (*func).args.push_back((*obj_param));
    Token* end_param=new Token;
    (*end_param).data="end";
    (*func).args.push_back((*end_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "range");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    Number* num=new Number(BigFloat("0"));
    obj=new Object(num, OBJ_NUM, "0");
    (*obj).name="start";
    (*func).context.sym_tbl["start"]=(*obj);
    
    num=new Number(BigFloat("0"));
    obj=new Object(num, OBJ_NUM, "0");
    (*obj).name="end";
    (*func).context.sym_tbl["end"]=(*obj);

    (*interpreter).builtins.push_back("range");

}

void InitType(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="type";

    Token* funcname=new Token;
    (*funcname).data="type";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "type");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);

    (*interpreter).builtins.push_back("type");

}


void InitSuper(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="super";

    Token* funcname=new Token;
    (*funcname).data="super";
    Function* func=new Function;
    (*func).name=(*funcname);

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "super");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);

    (*interpreter).builtins.push_back("super");

}


void InitGetAttr(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="getattr";

    Token* funcname=new Token;
    (*funcname).data="getattr";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));
    Token* name_param=new Token;
    (*name_param).data="name";
    (*func).args.push_back((*name_param));
    Token* def_param=new Token;
    (*def_param).data="default";
    (*func).args.push_back((*def_param));;

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "getattr");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="name";
    (*func).context.sym_tbl["name"]=(*obj);

    obj=new Object(OBJ_NONE);
    (*obj).name="default";
    (*func).context.sym_tbl["default"]=(*obj);

    (*interpreter).builtins.push_back("getattr");

}

void InitSetAttr(Interpreter* interpreter){
    Context* ctxt=new Context;
    (*ctxt).name="setattr";

    Token* funcname=new Token;
    (*funcname).data="setattr";
    Function* func=new Function;
    (*func).name=(*funcname);
    

    Token* obj_param=new Token;
    (*obj_param).data="obj";
    (*func).args.push_back((*obj_param));
    Token* name_param=new Token;
    (*name_param).data="name";
    (*func).args.push_back((*name_param));
    Token* def_param=new Token;
    (*def_param).data="value";
    (*func).args.push_back((*def_param));;

    (*func).context=(*ctxt);
    Object* obj=new Object(func, OBJ_FUNC, "setattr");
    (*interpreter).builtin_funcs[(*obj).name]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="obj";
    (*func).context.sym_tbl["obj"]=(*obj);
    
    obj=new Object(OBJ_NONE);
    (*obj).name="name";
    (*func).context.sym_tbl["name"]=(*obj);

    obj=new Object(OBJ_NONE);
    (*obj).name="value";
    (*func).context.sym_tbl["value"]=(*obj);

    (*interpreter).builtins.push_back("setattr");

}

