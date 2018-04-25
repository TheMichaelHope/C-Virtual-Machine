#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <list>
#include <bitset>
#include <iomanip>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include "lexer.hpp"
#include "token.hpp"

using namespace std;

class Parser
{
public:
    typedef unordered_map<string, int32_t> RegisterType;
    RegisterType the_registers;
    
    struct MemoryType
    {
        string LABEL = "";
        int OFFSET = 0;
        int labelADDRESS = 0;
        int labelADDRESS_SIZE = 0;
        vector<string> storedINFO;
        string registerINFO = ""; //passed to register when I load word
        int displayedINFO;
    };
    list<MemoryType> the_memory;
    
    MemoryType current_memory;
    
    struct InstructionsType
    {
        string INSTRUCTIONNAME = "";
        string RD = "";
        string RS = "";
        string RT = "";
        string IMMEDIATEVALUE = "";
        int branchID = 0;
    };
    list<InstructionsType> the_instructions;
    
    struct DataLabelsType
    {
        string LABEL = "";
        int ADDRESS_SIZE = 0;
        int ADDRESS = 0;
    };
    vector<DataLabelsType> the_data_labels;
    
    vector<string> the_text_labels;
    
    struct ConstantType
    {
        string NAME = "";
        int VALUE = 0;
    };
    vector<ConstantType> the_constants;
    
    //parser function
    bool parse(TokenList &tokens);
    TokenType taxonomize (TokenList::const_iterator it);
    
    int storageprotocol = 0;
    int regcount = 0;
    int sepcount = 0;
    int parencount = 0;
    int instructioncount = 0;
    bool BRNCHsep = false;
    bool immediateprotocol = false;
    bool storeprotocol = false;
    bool moveprotocol = false;
    bool sepprotocol = false;
    bool stringprotocol = false;
    bool hashprotocol = false;
    bool parenprotocol = false;
    bool jump = false;
    
    enum States {startparsing, dataentry, textentry, MOVEinstruction, ARTHinstruction, LOGinstruction, CTRinstruction, constant, dotword, dothalf, dotbyte, dotspace, dotascii, dotasciiz, END, ERR};
    
    void data_or_text(States & state, TokenType token, TokenList::const_iterator it);
    void data_entry(States & state, TokenType token, TokenList::const_iterator it);
    void text_entry(States & state, TokenType token, TokenList::const_iterator it);
    void MOVE_instruction(States & state, TokenType token, TokenList::const_iterator it);
    void MIPS_instruction(States & state, TokenType token, TokenList::const_iterator it);
    void ARTH_instruction(States & state, TokenType token, TokenList::const_iterator it);
    void LOG_instruction(States & state, TokenType token, TokenList::const_iterator it);
    void CTR_instruction(States & state, TokenType token, TokenList::const_iterator it);
    void data_constant(States & state, TokenType token, TokenList::const_iterator it);
    void dot_word(States & state, TokenType token, TokenList::const_iterator it);
    void dot_half(States & state, TokenType token, TokenList::const_iterator it);
    void dot_byte(States & state, TokenType token, TokenList::const_iterator it);
    void dot_space(States & state, TokenType token, TokenList::const_iterator it);
    void dot_ascii(States & state, TokenType token, TokenList::const_iterator it);
    void dot_asciiz(States & state, TokenType token, TokenList::const_iterator it);
    void data_store(States & state, TokenType token, TokenList::const_iterator it);
    
private:
    InstructionsType current_instruction;
    DataLabelsType current_label;
    
    ConstantType current_constant;
    string current_variable_in_hex;
    
    template< typename T >
    string string_to_hex(T input)
    {
        stringstream stream;
        if (input.size() > 5)
        {
            string binary = string_to_32bin(stoi(input));
            bitset<32> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else
        {
            string binary = string_to_bin(stoi(input));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        
        return stream.str();
    }
    
    string string_to_32bin(int input)
    {
        string binary = "";
        
        int mask = 1;
        
        for(int i = 0; i < 32; i++)
        {
            if (mask & input)
                binary = "1"+binary;
            else
                binary = "0"+binary;
            mask <<= 1;
        }
        return binary;
    }
    
    string string_to_bin(int input)
    {
        string binary = "";
        
        int mask = 1;
        
        for(int i = 0; i < 16; i++)
        {
            if (mask & input)
                binary = "1"+binary;
            else
                binary = "0"+binary;
            mask <<= 1;
        }
        return binary;
    }
};

#endif
