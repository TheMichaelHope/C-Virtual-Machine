#include "catch.hpp"

#include "parser.hpp"
#include "module.hpp"

#include <string>
#include <sstream>
#include <map>

TEST_CASE( "test li", "[module]" )
{
    {
        std::string input = ".data\nx: .word 30\ny: .half 15\n z: .byte 7\n.text\nmain:\nli $t0 7\nli $t1 8\nli $t2 25";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.printRegister("$t0");
        parser.printRegister("$t1");
        parser.printRegister("$t2");
        parser.executeProgram();
        parser.printRegister("$t0");
        parser.executeProgram();
        parser.printRegister("$t1");
        parser.executeProgram();
        parser.printRegister("$t2");
        parser.printByteAt("0x00000001");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test li with aliases", "[module]" )
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        li $0, 1
        li $1, 1
        li $2, 1
        li $3, 1
        li $4, 1
        li $5, 1
        li $6, 1
        li $7, 1
        li $8, 1
        li $9, 1
        li $10, 1
        li $11, 1
        li $12, 1
        li $13, 1
        li $14, 1
        li $15, 1
        li $16, 1
        li $17, 1
        li $18, 1
        li $19, 1
        li $20, 1
        li $21, 1
        li $22, 1
        li $23, 1
        li $24, 1
        li $25, 1
        li $26, 1
        li $27, 1
        li $28, 1
        li $29, 1
        li $30, 1
        li $31, 1
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.printByteAt("0x00000001");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test moves", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        move $t1, $t0
        mfhi $t8
        mflo $t8
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test adds", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        add $t1, $t0, $t2
        add $t1, $t0, 1
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test addus", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        addu $t1, $t0, $t2
        addu $t1, $t0, 1
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}


TEST_CASE("test subs", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        sub $t1, $t0, $t2
        sub $t1, $t0, 1
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test subus", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        subu $t1, $t0, $t2
        subu $t1, $t0, 1
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test mults", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        mult $t1, $t0
        mult $t1, $t0
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test multus", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        multu $t1, $t0
        multu $t1, $t0
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test divs", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        li $t1, 30
        li $t0, 15
        div $t1, $t0
        div $t1, $t0
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test divus", "[module]")
{
    {
        std::string input = R"(.data
    x: .word 30
    y: .half 15
    z: .byte 7
        .text
    main:
        li $t1, 30
        li $t0, 15
        divu $t1, $t0
        divu $t1, $t0
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test and", "[module]")
{
    {
        std::string input = R"(.data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        and $t2, $t0, $t1
        and $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test or", "[module]")
{
    {
        std::string input = R"(.data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        or $t2, $t0, $t1
        or $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test xor", "[module]")
{
    {
        std::string input = R"(.data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        xor $t2, $t0, $t1
        xor $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test nor", "[module]")
{
    {
        std::string input = R"(.data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        nor $t2, $t0, $t1
        nor $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test not", "[module]")
{
    {
        std::string input = R"(.data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        not $t2, $t1
        not $t2, VALUE
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test la", "[module]")
{
    {
        std::string input = ".data\nx: .word 12\n.text\nmain:\nla $t0, x";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.printRegister("$t0");
        parser.executeProgram();
        parser.printRegister("$t0");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE("test li with constants", "[module]")
{
    {
        std::string input = ".data\nA = 0\nB = 1\nC = 2\n.text\nmain:\nli $t0 100\nli $t1 A\nli $t2 B\nli $t3 C";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.printRegister("$t0");
        parser.printRegister("$t1");
        parser.printRegister("$t2");
        parser.printRegister("$t3");
        parser.printRegister("$t0");
        parser.executeProgram();
        parser.printRegister("$t1");
        parser.executeProgram();
        parser.printRegister("$t2");
        parser.executeProgram();
        parser.printRegister("$t3");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test lw and add", "[module]" )
{
    {
        std::string input = ".data\nx: .word 30\ny: .half 15\n z: .byte 7\n.text\nmain:\nlw $t0 x\nadd $t1, $t6, $t0\nadd $t2, $t1, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.printRegister("$t0");
        parser.printRegister("$t1");
        parser.printRegister("$t2");
        parser.executeProgram();
        parser.printRegister("$t0");
        parser.executeProgram();
        parser.printRegister("$t1");
        parser.executeProgram();
        parser.printRegister("$t2");
        parser.printByteAt("0x00000001");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test j", "[module]" )
{
    {
        std::string input = ".data\nx: .word 30\ny: .half 15\n z: .byte 7\n.text\nmain:\nlw $t0 x\naddition:\nadd $t1, $t6, $t0\nj addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nx: .word 30\ny: .half 15\n z: .byte 7\n.text\nmain:\nlw $t0 x\naddition:\nadd $t1, $t6, $t0\nj main\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test branches", "[module]" )
{
    {
        std::string input = ".data\nx: .word 15\ny: .half 15\n.text\nmain:\nli $t0 100\nli $t1 100\naddition:\nadd $t2, $t6, $t0\nbeq $t0, $t1, addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nx: .word 14\ny: .half 15\n.text\nmain:\nli $t0 101\nli $t1 100\naddition:\nadd $t2, $t6, $t0\nblt $t0, $t1, addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nx: .word 15\ny: .half 15\n.text\nmain:\nli $t0 101\nli $t1 100\naddition:\nadd $t2, $t6, $t0\nble $t0, $t1, addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nx: .word 16\ny: .half 15\n.text\nmain:\nli $t0 99\nli $t1 100\naddition:\nadd $t2, $t6, $t0\nbgt $t0, $t1, addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nx: .word 15\ny: .half 15\n.text\nmain:\nli $t0 99\nli $t1 100\naddition:\nadd $t2, $t6, $t0\nbge $t0, $t1, addition1\naddition1:\nadd $t2, $t6, $t0";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(.data
    var0:   .word 0
    var1:   .word 1
    var2:   .word 2
    var3:   .word 3
        .text
    main:
        lw $t0, var0
        lw $t1, var1
        lw $t2, var2
        lw $t3, var3
        
        beq $t0, $t1, check1
        beq $t0, $t0, check1
        nop
    check1:
        bne $t0, $t0, check2
        bne $t0, $t1, check2
        nop
    check2:
        bgt $t0, $t0, check3
        bgt $t3, $t1, check3
        nop
    check3:
        bge $t0, $t1, check4
        bge $t3, $t2, check4
        nop
    check4:
        blt $t3, $t1, check5
        blt $t1, $t3, check5
        nop
    check5:
        ble $t3, $t1, check6
        ble $t3, $t3, check6
        nop
    check6:
        nop
        j check6
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test lw with test file", "[module]" )
{
    {
        std::string input = R"(.data
        .space 8
    var1:   .word 1
    var2:   .word -2
        
        .text
    main:
        la $t0, var1
        
        lw $t1, 0
        lw $t2, $t0
        lw $t3, 4($t0)
        lw $t4, 4(var1)
        lw $t5, var2
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test addu with test file", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = 12
    var:    .word 31
        .text
    main:
        lw $t0, var
        addu $t1, $t0, VALUE # 31+12=43
        addu $t2, $t1, $t0 # 43+31=74
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test add with test file", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = -1
    var:    .word 1
        .text
    main:
        lw $t0, var
        add $t1, $t0, VALUE
        add $t2, $t1, $t0
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test sub with test file", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = 2
    var1:   .word 1
    var2:   .word 12
    var3:   .word -1
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        sub $t3, $t0, VALUE # 1-2 = -1
        sub $t4, $t1, $t0 # 12-1 = 11
        sub $t5, $t2, VALUE # -1-2 = -3
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test subu with test file", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = 2
    var1:   .word 1
    var2:   .word 12
    var3:   .word -1
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        subu $t3, $t0, VALUE # 1-2 = -1 = 4294967295
        subu $t4, $t1, $t0 # 12-1 = 11
        subu $t5, $t2, VALUE # -1-2 = -3 = 4294967293
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.executeProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test break", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = 2
    var1:   .word 1
    var2:   .word 12
    var3:   .word -1
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        subu $t3, $t0, VALUE # 1-2 = -1 = 4294967295
        subu $t4, $t1, $t0 # 12-1 = 11
        subu $t5, $t2, VALUE # -1-2 = -3 = 4294967293
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.runProgram();
        parser.breakProgram();
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test more register aliases", "[module]" )
{
    {
        std::string input = R"(.data
        VALUE = 2
    var1:   .word 1
    var2:   .word 12
    var3:   .word -1
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        subu $t3, $t0, VALUE # 1-2 = -1 = 4294967295
        subu $t4, $t1, $t0 # 12-1 = 11
        subu $t5, $t2, VALUE # -1-2 = -3 = 4294967293
        )";
        std::istringstream iss(input);
        
        VirtualMachine parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        parser.printRegister("$23");
        parser.printRegister("$24");
        parser.printRegister("$25");
        parser.printRegister("$26");
        parser.printRegister("$27");
        parser.printRegister("$28");
        parser.printRegister("$29");
        parser.printRegister("$30");
        parser.printRegister("$31");
        parser.printRegister("$32");
        parser.getStatus();
        
        REQUIRE(parsed == true);
    }
}

