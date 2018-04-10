#ifndef MODULE_HPP
#define MODULE_HPP

#include "parser.hpp"
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class VirtualMachine : public Parser
{
public:
    VirtualMachine();
    void printRegister(string a_reg);
    void printByteAt(string the_addy); //to_do
    void executeProgram();
    void getStatus();
    string numberToRegister(string a_reg);
    
private:
    template< typename T >
    string string_to_hex(T input)
    {
        stringstream stream;
        if (input == "A")
        {
            string binary = string_to_bin(stoi("10"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input == "B")
        {
            string binary = string_to_bin(stoi("11"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input == "C")
        {
            string binary = string_to_bin(stoi("12"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input == "D")
        {
            string binary = string_to_bin(stoi("13"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input == "E")
        {
            string binary = string_to_bin(stoi("14"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input == "F")
        {
            string binary = string_to_bin(stoi("15"));
            bitset<16> set(binary);
            stream << "0x" << setfill ('0') << setw(8) << hex << set.to_ulong();
        }
        else if (input.size() > 5)
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
        //return stoul(binary);
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
        //return stoul(binary);
        return binary;
    }
};


#endif
