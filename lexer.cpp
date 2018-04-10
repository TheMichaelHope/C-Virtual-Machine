#include "lexer.hpp"

// implement the lexer function here
TokenList tokenize(std::istream & ins)
{
    TokenList my_tokens; //list of tokens
    
    char current_character = 0; //current character being read
    string word; //string to be emplaced
    string placeholder_word;
    
    int lettercount = 0; //character counter
    bool quoted = false; //have you read a '"' and started adding words to the string?
    bool bracketflag = false; //have you read a '('?
    int bracketcounter = 0; //how many '(' have you seen?
    bool quoteprotocol = false; //have you read an opening '"' without reading the corresponding closing '"'?
    bool shadowquoteprotocol = false; //have you read a quote and read another '"' without reading another character?
    
    size_t line = 1; //line counter
    
    while(ins.get(current_character))
    {
        if (current_character == '\n')
        {
            if(!word.empty())
            {
                //if the word has letters in it, emplace it to the tokenlist.
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            //even if it's not empty emplace an EOL token, but if it's the first character, don't.
            if (lettercount != 0)
                my_tokens.emplace_back(Token(EOL, line));
            
            //if there's a quote, then emplace an error message. Strings can't be multiple lines.
            if (quoteprotocol == true)
            {
                my_tokens.emplace_back(Token(ERROR, line, "Error: String spanning multiple lines"));
                break;
            }
            
            //if there's an unpaired bracket, then emplace an error message. Bracketed statements can't be multiple lines.
            if (bracketflag == true || bracketcounter != 0)
            {
                my_tokens.emplace_back(Token(ERROR, line, "Error: Either brackets spanning multiple lines or opened bracket unclosed"));
                break;
            }
            
            //increase the number of lines after you emplace the EOL token
            line++;
            
        }
        else if (isalpha(current_character) || current_character == '.'|| current_character == '$' || current_character == ':' || current_character == '#' || isdigit(current_character) || current_character == '-' || current_character == '/' || current_character == '^' || current_character == '+')
        {
            // if it's an alphabet or a word or . add it to the string
            placeholder_word += current_character;
            lettercount++;
            word = placeholder_word;
        }
        else if (current_character == ',')
        {
            //same as for EOL except you don't increase the numbers of lines
            if(!word.empty())
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            my_tokens.emplace_back(Token(SEP, line));
        }
        else if (current_character == '=')
        {
            //same as for EOL except you don't increase the numbers of lines
            if(!word.empty())
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            my_tokens.emplace_back(Token(EQUAL, line));
        }
        else if (current_character == '(')
        {
            //same as for EOL except you don't increase the numbers of lines
            if(!word.empty())
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            my_tokens.emplace_back(Token(OPEN_PAREN, line));
            bracketflag = true;
            bracketcounter++;
            
        }
        else if (current_character == ')')
        {
            //same as for EOL except you don't increase the numbers of lines
            if(!word.empty() && quoteprotocol == false)
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            
            //if you've read an open bracket then it's to close the bracket and emplace the close bracket.
            if (bracketflag == true)
            {
                if (quoteprotocol == true) //if this isn't a quoted bracket
                {
                    placeholder_word += current_character;
                    lettercount++;
                    word = placeholder_word;
                }
                else
                {
                    my_tokens.emplace_back(Token(CLOSE_PAREN, line));
                    bracketflag = false;
                    bracketcounter--; //make sure that each '(' has a corresponding ')'
                }
            }
            
            else
            {
                my_tokens.emplace_back(Token(ERROR, line, "Error: Unmatched bracket"));
                break;
            }
        }
        else if (current_character == '"')
        {
            //if you've read a first " and you read a second " without reading any new characters, emplace an empty string
            if (quoteprotocol == true && word.empty())
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                shadowquoteprotocol = true;
            }
            
            if(!word.empty())
            {
                my_tokens.emplace_back(Token(STRING, line, word));
                word.clear();
                placeholder_word.clear();
            }
            
            my_tokens.emplace_back(Token(STRING_DELIM, line));
            
            if (shadowquoteprotocol == false) //regular behavior
                quoteprotocol = true;
            
            else if (shadowquoteprotocol == true) //if shadow quote protocol is true then you've successfully emplaced an empty string onto the token list. This resets both quote protocol and shadow quote protocol to the original states.
            {
                shadowquoteprotocol = false;
                quoteprotocol = false;
            }
            
            if (quoteprotocol == true && quoted == true) //this is for when you have successfully read letters in between quotes and it's time to "close" the quotes. Reset quote protocol to it's original state and reset the quote flag to zero.
            {
                quoteprotocol = false;
                quoted = false;
            }
        }
        else if (current_character == ' ')
        {
            //if you see a space and it's not in the quote protocol then you emplace the word and clear the word variable along with its placeholder so you can get ready for the next word
            if (quoteprotocol == false)
            {
                if(!word.empty())
                {
                    my_tokens.emplace_back(Token(STRING, line, word));
                    word.clear();
                    placeholder_word.clear();
                }
            }
            //if you see a space it's in between quotes then you need to add the space to the word
            else if (quoteprotocol == true)
            {
                placeholder_word += current_character;
                lettercount++;
                quoted = true;
                word = placeholder_word;
            }
        }
        else if (current_character == '\t')
        {
            //if you see a space and it's not in the quote protocol then you emplace the word and clear the word variable along with its placeholder so you can get ready for the next word
            if (quoteprotocol == false)
            {
                if(!word.empty())
                {
                    my_tokens.emplace_back(Token(STRING, line, word));
                    word.clear();
                    placeholder_word.clear();
                }
            }
            //if you see a space it's in between quotes then you need to add the space to the word
            else if (quoteprotocol == true)
            {
                placeholder_word += current_character;
                lettercount++;
                quoted = true;
                word = placeholder_word;
            }
        }
    }
    
    //if you get to the end of the file and the last character is an alphabet then you need to emplace the last word, clear the variables and then emplace an EOL token
    if ((ins.eof() && isalpha(current_character)) || (ins.eof() && current_character == '.') || (ins.eof() && current_character == '#') || (ins.eof() && current_character == '$') || (ins.eof() && current_character == ':') || (ins.eof() && isdigit(current_character)) || (ins.eof() && current_character == '-'))
    {
        if(!word.empty())
        {
            my_tokens.emplace_back(Token(STRING, line, word));
            word.clear();
            placeholder_word.clear();
        }
        
        if (quoteprotocol == true)
            my_tokens.emplace_back(Token(ERROR, line, "Error: Unclosed quote"));
        
        if (bracketflag == true)
            my_tokens.emplace_back(Token(ERROR, line, "Error: Unclosed bracket"));
        
        my_tokens.emplace_back(Token(EOL, line));
        line++;
    }
    
    return my_tokens;
}

