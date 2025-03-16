#include <iostream>
#include <vector>
using namespace std;

// Token types
typedef enum {
    KEYWORD_TOKEN,              // keyword token
    CURVE_LBRACE_TOKEN,               // "(" left brace token 
    CURVE_RBRACE_TOKEN,               // ")" right brace token
    SQUARE_LBRACE_TOKEN,               // "[" left brace token 
    SQUARE_RBRACE_TOKEN,               // "]" right brace token
    CURLY_LBRACE_TOKEN,               // "{" left brace token 
    CURLY_RBRACE_TOKEN,               // "}" right brace token
    ID_TOKEN,                   // id token
    NUM_TOKEN,                  // num token
    OPERATOR_TOKEN,             // +,-,/,*,%,**, operator token
    COLON_TOKEN  ,               // : 
    INVALID_TOKEN,              // invalid token
    COMPARE_OPERATOR_TOKEN,      // ==,>=,<=,!=
    BOOL_TOKEN,                 // True or False
    NOT_TOKEN,                // not ! token
    COMMENT_TOKEN,              // comment token
    EQUAL_TOKEN,               // = token
    STRING_TOKEN,              // string token
    CHAR_TOKEN,                // char token
} TokenType;

// Token structure

typedef struct Token{
    TokenType token_type;
    string token_text;
    Token(string s,TokenType t){
        token_text=s;
        token_type=t;
    }
} Token;

// check if the character is a start of an identifier
bool is_id_start(char s){
    if(s=='_'||isalpha(s)) return true;
    return false;
}
// check if the character is an identifier
bool is_id(char s){
    if(s=='_'||isalnum(s)) return true;
    return false;
}
// check if the character is a digit start
bool is_digit_start(char s){
    if(isdigit(s) && s!=0) return true;
    return false;
}
// check if the character is a digit
bool is_digit(char s){
    if(isdigit(s)) return true;
    return false;
}
// check if the character is an operator
bool is_operator(char c) {
    if ( (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '%') || (c == '&') || (c == '|') || (c == '^')){
        return true;
    }else{
        return false;
    }
}
// check if the character is a compare operator
bool is_compare_operator(string c) {
    if ( (c == "==") || (c == ">=") || (c == "<=") || (c == "!=") || (c == ">") || (c == "<") ){
        return true;
    }else{
        return false;
    }
}
// check if the character is a compare operator start
bool is_compare_operator_start(char c) {
    if ( (c == '=') || (c == '>') || (c == '<') || (c == '!') ){
        return true;
    }else{
        return false;
    }
}
// check if the character is a braces
bool is_braces(char c) {
    if ( (c == '{') || (c == '[') || (c == '(') || (c == ')') || (c == ']') || (c == '}') ){
        return true;
    }else{
        return false;
    }
}
// Keywords list
vector<string> keywords = {
    "break",
    "if",
    "else",
    "elif",
    "continue",
    "return",
    "print"
};

// Tokenizer function
vector<Token> tokenizer(string s){
    int cursor=0;
    vector <Token> tokens;  // vector to store tokens
    while(cursor<s.size()){
        string token="";
        // check if the next token is a comment
        if(s[cursor]=='#'){
            token+=s[cursor];
            cursor++;
            while(s[cursor]!='\n'){
                token+=s[cursor];
                cursor++;
            }
            tokens.push_back(Token(token,COMMENT_TOKEN));
        }
        // check if the next token is a string
        else if(s[cursor]=='\"'){
            token+=s[cursor];
            cursor++;
            while(s[cursor]!='\"'){
                token+=s[cursor];
                cursor++;
            }
            token+=s[cursor];
            cursor++;
            tokens.push_back(Token(token,STRING_TOKEN));
        }
        // check if the next token is a char
        else if(s[cursor]=='\''){
            token+=s[cursor];
            cursor++;
            while(s[cursor]!='\''){
                token+=s[cursor];
                cursor++;
            }
            token+=s[cursor];
            cursor++;
            if(token.size()==3){
                tokens.push_back(Token(token,CHAR_TOKEN));
            }
            else{
                tokens.push_back(Token(token,INVALID_TOKEN));
            }
        }
        // check if the next token is a keyword or an identifier
        else if(is_id_start(s[cursor])){
            token+=s[cursor];
            cursor++;
            bool keyword_flag=true;
            while(cursor<s.size()&&is_id(s[cursor])){
                token+=s[cursor];
                cursor++;
            }
            // check if the token is a keyword
            for(int i=0;i<keywords.size();i++){
                if(token==keywords[i]){
                    tokens.push_back(Token(token,KEYWORD_TOKEN));
                    keyword_flag=false;
                    break;
                }
            }
            // check if the token is a boolean
            if((token=="True" || token=="False")){
                tokens.push_back(Token(token,BOOL_TOKEN));
            }
            // if the token is not a keyword, it is an identifier
            else if(keyword_flag){
                tokens.push_back(Token(token,ID_TOKEN));
            }
        }
        //check if the next token is a number
        else if(is_digit_start(s[cursor])){
            token+=s[cursor];
            cursor++;
            while(cursor<s.size()&&is_digit(s[cursor])){
                token+=s[cursor];
                cursor++;
            }
            tokens.push_back(Token(token,NUM_TOKEN));
        }
        // check if the next token is an operator
        else if (is_operator(s[cursor])){
            token+=s[cursor];
            cursor++;
            while(cursor<s.size()&&is_operator(s[cursor])){
                token+=s[cursor];
                cursor++;
            }
            if(token.size()==1 ||  token=="**"){
                tokens.push_back(Token(token,OPERATOR_TOKEN));
            }
            else{
                tokens.push_back(Token(token,INVALID_TOKEN));
            }
        }
        // check if the next token is a compare operator
        else if(is_compare_operator_start(s[cursor])){
            token+=s[cursor];
            cursor++;
            while(cursor<s.size()&&is_compare_operator_start(s[cursor])){
                token+=s[cursor];
                cursor++;
            }
            // check if the token is a compare operator
            if(is_compare_operator(token)){
                tokens.push_back(Token(token,COMPARE_OPERATOR_TOKEN));
            }
            else{
                // check if the token is a not operator
                if(token=="!"){
                    tokens.push_back(Token(token,NOT_TOKEN));
                }
                // check if the token is an equal operator
                else if(token=="="){
                    tokens.push_back(Token(token,EQUAL_TOKEN));
                }
                // if the token is not a compare operator, it is an invalid token
                else tokens.push_back(Token(token,INVALID_TOKEN));
            }
        }
        // check if the next token is a braces
        else if(is_braces(s[cursor])){
            if(s[cursor]=='{'){
                tokens.push_back(Token("{",CURLY_LBRACE_TOKEN));
            }
            else if(s[cursor]=='}'){
                tokens.push_back(Token("}",CURLY_RBRACE_TOKEN));
            }
            else if(s[cursor]=='['){
                tokens.push_back(Token("[",SQUARE_LBRACE_TOKEN));
            }
            else if(s[cursor]==']'){
                tokens.push_back(Token("]",SQUARE_RBRACE_TOKEN));
            }
            else if(s[cursor]=='('){
                tokens.push_back(Token("(",CURVE_LBRACE_TOKEN));
            }
            else if(s[cursor]==')'){
                tokens.push_back(Token(")",CURVE_RBRACE_TOKEN));
            }
            cursor++;
        }
        // check if the next token is a colon
        else if(s[cursor]==':'){
            tokens.push_back(Token(":",COLON_TOKEN));
            cursor++;
        }
        else{
            cursor++;
        }



    }
    return tokens;
}


const char* token_type_str[] = {
    "KEYWORD_TOKEN",
    "CURVE_LBRACE_TOKEN",
    "CURVE_RBRACE_TOKEN",
    "SQUARE_LBRACE_TOKEN",
    "SQUARE_RBRACE_TOKEN",
    "CURLY_LBRACE_TOKEN",
    "CURLY_RBRACE_TOKEN",
    "ID_TOKEN",
    "NUM_TOKEN",
    "OPERATOR_TOKEN",
    "COLON_TOKEN",
    "INVALID_TOKEN",
    "COMPARE_OPERATOR_TOKEN",
    "BOOL_TOKEN",
    "NOT_TOKEN",
    "COMMENT_TOKEN",
    "EQUAL_TOKEN",
    "STRING_TOKEN",
    "CHAR_TOKEN"
};
int main(){
    string s = "x = 10\ny = 20\nz = 30\n\nif x < y:\n    print(\"x is less than y\")\nelif x > y:\n    print(\"x is greater than y\")\nelse:\n    print(\"x is equal to y\")\n\nif y != z:\n    print(\"y is not equal to z\")\n\nif x + y == z:\n    print(\"x plus y is equal to z\")\n\nif z - y > x:\n    print(\"z minus y is greater than x\")\n\nif x * 2 <= y:\n    print(\"x multiplied by 2 is less than or equal to y\")\n\nif z / y >= 1:\n    print(\"z divided by y is greater than or equal to 1\")\n\nif x % 2 == 0:\n    print(\"x is even\")\n\nif y // x == 2:\n    print(\"y floor divided by x is 2\")\n\nif not (x > z):\n    print(\"x is not greater than z\")\n\nif (x < y) and (y < z):\n    print(\"x is less than y and y is less than z\")\n\nif (x > y) or (y < z):\n    print(\"Either x is greater than y or y is less than z\")";

    vector<Token> s2=tokenizer(s);
    for(Token a:s2){
        cout<<a.token_text<<" "<<token_type_str[a.token_type]<<endl;
    }
    return 0;
}