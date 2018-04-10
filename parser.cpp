#include "parser.hpp"


bool Parser::parse(TokenList &tokens)
{
    States the_state = startparsing; // start in the initial state
    
    auto it = tokens.begin();
    if (tokens.empty() == true)
        the_state = ERR;
    
    while ((the_state != ERR) && (the_state != END) && it != tokens.end())
    {
        // classify input
        TokenType new_token = taxonomize(it);
        
        // next state logic
        switch(the_state)
        {
            case startparsing:
                data_or_text(the_state, new_token, it);
                break;
                
            case dataentry:
                data_entry(the_state, new_token, it);
                break;
                
            case textentry:
                text_entry(the_state, new_token, it);
                break;
                
            case MOVEinstruction:
                MOVE_instruction(the_state, new_token, it);
                break;
                
            case ARTHinstruction:
                ARTH_instruction(the_state, new_token, it);
                break;
                
            case LOGinstruction:
                LOG_instruction(the_state, new_token, it);
                break;
                
            case CTRinstruction:
                CTR_instruction(the_state, new_token, it);
                break;
                
            case dotword:
                dot_word(the_state, new_token, it);
                break;
                
            case dothalf:
                dot_half(the_state, new_token, it);
                break;
                
            case constant:
                data_constant(the_state, new_token, it);
                break;
                
            case dotbyte:
                dot_byte(the_state, new_token, it);
                break;
                
            case dotspace:
                dot_space(the_state, new_token, it);
                break;
                
            case dotascii:
                dot_ascii(the_state, new_token, it);
                break;
                
            case dotasciiz:
                dot_asciiz(the_state, new_token, it);
                break;
                
            default:
                the_state = ERR;
        };
        
        it++;
    }
    
    if (it == tokens.end() && !tokens.empty())
    {
        the_state = END;
    }
    
    
    if (the_state == ERR) return false;
    
    return true;
}

TokenType Parser::taxonomize (TokenList::const_iterator it)
{
    TokenType current_token = EOL;
    
    if (it->type() == EOL)
    {
        current_token = EOL;
    }
    
    else if (it->type() == SEP)
    {
        current_token = SEP;
    }
    
    else if (it->type() == EQUAL)
    {
        current_token = EQUAL;
    }
    
    else if (it->type() == OPEN_PAREN)
    {
        current_token = OPEN_PAREN;
    }
    
    else if (it->type() == CLOSE_PAREN)
    {
        current_token = CLOSE_PAREN;
    }
    
    else if (it->type() == STRING_DELIM)
    {
        current_token = STRING_DELIM;
    }
    
    else if (it->type() == STRING)
    {
        current_token = STRING;
    }
    
    else if (it->type() == ERROR)
    {
        current_token = ERROR;
    }
    
    return current_token;
}

void Parser::data_or_text(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            if (it->value() == ".data")
            {
                state = dataentry;
            }
            
            else if (it->value() == ".text")
            {
                state = textentry;
            }
            
            else
                state = startparsing;
            break;
            
        case EOL:
            state = startparsing;
            break;
            
        default:
            state = ERR;
    };
}

void Parser::data_entry(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case EQUAL:
            
            if (hashprotocol == true)
            {
                state = dataentry;
                break;
            }
            
        case STRING:
            
            if (hashprotocol == true)
            {
                state = dataentry;
                break;
            }
            
            if (it->value().at(it->value().length()-1) == ':')
            {
                current_label.LABEL = it->value().substr(0, it->value().length()-1);
                current_memory.LABEL = current_label.LABEL;
                state = dataentry;
                break;
            }
            
            if (isalpha(*it->value().substr(0,1).c_str()))
            {
                current_constant.NAME = it->value();
                the_text_labels.emplace_back(it->value());
                current_memory.LABEL = current_constant.NAME;
                state = constant;
            }
            
            else if (it->value() == ".word")
                state = dotword;
            
            else if (it->value() == ".half")
                state = dothalf;
            
            else if (it->value() == ".byte")
                state = dotbyte;
            
            else if (it->value() == ".space")
                state = dotspace;
            
            else if (it->value() == ".ascii")
                state = dotascii;
            
            else if (it->value() == ".asciiz")
                state = dotasciiz;
            
            else if (it->value() == ".text")
                state = textentry;
            
            break;
            
        case EOL:
            if (hashprotocol == true)
                hashprotocol = false;
            state = dataentry;
            break;
            
        case ERROR:
            state = dataentry;
            break;
            
        default:
            state = ERR;
    };
    
}

void Parser::text_entry(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case EQUAL:
            
            if (hashprotocol == true)
            {
                state = textentry;
                break;
            }
            
        case OPEN_PAREN:
            
            if (hashprotocol == true)
            {
                state = textentry;
                break;
            }
            
        case CLOSE_PAREN:
            
            if (hashprotocol == true)
            {
                state = textentry;
                break;
            }
            
        case STRING:
            if (hashprotocol == true)
            {
                state = textentry;
                break;
            }
            
            if (it->value().at(it->value().length()-1) == ':')
            {
                current_label.LABEL = it->value().substr(0, it->value().size() - 1);
                the_text_labels.emplace_back(it->value());
                current_memory.LABEL = current_label.LABEL;
                if (it->value() != "main:")
                {
                    current_instruction.IMMEDIATEVALUE = it->value().substr(0, it->value().size() - 1);
                }
                state = textentry;
                break;
            }
            
            else if (it->value() == "lw" ||
                     it->value() == "la" ||
                     it->value() == "sw" ||
                     it->value() == "sh" ||
                     it->value() == "sb")
            {
                if (it->value() == "sw" || it->value() == "sh" || it->value() == "sb")
                    storeprotocol = true;
                current_instruction.INSTRUCTIONNAME = it->value();
                state = MOVEinstruction;
                break;
            }
            
            else if (it->value() == "li")
            {
                immediateprotocol = true;
                current_instruction.INSTRUCTIONNAME = it->value();
                state = MOVEinstruction;
                break;
            }
            
            else if (it->value() == "move" ||
                     it->value() == "mfhi" ||
                     it->value() == "mflo")
            {
                moveprotocol = true;
                current_instruction.INSTRUCTIONNAME = it->value();
                state = MOVEinstruction;
                break;
            }
            
            else if (it->value() == "add" ||
                     it->value() == "addu" ||
                     it->value() == "sub" ||
                     it->value() == "subu" ||
                     it->value() == "mult" ||
                     it->value() == "multu" ||
                     it->value() == "div" ||
                     it->value() == "divu")
            {
                current_instruction.INSTRUCTIONNAME = it->value();
                state = ARTHinstruction;
                break;
            }
            
            else if (it->value() == "and" ||
                     it->value() == "or" ||
                     it->value() == "not" ||
                     it->value() == "nor" ||
                     it->value() == "xor")
            {
                current_instruction.INSTRUCTIONNAME = it->value();
                state = LOGinstruction;
                break;
            }
            
            else if (it->value() == "beq" ||
                     it->value() == "bne" ||
                     it->value() == "blt" ||
                     it->value() == "ble" ||
                     it->value() == "bgt" ||
                     it->value() == "bge")
            {
                BRNCHsep = true;
                current_instruction.INSTRUCTIONNAME = it->value();
                state = CTRinstruction;
                break;
            }
            else if (it->value() == "j")
            {
                BRNCHsep = true;
                jump = true;
                current_instruction.INSTRUCTIONNAME = it->value();
                state = CTRinstruction;
                break;
            }
            
            else if (it->value() == "nop")
            {
                instructioncount++;
                current_instruction.branchID = instructioncount;
                current_instruction.INSTRUCTIONNAME = it->value();
                the_instructions.emplace_back(current_instruction);
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                the_memory.emplace_back(current_memory);
                state = textentry;
                break;
            }
            
        case EOL:
            if (hashprotocol == true)
                hashprotocol = false;
            state = textentry;
            break;
            
        default:
            state = ERR;
    }
}

void Parser::MOVE_instruction(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            if (it->value() == "#")
            {
                hashprotocol = true;
                if (parenprotocol == true && parencount != 0)
                    state = ERR;
                else
                {
                    sepcount = 0;
                    the_instructions.emplace_back(current_instruction);
                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                    else current_label.ADDRESS = 0;
                    
                    current_label.ADDRESS_SIZE = 4;
                    
                    current_memory.labelADDRESS = current_label.ADDRESS;
                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                    the_memory.emplace_back(current_memory);
                    state = textentry;
                    immediateprotocol = false;
                    break;
                }
            }
            if (it->value().substr(0,1) == "$" && sepcount > 1)
                state = ERR;
            else
            {
                
                if (immediateprotocol == true)
                {
                    if (it->value().substr(0,1) == "$")
                    {
                        current_instruction.RT = it->value();
                        state = MOVEinstruction;
                    }
                    else if (it->value().substr(0,1) != "$" || isdigit(*it->value().c_str()))
                    {
                        current_instruction.IMMEDIATEVALUE = it->value();
                        //current_variable_in_hex = string_to_hex(it->value());
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else
                        state = ERR;
                }
                else if (moveprotocol == true)
                {
                    if (it->value().substr(0,1) == "$")
                    {
                        if (sepcount == 0)
                        {
                            current_instruction.RD = it->value();
                            //current_variable_in_hex = string_to_hex(it->value());
                            state = MOVEinstruction;
                        }
                        else if (sepcount == 1)
                        {
                            current_instruction.RS = it->value();
                            //current_variable_in_hex = string_to_hex(it->value());
                            state = MOVEinstruction;
                        }
                    }
                    else
                        state = ERR;
                }
                else if (storeprotocol == true)
                {
                    if (it->value().substr(0,1) == "$" && parenprotocol == false)
                    {
                        if (sepcount == 0)
                        {
                            current_instruction.RD = it->value();
                            state = MOVEinstruction;
                        }
                        else if (sepcount == 1)
                        {
                            current_instruction.RS = it->value();
                            state = MOVEinstruction;
                        }
                    }
                    else if (it->value().substr(0,1) == "$" && parenprotocol == true)
                    {
                        current_instruction.IMMEDIATEVALUE = it->value();
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else if (isdigit(*it->value().c_str()) && parenprotocol == false)
                    {
                        current_instruction.IMMEDIATEVALUE = it->value();
                        current_memory.OFFSET = stoi(it->value());
                        state = MOVEinstruction;
                    }
                    else if (isdigit(*it->value().c_str()) && parenprotocol == true)
                    {
                        current_instruction.IMMEDIATEVALUE = it->value();
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else
                        state = ERR;
                }
                else
                {
                    if (it->value().substr(0,1) == "$" && parenprotocol == false)
                    {
                        if (sepcount == 0)
                            current_instruction.RT = it->value();
                        else if (sepcount > 0)
                        {
                            current_instruction.RS = it->value();
                            current_memory.registerINFO = it->value();
                        }
                        state = MOVEinstruction;
                    }
                    else if ((it->value().substr(0,1) == "$" || isdigit(*it->value().c_str())) && parenprotocol == true)
                    {
                        current_instruction.IMMEDIATEVALUE = current_instruction.IMMEDIATEVALUE + "(" + it->value() + ")";
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else if (isdigit(*it->value().c_str()) && parenprotocol == false)
                    {
                        current_instruction.IMMEDIATEVALUE = it->value();
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else if (isalpha(*it->value().c_str()) && parenprotocol == false)
                    {
                        current_instruction.RS = "";
                        current_instruction.IMMEDIATEVALUE = it->value();
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else if ((it->value().substr(0,1) != "$" || isdigit(*it->value().c_str())) && parenprotocol == true)
                    {
                        current_instruction.IMMEDIATEVALUE = current_instruction.IMMEDIATEVALUE + "(" + it->value() + ")";
                        current_memory.registerINFO = it->value();
                        state = MOVEinstruction;
                    }
                    else
                        state = ERR;
                }
            }
            break;
            
        case SEP:
            sepprotocol = true;
            sepcount++;
            state = MOVEinstruction;
            break;
            
        case OPEN_PAREN:
            parenprotocol = true;
            parencount++;
            state = MOVEinstruction;
            break;
            
        case CLOSE_PAREN:
            if (parenprotocol == true)
            {
                parenprotocol = false;
                parencount--;
                state = CTRinstruction;
            }
            else
                state = ERR;
            break;
            
        case EOL:
            if (parenprotocol == true && parencount != 0)
                state = ERR;
            else
            {
                sepcount = 0;
                instructioncount++;
                current_instruction.branchID = instructioncount;
                the_instructions.emplace_back(current_instruction);
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                the_memory.emplace_back(current_memory);
                state = textentry;
                immediateprotocol = false;
                if (moveprotocol == true)
                    moveprotocol = false;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::ARTH_instruction(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            if (it->value() == "#")
            {
                hashprotocol = true;
                if (parenprotocol == true && parencount != 0)
                    state = ERR;
                else
                {
                    sepcount = 0;
                    the_instructions.emplace_back(current_instruction);
                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                    else current_label.ADDRESS = 0;
                    
                    current_label.ADDRESS_SIZE = 4;
                    
                    current_memory.labelADDRESS = current_label.ADDRESS;
                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                    the_memory.emplace_back(current_memory);
                    state = textentry;
                    immediateprotocol = false;
                    break;
                }
            }
            if (it->value().substr(0,1) == "$")
            {
                if (sepcount == 0)
                {
                    current_instruction.RD = it->value();
                    state = ARTHinstruction;
                }
                
                else if (sepcount == 1)
                {
                    current_instruction.RS = it->value();
                    state = ARTHinstruction;
                }
                
                else if (sepcount == 2)
                {
                    current_instruction.RT = it->value();
                    state = ARTHinstruction;
                }
                
            }
            else if ((isdigit(*it->value().c_str()) && sepcount == 2) || (isalpha(*it->value().c_str()) && sepcount == 2))
            {
                current_instruction.RT = it->value();
                current_instruction.IMMEDIATEVALUE = it->value();
                state = ARTHinstruction;
            }
            break;
            
        case SEP:
            state = ARTHinstruction;
            sepcount++;
            break;
            
        case OPEN_PAREN:
            parenprotocol = true;
            parencount++;
            state = ARTHinstruction;
            break;
            
        case CLOSE_PAREN:
            if (parenprotocol == true)
            {
                parencount--;
                parenprotocol = false;
                state = ARTHinstruction;
            }
            else
                state = ERR;
            break;
            
        case EOL:
            if (parenprotocol == true && parencount != 0)
                state = ERR;
            else
            {
                sepcount = 0;
                instructioncount++;
                current_instruction.branchID = instructioncount;
                the_instructions.emplace_back(current_instruction);
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                the_memory.emplace_back(current_memory);
                state = textentry;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::LOG_instruction(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
//            if (it->value() == "#")
//            {
//                hashprotocol = true;
//                if (parenprotocol == true && parencount != 0)
//                    state = ERR;
//                else
//                {
//                    sepcount = 0;
//                    the_instructions.emplace_back(current_instruction);
//                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                    else current_label.ADDRESS = 0;
//                    
//                    current_label.ADDRESS_SIZE = 4;
//                    
//                    current_memory.labelADDRESS = current_label.ADDRESS;
//                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//                    the_memory.emplace_back(current_memory);
//                    state = textentry;
//                    immediateprotocol = false;
//                    break;
//                }
//            }
            if (it->value().substr(0,1) == "$")
            {
                if (sepcount == 0)
                {
                    current_instruction.RD = it->value();
                    current_instruction.IMMEDIATEVALUE = it->value();
                    state = LOGinstruction;
                }
                
                else if (sepcount == 1)
                {
                    current_instruction.RS = it->value();
                    current_instruction.IMMEDIATEVALUE = it->value();
                    state = LOGinstruction;
                }
                
                else if (sepcount == 2)
                {
                    current_instruction.RT = it->value();
                    current_instruction.IMMEDIATEVALUE = it->value();
                    state = LOGinstruction;
                }
                
            }
            else if (it->value().substr(0,1) != "$" || isalpha(*it->value().c_str()))
            {
                current_memory.registerINFO = it->value();
                current_instruction.IMMEDIATEVALUE = it->value();
                state = LOGinstruction;
            }
            else if (isdigit(*it->value().substr(1,it->value().length()-1).c_str()))
                state = ERR;
            
            break;
            
        case SEP:
            state = LOGinstruction;
            sepcount++;
            break;
            
        case OPEN_PAREN:
            parencount++;
            parenprotocol = true;
            state = LOGinstruction;
            break;
            
        case CLOSE_PAREN:
            if (parenprotocol == true)
            {
                parencount--;
                parenprotocol = false;
                state = LOGinstruction;
            }
            else
                state = ERR;
            break;
            
        case EOL:
            if (parenprotocol == true && parencount != 0)
                state = ERR;
            else
            {
                sepcount = 0;
                instructioncount++;
                current_instruction.branchID = instructioncount;
                the_instructions.emplace_back(current_instruction);
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                the_memory.emplace_back(current_memory);
                state = textentry;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::CTR_instruction(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
//            if (it->value() == "#")
//            {
//                hashprotocol = true;
//                if (parenprotocol == true && parencount != 0)
//                    state = ERR;
//                else
//                {
//                    sepcount = 0;
//                    the_instructions.emplace_back(current_instruction);
//                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                    else current_label.ADDRESS = 0;
//
//                    current_label.ADDRESS_SIZE = 4;
//
//                    current_memory.labelADDRESS = current_label.ADDRESS;
//                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//                    the_memory.emplace_back(current_memory);
//                    state = textentry;
//                    immediateprotocol = false;
//                    break;
//                }
//            }
            if (jump == true)
            {
                if (isalpha(*it->value().c_str()) && sepcount == 0)
                {
                    current_instruction.IMMEDIATEVALUE = it->value();
                    the_text_labels.emplace_back(it->value());
                    state = CTRinstruction;
                }
                else
                    state = ERR;
            }
            else
            {
                if (it->value().substr(0,1) == "$")
                {
                    if (sepcount == 0)
                    {
                        current_instruction.RS = it->value();
                        state = CTRinstruction;
                    }
                    
                    else if (sepcount == 1)
                    {
                        current_instruction.RT = it->value();
                        state = CTRinstruction;
                    }
                }
                else if (isalpha(*it->value().c_str()))
                {
                    if (sepcount < 2)
                        state = ERR;
                    else
                    {
                        sepcount = 0;
                        the_text_labels.emplace_back(it->value());
                        current_memory.LABEL = it->value();
                        current_instruction.IMMEDIATEVALUE = it->value();
                        state = CTRinstruction;
                    }
                }
            }
            break;
            
        case SEP:
            sepcount++;
            state = CTRinstruction;
            break;
            
        case OPEN_PAREN:
            parencount++;
            parenprotocol = true;
            state = CTRinstruction;
            break;
            
        case CLOSE_PAREN:
            if (parenprotocol == true)
            {
                parencount--;
                parenprotocol = false;
                state = CTRinstruction;
            }
            else
                state = ERR;
            break;
            
            
        case EOL:
            if (parenprotocol == false && parencount != 0)
                state = ERR;
            else
            {
                sepcount = 0;
                instructioncount++;
                current_instruction.branchID = instructioncount;
                the_instructions.emplace_back(current_instruction);
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                the_memory.emplace_back(current_memory);
                state = textentry;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::data_constant(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case EQUAL:
            state = constant;
            break;
            
        case STRING:
//            if (it->value() == "#")
//            {
//                hashprotocol = true;
//                if (parenprotocol == true && parencount != 0)
//                    state = ERR;
//                else
//                {
//                    sepcount = 0;
//                    the_instructions.emplace_back(current_instruction);
//                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                    else current_label.ADDRESS = 0;
//
//                    current_label.ADDRESS_SIZE = 4;
//
//                    current_memory.labelADDRESS = current_label.ADDRESS;
//                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//                    the_memory.emplace_back(current_memory);
//                    state = dataentry;
//                    immediateprotocol = false;
//                    break;
//                }
//            }
            if (it->value().substr(0, 1) == "+" || it->value().substr(0, 1) == "-" || it->value().substr(0, 1) == "{" || it->value().substr(0, 1) == "}")
            {
                if (it->value().substr(0, 1) == "-")
                    current_constant.VALUE = stoi(it->value());
                else
                    current_constant.VALUE = stoi(it->value().substr(1, it->value().size() - 1));
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(4,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(2,2));
                
                current_memory.registerINFO = it->value();
                state = constant;
            }
            else if (isdigit(*it->value().c_str()) && stoi(it->value().c_str()) < 2147483647)
            {
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(4,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(2,2));
                
                current_constant.VALUE = stoi(it->value());
                
                current_memory.registerINFO = it->value();
                state = constant;
            }
            else if (isalpha(*it->value().c_str()))
            {
                state = constant;
            }
            else
                state = ERR;
            break;
            
        case SEP:
            state = constant;
            break;
            
        case EOL:
        {
            the_constants.emplace_back(current_constant);
            the_data_labels.emplace_back(current_label);
            the_memory.emplace_back(current_memory);
            storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            state = dataentry;
        }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::dot_word(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            stringprotocol = true;
            if (it->value() == "#")
            {
                hashprotocol = true;
                if (parenprotocol == true && parencount != 0)
                    state = ERR;
                else
                {
                    sepcount = 0;
                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                    else current_label.ADDRESS = 0;
                    
                    current_label.ADDRESS_SIZE = 4;
                    
                    current_memory.labelADDRESS = current_label.ADDRESS;
                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                    the_memory.emplace_back(current_memory);
                    state = dataentry;
                    immediateprotocol = false;
                    break;
                }
            }
            
            if (it->value().substr(0, 1) == "+" || it->value().substr(0, 1) == "-")
            {
                sepprotocol = false;
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(4,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(2,2));
                
                current_memory.registerINFO = it->value();
                
                state = dotword;
            }
            
            else if (isdigit(*it->value().c_str()) && stol(it->value().c_str()) < 2147483647)
            {
                sepprotocol = false;
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 4;
                
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(4,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(2,2));
                
                current_memory.registerINFO = it->value();
                
                state = dotword;
            }
            
            else if (isalpha(*it->value().c_str()) && sepcount == 2)
            {
                state = dotword;
            }
            
            else if (it->value().substr(0, 1) == "#")
            {
                sepprotocol = false;
                state = constant;
            }
            
            else
                state = ERR;
            break;
            
        case SEP:
            sepprotocol = true;
            the_data_labels.emplace_back(current_label);
            the_memory.emplace_back(current_memory);
            state = dotword;
            storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            break;
            
        case EOL:
            if (sepprotocol == true || stringprotocol == false)
                state = ERR;
            else
            {
                the_data_labels.emplace_back(current_label);
                the_memory.emplace_back(current_memory);
                state = dataentry;
                storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::dot_half(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            stringprotocol = true;
//            if (it->value() == "#")
//            {
//                hashprotocol = true;
//                if (parenprotocol == true && parencount != 0)
//                    state = ERR;
//                else
//                {
//                    sepcount = 0;
//                    the_instructions.emplace_back(current_instruction);
//                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                    else current_label.ADDRESS = 0;
//
//                    current_label.ADDRESS_SIZE = 4;
//
//                    current_memory.labelADDRESS = current_label.ADDRESS;
//                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//                    the_memory.emplace_back(current_memory);
//                    state = dataentry;
//                    immediateprotocol = false;
//                    break;
//                }
//            }
//            if (it->value().substr(0, 1) == "+" || it->value().substr(0, 1) == "-")
//            {
//                sepprotocol = false;
//
//                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                else current_label.ADDRESS = 0;
//
//                current_label.ADDRESS_SIZE = 2;
//
//                current_memory.labelADDRESS = current_label.ADDRESS;
//                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//
//                current_variable_in_hex = string_to_hex(it->value());
//
//                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
//                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
//
//                current_memory.registerINFO = it->value();
//
//                state = dothalf;
//            }
            
            if (isdigit(*it->value().c_str()) && stoi(it->value().c_str()) < 32768)
            {
                sepprotocol = false;
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 2;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                
                current_memory.registerINFO = it->value();
                
                state = dothalf;
            }
            
            else if (it->value().substr(0, 1) == "#")
            {
                sepprotocol = false;
                state = constant;
            }
            
            else
                state = ERR;
            break;
            
        case SEP:
            sepprotocol = true;
            the_data_labels.emplace_back(current_label);
            the_memory.emplace_back(current_memory);
            state = dothalf;
            storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            break;
            
        case EOL:
            if (sepprotocol == true || stringprotocol == false)
                state = ERR;
            else
            {
                the_data_labels.emplace_back(current_label);
                the_memory.emplace_back(current_memory);
                state = dataentry;
                storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            }
            break;
            
        default:
            state = ERR;
    }
    
}

void Parser::dot_byte(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
//            if (it->value() == "#")
//            {
//                hashprotocol = true;
//                if (parenprotocol == true && parencount != 0)
//                    state = ERR;
//                else
//                {
//                    sepcount = 0;
//                    the_instructions.emplace_back(current_instruction);
//                    if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                    else current_label.ADDRESS = 0;
//
//                    current_label.ADDRESS_SIZE = 4;
//
//                    current_memory.labelADDRESS = current_label.ADDRESS;
//                    current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//                    the_memory.emplace_back(current_memory);
//                    state = dataentry;
//                    immediateprotocol = false;
//                    break;
//                }
//            }
//            stringprotocol = true;
//
//            if (it->value().substr(0, 1) == "+" || it->value().substr(0, 1) == "-")
//            {
//                sepprotocol = false;
//
//                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
//                else current_label.ADDRESS = 0;
//
//                current_label.ADDRESS_SIZE = 1;
//
//                current_memory.labelADDRESS = current_label.ADDRESS;
//                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
//
//                current_variable_in_hex = string_to_hex(it->value());
//
//
//                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
//
//                current_memory.registerINFO = it->value();
//
//                state = dotbyte;
//            }
            
            if (isdigit(*it->value().c_str()) && stoi(it->value().c_str()) < 255)
            {
                sepprotocol = false;
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = 1;
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                
                current_memory.registerINFO = it->value();
                
                state = dotbyte;
            }
            
            else if (it->value().substr(0, 1) == "#")
            {
                sepprotocol = false;
                state = constant;
            }
            
            else
                state = ERR;
            break;
            
        case SEP:
            sepprotocol = true;
            the_data_labels.emplace_back(current_label);
            the_memory.emplace_back(current_memory);
            state = dotbyte;
            storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            break;
            
        case EOL:
            if (sepprotocol == true || stringprotocol == false)
                state = ERR;
            else
            {
                the_data_labels.emplace_back(current_label);
                the_memory.emplace_back(current_memory);
                state = dataentry;
                storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            }
            break;
            
        default:
            state = ERR;
    }
    
}

void Parser::dot_space(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            stringprotocol = true;
            if (isdigit(*it->value().c_str()) && stoi(it->value().c_str()) < 2147483647)
            {
                sepprotocol = false;
                
                if (storageprotocol > 0) current_label.ADDRESS = storageprotocol;
                else current_label.ADDRESS = 0;
                
                current_label.ADDRESS_SIZE = stol(it->value());
                
                current_memory.labelADDRESS = current_label.ADDRESS;
                current_memory.labelADDRESS_SIZE = current_label.ADDRESS_SIZE;
                
                current_variable_in_hex = string_to_hex(it->value());
                
                int bytecount = stoi(it->value())/4;
                
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(8,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(6,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(4,2));
                current_memory.storedINFO.emplace_back(current_variable_in_hex.substr(2,2));
                
                for (int i = 0; i < bytecount; i++)
                {
                    current_memory.storedINFO.emplace_back("");
                    current_memory.storedINFO.emplace_back("");
                    current_memory.storedINFO.emplace_back("");
                    current_memory.storedINFO.emplace_back("");
                }
                
                current_memory.registerINFO = it->value();
                
                state = dotspace;
            }
            
            else
                state = dotspace;
            break;
            
        case EOL:
            if (sepprotocol == true || stringprotocol == false)
                state = ERR;
            else
            {
                the_data_labels.emplace_back(current_label);
                the_memory.emplace_back(current_memory);
                state = dataentry;
                storageprotocol = storageprotocol + current_label.ADDRESS_SIZE;
            }
            break;
            
        default:
            state = ERR;
    }
}

void Parser::dot_ascii(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            if (isdigit(*it->value().c_str()))
            {
                storageprotocol = 5;
                state = ERR;
            }
            else
                state = dotascii;
            break;
            
        case STRING_DELIM:
            state = dotascii;
            break;
            
        case EOL:
            state = dataentry;
            break;
            
        default:
            state = ERR;
    }
}

void Parser::dot_asciiz(States & state, TokenType token, TokenList::const_iterator it)
{
    switch(token)
    {
        case STRING:
            if (isdigit(*it->value().c_str()))
            {
                storageprotocol = 5;
                state = ERR;
            }
            else
                state = dotasciiz;
            break;
            
        case STRING_DELIM:
            state = dotasciiz;
            break;
            
        case EOL:
            state = dataentry;
            break;
            
        case ERROR:
            state = dataentry;
            break;
            
        default:
            state = ERR;
    }
}
