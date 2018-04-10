#include "catch.hpp"

#include "parser.hpp"

#include <string>
#include <sstream>
#include <map>

TEST_CASE( "test an empty but valid file", "[parser]" )
{
    
    {
        std::string input = ".data\n.text";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test one entry", "[parser]" )
{
    
    {
        std::string input = ".data\n.word 10";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test two entries", "[parser]" )
{
    
    {
        std::string input = ".data\n.word 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test one entry, with a constant", "[parser]" )
{
    {
        std::string input = ".data\nx: .word 10";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test two entries, with a constant", "[parser]" )
{
    {
        std::string input = ".data\nx: .word 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test two lines of .data", "[parser]" )
{
    {
        std::string input = ".data\n.word 10, 20\n.word 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test multiple lines of .data, with different types", "[parser]" )
{
    {
        std::string input = ".data\n.word 10, 20\n.half 10, 20\n.byte 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test multiple lines of .data, with different types, but wrong data sizes", "[parser]" )
{
    {
        std::string input = ".data\n.word 2147483648, 20\n.half 10, 20\n.byte 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == false);
    }
    {
        std::string input = ".data\n.word 10, 20\n.half 32769, 20\n.byte 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == false);
    }
    {
        std::string input = ".data\n.word 10, 20\n.half 10, 20\n.byte 256, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == false);
    }
}

TEST_CASE( "test .space", "[parser]" )
{
    {
        std::string input = ".data\n.space 2";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test the two .ascii", "[parser]" )
{
    {
        std::string input = ".data\n.ascii hello";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\n.asciiz hello";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test .text", "[parser]" )
{
    {
        std::string input = ".data\n.word 10\n.half 10\n.byte 10\n.text\nmain:\nlw $t1, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test the different types of MIPS instructions", "[parser]" )
{
    {
        std::string input = ".data\nvar: .word 10\nvar2: .half 10\nvar3: .byte 10\n.text\nmain:\nlw $t0, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\nvar: .word 10\nvar2: .half 10\nvar3: .byte 10\n.text\nmain:\nadd $t0, $t1, $t2";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\n.word 10\n.half 10\n.byte 10\n.text\nmain:\nand $t0, $t1, $t3";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\n.word 10\n.half 10\n.byte 10\n.text\nmain:\nbne $t0, $t1, next";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\n.word 10\n.half 10\n.byte 10\n.space 10\n.text\nmain:\nbne $t0, $t1, next";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test .text with a fake MIPS instruction", "[parser]" )
{
    {
        std::string input = ".data\n.word 10, 20\n.half 10, 20\n.byte 10, 20\n.text\nmain:\nlz $t1, arr";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == false);
    }
}

TEST_CASE( "test constants", "[parser]" )
{
    {
        std::string input = ".data\nVALUE = 1";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test multiple lines of .data, with different types, with a constant", "[parser]" )
{
    {
        std::string input = ".data\nVALUE = 1\n.word 10, 20\n.half 10, 20\n.byte 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test multiple lines of .data, with different types, with a hex", "[parser]" )
{
    {
        std::string input = ".data\nVALUE = A\n.word B\n.half C\n.half D\n.half E\n.byte 10, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == false);
    }
}

TEST_CASE( "test labels")
{
    {
        std::string input = ".data\nx: .word 24\ny: .half 14\nz: .byte 9";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test #")
{
    {
        std::string input = ".data\n.word 10 # haha \n.half 10";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = ".data\n.word 10\n.half 10\n.byte 10\n.text\nmain:\nli $t1, 20 # haha\nli $t2, 20";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

TEST_CASE( "test the test cases")
{
    {
        std::string input = R"(# simple infinite loop
        .data
        .text
    main:    j main
        )";
        
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
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
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        A = 0
        B = 1
        C = 2
        D = 4
        .text
    main:
        li $t0, 100
        li $t1, A
        li $t2, B
        li $t3, C
        li $t4, D
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = -1234
        
        .text
    main:
        li $t0, VALUE
        move $t1, $t0
        move $t2, $t1
        move $t3, $t2
        move $t4, $t3
        move $t5, $t4
        move $t6, $t5
        move $t7, $t6
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = -1
    var:    .word 1
        .text
    main:
        lw $t0, var
        add $t1, $t0, VALUE
        add $t2, $t1, $t0
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 12
    var:    .word 31
        .text
    main:
        lw $t0, var
        addu $t1, $t0, VALUE # 31+12=43
        addu $t2, $t1, $t0 # 43+31=74
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
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
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
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
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 4
        VALUE2 = -4
    var1:   .word 2
    var2:   .word -2
    var3:   .word 1073741824 # = 2^30
        .text
    main:
        lw $t0, var1
        li $t1, VALUE
        mult $t0, $t1 # 2*4 = 8
        mflo $t8
        mfhi $t9
        
        lw $t0, var2
        lw $t1, var1
        mult $t0, $t1 # -2*2 = -4
        mflo $t8
        mfhi $t9
        
        lw $t0, var3
        li $t1, VALUE
        mult $t0, $t1 # 1073741824*4 = 4294967296 (overflow)
        mflo $t8
        mfhi $t9
        
        lw $t0, var3
        li $t1, VALUE2
        mult $t0, $t1 # 1073741824*-4 = -4294967296 (overflow)
        mflo $t8
        mfhi $t9
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 4
    var1:   .word 2
    var2:   .word 1073741824 # = 2^30
        .text
    main:
        lw $t0, var1
        li $t1, VALUE
        mult $t0, $t1 # 2*4 = 8
        mflo $t8
        mfhi $t9
        
        lw $t0, var2
        li $t1, VALUE
        mult $t0, $t1 # 1073741824*4 = 4294967296 (overflow)
        mflo $t8
        mfhi $t9
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 4
        VALUE2 = -4
    var1:   .word 2
    var2:   .word -2
    var3:   .word 1073741824 # = 2^30
        .text
    main:
        lw $t0, var1
        li $t1, VALUE
        div $t0, $t1 # 2/4 = 0 rem 2
        mflo $t8
        mfhi $t9
        
        lw $t0, var2
        lw $t1, var1
        div $t0, $t1 # -2/2 = -1 rem 0
        mflo $t8
        mfhi $t9
        
        lw $t0, var3
        li $t1, VALUE
        div $t0, $t1 # 1073741824/4 = 268435456 rem 0
        mflo $t8
        mfhi $t9
        
        lw $t0, var3
        li $t1, VALUE2
        div $t0, $t1 # 1073741824/-4 = -268435456 rem 0
        mflo $t8
        mfhi $t9
        
# divide by 0
        div $t0, $0
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 4
    var1:   .word 2
    var2:   .word 1073741825 # = 2^30+1
        .text
    main:
        lw $t0, var1
        li $t1, VALUE
        div $t0, $t1 # 2/4 = 0 rem 2
        mflo $t8
        mfhi $t9
        
        lw $t0, var2
        li $t1, VALUE
        div $t0, $t1 # 1073741825/4 = 268435456 rem 1
        mflo $t8
        mfhi $t9
        
# divide by 0
        div $t0, $0
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        and $t2, $t0, $t1
        and $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        nor $t2, $t0, $t1
        nor $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        or $t2, $t0, $t1
        or $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        xor $t2, $t0, $t1
        xor $t2, $t0, VALUE
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        VALUE = 3
    var1:   .word 12
    var2:   .word 10
        .text
    main:
        lw $t0, var1
        lw $t1, var2
        not $t2, $t0
        not $t2, $t1
        not $t2, VALUE
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
        .text
    main:
        nop
        j next
        nop
    next:
        nop
        j main
        )";
        std::istringstream iss(input);
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
    {
        std::string input = R"(
        .data
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
        
        Parser parser;
        TokenList tl = tokenize(iss);
        
        bool parsed = parser.parse(tl);
        
        REQUIRE(parsed == true);
    }
}

