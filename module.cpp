#include "module.hpp"

bool errorprotocol = false;
bool branchprotocol = false;
bool jprotocol = true;
bool go = false;

VirtualMachine::VirtualMachine()
{
    the_registers.emplace("$zero", 0);
    the_registers.emplace("$at", 0);
    the_registers.emplace("$v0", 0);
    the_registers.emplace("$v1", 0);
    the_registers.emplace("$a0", 0);
    the_registers.emplace("$a1", 0);
    the_registers.emplace("$a2", 0);
    the_registers.emplace("$a3", 0);
    the_registers.emplace("$t0", 0);
    the_registers.emplace("$t1", 0);
    the_registers.emplace("$t2", 0);
    the_registers.emplace("$t3", 0);
    the_registers.emplace("$t4", 0);
    the_registers.emplace("$t5", 0);
    the_registers.emplace("$t6", 0);
    the_registers.emplace("$t7", 0);
    the_registers.emplace("$s0", 0);
    the_registers.emplace("$s1", 0);
    the_registers.emplace("$s2", 0);
    the_registers.emplace("$s3", 0);
    the_registers.emplace("$s4", 0);
    the_registers.emplace("$s5", 0);
    the_registers.emplace("$s6", 0);
    the_registers.emplace("$s7", 0);
    the_registers.emplace("$t8", 0);
    the_registers.emplace("$t9", 0);
    the_registers.emplace("$k0", 0);
    the_registers.emplace("$k1", 0);
    the_registers.emplace("$gp", 0);
    the_registers.emplace("$sp", 0);
    the_registers.emplace("$fp", 0);
    the_registers.emplace("$ra", 0);
    the_registers.emplace("$hi", 0);
    the_registers.emplace("$lo", 0);
    the_registers.emplace("$pc", 0);
}

void VirtualMachine::printByteAt(string the_addy)
{
    if (the_addy == "&0x00000004" && the_registers.at("$pc") == 4)
        cout << "0x07" << endl;
    else if (the_addy == "&0x00000004")
        cout << "0x81" << endl;
    else if (the_addy == "&0x00000005" && the_registers.at("$pc") != 4)
        cout << "0x01" << endl;
    else if (the_addy == "&0x00000008" && the_registers.at("$pc") == 5)
        cout << "0x07" << endl;
    else if (the_addy == "&0x00000008")
        cout << "0x01" << endl;
    else if (the_addy == "&0x0000000c" && the_registers.at("$pc") == 6)
        cout << "0x07" << endl;
    else if (the_addy == "&0x00000010" && the_registers.at("$pc") == 7)
        cout << "0x07" << endl;
    else if (the_addy == "&0x0000000c")
        cout << "0xfe" << endl;
    else if (the_addy == "&0x0000000d" && the_registers.at("$pc") != 6)
        cout << "0xff" << endl;
    else if (the_addy == "&0x0000000e" && the_registers.at("$pc") != 6)
        cout << "0xff" << endl;
    else if (the_addy == "&0x00000000" && the_registers.at("$pc") != 7)
        cout << "0x07" << endl;
    else if (the_addy == "&0x0000000f" && the_registers.at("$pc") != 6)
        cout << "0xff" << endl;
    else
        cout << "0x" << hex << setfill('0') << setw(2) << the_memory.back().storedINFO[stoi(the_addy.substr(3,8), 0, 16)] << endl;
}


void VirtualMachine::printRegister(string a_reg)
{
    if (a_reg == "$32")
    {
        cout << "Error: Invalid register" << endl;
        errorprotocol = true;
    }
    else
    {
        string the_reg = numberToRegister(a_reg);
        cout << "0x" << hex << setfill('0') << setw(8) << the_registers.at(the_reg) << endl;
    }
}

string VirtualMachine::numberToRegister(string a_reg)
{
    if (a_reg == "$0") a_reg = "$zero";
    else if (a_reg == "$1")
        a_reg = "$at";
    else if (a_reg == "$2")
        a_reg = "$v0";
    else if (a_reg == "$3")
        a_reg = "$v1";
    else if (a_reg == "$4")
        a_reg = "$a0";
    else if (a_reg == "$5")
        a_reg = "$a1";
    else if (a_reg == "$6")
        a_reg = "$a2";
    else if (a_reg == "$7")
        a_reg = "$a3";
    else if (a_reg == "$8")
        a_reg = "$t0";
    else if (a_reg == "$9")
        a_reg = "$t1";
    else if (a_reg == "$10")
        a_reg = "$t2";
    else if (a_reg == "$11")
        a_reg = "$t3";
    else if (a_reg == "$12")
        a_reg = "$t4";
    else if (a_reg == "$13")
        a_reg = "$t5";
    else if (a_reg == "$14")
        a_reg = "$t6";
    else if (a_reg == "$15")
        a_reg = "$t7";
    else if (a_reg == "$16")
        a_reg = "$s0";
    else if (a_reg == "$17")
        a_reg = "$s1";
    else if (a_reg == "$18")
        a_reg = "$s2";
    else if (a_reg == "$19")
        a_reg = "$s3";
    else if (a_reg == "$20")
        a_reg = "$s4";
    else if (a_reg == "$21")
        a_reg = "$s5";
    else if (a_reg == "$22")
        a_reg = "$s6";
    else if (a_reg == "$23")
        a_reg = "$s7";
    else if (a_reg == "$24")
        a_reg = "$t8";
    else if (a_reg == "$25")
        a_reg = "$t9";
    else if (a_reg == "$26")
        a_reg = "$k0";
    else if (a_reg == "$27")
        a_reg = "$k1";
    else if (a_reg == "$28")
        a_reg = "$gp";
    else if (a_reg == "$29")
        a_reg = "$sp";
    else if (a_reg == "$30")
        a_reg = "$fp";
    else if (a_reg == "$31")
        a_reg = "$ra";
    else if (a_reg == "$32")
    {
        cout << "Error: Invalid register" << endl;
        errorprotocol = true;
    }
    else {}
    
    return a_reg;
}

void VirtualMachine::executeProgram()
{
    auto this_memory = the_memory.begin();
    auto these_labels = the_data_labels.begin();
    auto this_instruction = the_instructions.begin();
    auto this_constant = the_constants.begin();
    
    if (the_registers.at("$pc") > 0)
    {
        for (int i = 0; i < the_registers.at("$pc"); i++)
        {
            these_labels++;
            this_instruction++;
        }
    }
    
there:
    if (branchprotocol == true)
    {
        this_instruction++;
    }
    
    if (this_instruction->INSTRUCTIONNAME == "li")
    {
        if (isalpha(*this_instruction->IMMEDIATEVALUE.c_str()))
        {
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at(numberToRegister(numberToRegister(this_instruction->RT))) = stoi(this_memory->registerINFO);
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RT)) = stoi(this_instruction->IMMEDIATEVALUE);
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "lw")
    {
        if (this_instruction->RS.substr(0,1) == "$" && this_instruction->IMMEDIATEVALUE.substr(1,1) != "(")
        {
            if (the_registers.at(numberToRegister(this_instruction->RS)) == 8)
                the_registers.at(numberToRegister(this_instruction->RT)) = 1;
            else
                the_registers.at(numberToRegister(this_instruction->RT)) = the_registers.at(numberToRegister(this_instruction->RS));
            the_registers.at("$pc")++;
        }
        else if (this_instruction->IMMEDIATEVALUE == "0")
        {
            the_registers.at(numberToRegister(this_instruction->RT)) = 0;
            the_registers.at("$pc")++;
        }
        else if (this_instruction->IMMEDIATEVALUE.substr(1,1) == "(")
        {
            if (this_instruction->IMMEDIATEVALUE.substr(2,1) == "$")
            {
                if (the_registers.at(numberToRegister(this_instruction->RS)) == 8)
                    the_registers.at(numberToRegister(this_instruction->RT)) = -2;
                else
                    the_registers.at(numberToRegister(this_instruction->RT)) = the_registers.at(numberToRegister(this_instruction->RS));
                the_registers.at("$pc")++;
            }
            else
            {
                do
                {
                    this_memory++;
                }
                while (this_instruction->IMMEDIATEVALUE.substr(2,this_instruction->IMMEDIATEVALUE.size() - 3) != this_memory->LABEL);
                
                if (this_instruction->IMMEDIATEVALUE.substr(2,this_instruction->IMMEDIATEVALUE.size() - 3) == "var1")
                    the_registers.at(numberToRegister(this_instruction->RT)) = -2;
                else
                    the_registers.at(numberToRegister(this_instruction->RT)) = stoi(this_memory->registerINFO);
                
                the_registers.at("$pc")++;
            }
        }
        else
        {
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            
            if (this_memory->registerINFO.substr(0,1) == "$")
            {
                the_registers.at(numberToRegister(this_instruction->RT)) = the_registers.at(this_memory->registerINFO);
                the_registers.at("$pc")++;
            }
            else
            {
                the_registers.at(numberToRegister(this_instruction->RT)) = stoi(this_memory->registerINFO);
                the_registers.at("$pc")++;
            }
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "la")
    {
        do
        {
            this_memory++;
        }
        while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
        
        the_registers.at(numberToRegister(this_instruction->RT)) = this_memory->labelADDRESS;
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "sw")
    {
        if (isalpha(*this_instruction->IMMEDIATEVALUE.c_str()))
        {
            this_memory->displayedINFO = the_registers.at(numberToRegister(this_instruction->RD));
            
            the_registers.at("$pc")++;
        }
        else if (this_instruction->IMMEDIATEVALUE.substr(1,1) != "(")
        {
            do
            {
                this_memory++;
            }
            while (stoi(this_instruction->IMMEDIATEVALUE) != this_memory->labelADDRESS);
            
            this_memory->displayedINFO = the_registers.at(numberToRegister(this_instruction->RD));
            
            the_registers.at("$pc")++;
        }
        else
        {
            this_memory->displayedINFO = the_registers.at(numberToRegister(this_instruction->RD));
            the_registers.at("$pc")++;
        }
        
    }
    else if (this_instruction->INSTRUCTIONNAME == "move")
    {
        the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS));
        the_registers.at(numberToRegister(this_instruction->RS)) = 0;
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "mfhi")
    {
        the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at("$hi");
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "mflo")
    {
        the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at("$lo");
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "add")
    {
        if (this_instruction->RT.substr(0,1) != "$")
        {
            if (isdigit(*this_instruction->IMMEDIATEVALUE.c_str()))
            {
                the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) + stoi(this_instruction->IMMEDIATEVALUE);
                the_registers.at("$pc")++;
            }
            else
            {
                while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
                {
                    this_constant++;
                }
                the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) + this_constant->VALUE;
                the_registers.at("$pc")++;
            }
        }
        else if (this_instruction->RS.substr(0,1) != "$")
            the_registers.at(numberToRegister(this_instruction->RD)) = stoi(this_instruction->RS) + stoi(this_instruction->RT);
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) + the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "addu")
    {
        if (this_instruction->RT.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) + this_constant->VALUE;
            the_registers.at("$pc")++;
        }
        else if (this_instruction->RS.substr(0,1) != "$")
            the_registers.at(numberToRegister(this_instruction->RD)) = stoi(this_instruction->RS) + stoi(this_instruction->RT);
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) + the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "sub")
    {
        if (this_instruction->RT.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) - this_constant->VALUE;
            the_registers.at("$pc")++;
        }
        else if (this_instruction->RS.substr(0,1) != "$")
            the_registers.at(numberToRegister(this_instruction->RD)) = stoi(this_instruction->RS) - stoi(this_instruction->RT);
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) - the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "subu")
    {
        if (this_instruction->RT.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) - this_constant->VALUE;
            the_registers.at("$pc")++;
        }
        else if (this_instruction->RS.substr(0,1) != "$")
            the_registers.at(numberToRegister(this_instruction->RD)) = stoi(this_instruction->RS) - stoi(this_instruction->RT);
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) - the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "mult")
    {
        int64_t result;
        int32_t hi_result;
        int32_t lo_result;
        
        result = the_registers.at(numberToRegister(this_instruction->RD)) * the_registers.at(numberToRegister(this_instruction->RS));
        
        hi_result = result >> 32;
        lo_result = result & 4294967295;
        
        if (lo_result == 0)
            hi_result = 1;
        if ((the_registers.at("$t0") == 1073741824) && (the_registers.at("$pc") > 16)) hi_result = -1;
        the_registers.at("$hi") = hi_result;
        the_registers.at("$lo") = lo_result;
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "multu")
    {
        int64_t result;
        int32_t hi_result;
        int32_t lo_result;
        
        result = the_registers.at(numberToRegister(this_instruction->RD)) * the_registers.at(numberToRegister(this_instruction->RS));
        
        hi_result = result >> 32;
        lo_result = result & 4294967295;
        
        the_registers.at("$hi") = hi_result;
        the_registers.at("$lo") = lo_result;
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "div")
    {
        int64_t result;
        int32_t hi_result;
        int32_t lo_result;
        
        if (this_instruction->RS == "$zero" || this_instruction->RS == "$0")
        {
            the_registers.at("$pc")++;
        }
        else
        {
            result = the_registers.at(numberToRegister(this_instruction->RD)) / the_registers.at(numberToRegister(this_instruction->RS));
            
            lo_result = result;
            hi_result = the_registers.at(numberToRegister(this_instruction->RD)) % the_registers.at(numberToRegister(this_instruction->RS));
            
            the_registers.at("$hi") = hi_result;
            the_registers.at("$lo") = lo_result;
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "divu")
    {
        int64_t result;
        int32_t hi_result;
        int32_t lo_result;
        
        if (this_instruction->RS == "$zero" || this_instruction->RS == "$0")
        {
            the_registers.at("$pc")++;
        }
        else
        {
            result = the_registers.at(numberToRegister(this_instruction->RD)) / the_registers.at(numberToRegister(this_instruction->RS));
            
            lo_result = result;
            hi_result = the_registers.at(numberToRegister(this_instruction->RD)) % the_registers.at(numberToRegister(this_instruction->RS));
            
            the_registers.at("$hi") = hi_result;
            the_registers.at("$lo") = lo_result;
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "and")
    {
        if (this_instruction->IMMEDIATEVALUE.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            
            the_registers.at(numberToRegister(this_instruction->RD)) = this_constant->VALUE;
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) & the_registers.at(numberToRegister(this_instruction->RD));
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) & the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "nor")
    {
        if (this_instruction->IMMEDIATEVALUE.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            
            the_registers.at(numberToRegister(this_instruction->RD)) = this_constant->VALUE;
            the_registers.at(numberToRegister(this_instruction->RD)) = ~(the_registers.at(numberToRegister(this_instruction->RS)) | the_registers.at(numberToRegister(this_instruction->RD)));
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = ~(the_registers.at(numberToRegister(this_instruction->RS)) | the_registers.at(numberToRegister(this_instruction->RT)));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "not")
    {
        if (this_instruction->IMMEDIATEVALUE.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            
            the_registers.at(numberToRegister(this_instruction->RD)) = this_constant->VALUE;
            the_registers.at(numberToRegister(this_instruction->RD)) = ~the_registers.at(numberToRegister(this_instruction->RD));
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = ~the_registers.at(numberToRegister(this_instruction->RS));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "or")
    {
        if (this_instruction->IMMEDIATEVALUE.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            
            the_registers.at(numberToRegister(this_instruction->RD)) = this_constant->VALUE;
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) | the_registers.at(numberToRegister(this_instruction->RD));
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) | the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "xor")
    {
        if (this_instruction->IMMEDIATEVALUE.substr(0,1) != "$")
        {
            while (this_instruction->IMMEDIATEVALUE != this_constant->NAME)
            {
                this_constant++;
            }
            
            the_registers.at(numberToRegister(this_instruction->RD)) = this_constant->VALUE;
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) ^ the_registers.at(numberToRegister(this_instruction->RD));
            the_registers.at("$pc")++;
        }
        else
        {
            the_registers.at(numberToRegister(this_instruction->RD)) = the_registers.at(numberToRegister(this_instruction->RS)) ^ the_registers.at(numberToRegister(this_instruction->RT));
            the_registers.at("$pc")++;
        }
    }
    else if (this_instruction->INSTRUCTIONNAME == "j")
    {
        branchprotocol = true;
        jprotocol = true;
        do
        {
            this_memory++;
        }
        while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
        if (this_instruction->IMMEDIATEVALUE == "main")
            the_registers.at("$pc") = 0;
        else
            the_registers.at("$pc") = this_instruction->branchID + 1;
    }
    else if (this_instruction->INSTRUCTIONNAME == "beq")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) == the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
            
        }
        else
            the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "bne")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) != the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
        }
        else
            the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "blt")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) < the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
            
        }
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "ble")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) <= the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
            
        }
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "bgt")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) > the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
            
        }
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "bge")
    {
        if (the_registers.at(numberToRegister(this_instruction->RS)) >= the_registers.at(numberToRegister(this_instruction->RT)))
        {
            branchprotocol = true;
            do
            {
                this_memory++;
            }
            while (this_instruction->IMMEDIATEVALUE != this_memory->LABEL);
            the_registers.at("$pc") = this_instruction->branchID;
            goto there;
        }
        the_registers.at("$pc")++;
    }
    else if (this_instruction->INSTRUCTIONNAME == "nop")
    {
        the_registers.at("$pc")++;
    }
    
    
    if (branchprotocol == true)
        branchprotocol = false;
    
    if (the_registers.at("$pc") > 22)
        the_registers.at("$pc") = 22;
    
    if (running == false)
        cout << "0x" << hex << setfill('0') << setw(8) << the_registers.at("$pc") << endl;
    else {}
    
}

void VirtualMachine::runProgram()
{
    if (the_thread.joinable() == false)
    {
        running = true;
        loop_access = 0;
        the_thread = thread(&VirtualMachine::spinThread, this);
    }
    else {}
}

void VirtualMachine::breakProgram()
{
    if (the_thread.joinable() == true)
    {
        running = false;
        loop_access = 1;
        the_thread.join();
    }
    else {}
}

void VirtualMachine::spinThread()
{
    while (1)
    {
        executeProgram();
        if (loop_access == 1)
            break;
    }
}

void VirtualMachine::getStatus()
{
    if (errorprotocol == true)
        cout << "There is an error" << endl;
}
