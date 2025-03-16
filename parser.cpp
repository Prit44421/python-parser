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
    OPERATOR_TOKEN,             // +,-,/,*,%,** operator token
    COMPARE_OPERATOR_TOKEN,     // ==,>=,<=
    COLON_TOKEN  ,               // : 
    INVALID_TOKEN,              // invalid token
    COMPARE_OPERATOR_TOKEN      // ==,>=,<=,!=
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
// bool is_id_start(char s){
//     if(s=='_'||isalpha(s)) return true;
//     return false;
// }
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
    if ( (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '%')){
        return true;
    }else{
        return false;
    }
}
// check if the character is a compare operator
bool is_compare_operator(string c) {
    if ( (c == "==") || (c == ">=") || (c == "<=") || (c == "!=") ){
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
};

// Tokenizer function
vector<Token> tokenizer(string s){
    int cursor=0;
    vector <Token> tokens;  // vector to store tokens
    while(cursor<s.size()){
        string token="";

        // check if the next token is a keyword or an identifier
        if(is_id(s[cursor])){
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
            // if the token is not a keyword, it is an identifier
            if(keyword_flag){
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
        else if(is_compare_operator_start(s[cursor])){
            token+=s[cursor];
            cursor++;
            while(cursor<s.size()&&is_compare_operator_start(s[cursor])){
                token+=s[cursor];
                cursor++;
            }
            if(is_compare_operator(token)){
                tokens.push_back(Token(token,COMPARE_OPERATOR_TOKEN));
            }
            else{
                tokens.push_back(Token(token,INVALID_TOKEN));
            }
        }
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
        else if(s[cursor]==':'){
            tokens.push_back(Token(":",COLON_TOKEN));
            cursor++;
        }




    }
    return tokens;
}



int main(){
    string s="if 3<5:\n    print(\"hello\")";
    // tokenizer(s);
    return 0;
}