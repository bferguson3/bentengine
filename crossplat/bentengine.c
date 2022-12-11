// bentengine.c 

//#define SDLVERSION 
#ifndef PC88VERSION
#define PC88VERSION 1
#endif
//#define MDVERSION 1


#ifdef SDLVERSION
#include <stdlib.h> // null, rand, srand
#include <time.h>   // time
#include <stdio.h>  // printf
//#include <math.h>   // pow
#endif 

#ifdef PC88VERSION
#include "../pc88-c/src/pc88-c.h"
#endif

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))

#ifndef NULL
#define NULL 0
#endif 

#ifndef __MATH_H__
long pow(int base, int pow)
{
    if(pow < 0)
        return -1;
    if(pow == 0)
        return 1;
        
    long result = base;
    for(int c = 1; c < pow; c++)
    {
        result *= base;
    }
    return result;
}
#endif

unsigned int Damage(int srcAtk, int tgtDef);

#ifdef SDLVERSION
int main(int argn, char** args)
#endif
#ifdef PC88VERSION
void main()
#endif
{
    // Seed rand
    #ifdef _TIME_H_
    #ifdef _STDLIB_H_
        srand(time(NULL));
    #endif 
    #endif 
    // Damage, based on derived ATK/DEF
    // DMG = min() of ((Atk x 2) / Def) 
    //                  + Atk - (Def/2)
    //       or Atk (Atk is max damage)
    //  then x MODIFIERS
    //   then max(dmg, 1) (1 is min damage)
    //    then randomize here with +0-2
    #ifdef _STDIO_H_
        printf("dmg %d\n", Damage(13, 25));
    #endif 
    #ifdef PC88VERSION
        SetCursorPos(0, 0);
        print(byToDec(Damage(13,25) & 0xff));
    #endif
    // Character EXP to NEXT level:
    // 10 x ( Lvl x (Lvl^2) )
    //  (This is added to current xp)
    int totalp = 0;
    for(int i = 1; i < 21; i++)
    {
        int nextexp = 10 * (i * pow(i,2));
        totalp += nextexp;
        #ifdef _STDIO_H_
            printf("lv %d / total %d\n", i, totalp);
        #endif 
    }

    // Average monster XP by monster level:
    // (Lvl^2) x 2
    for(int i = 1; i < 21; i++)
    {
        int next = pow(i,2) * 2;
        #ifdef _STDIO_H_
            printf("mob lv %d / xp %d\n", i, next);
        #endif
    }

    #ifdef SDLVERSION
    return 0;
    #endif
}

#ifdef PC88VERSION
int TGTDEF;
int SRCATK;
#endif 

unsigned int Damage(int srcAtk, int tgtDef)
{
    #ifdef SDLVERSION
    signed int result;
    result = (srcAtk * 2) / tgtDef;
    result += (srcAtk - (tgtDef / 2));
    #ifdef _STDLIB_H_
        result += (rand() % 3);
    #endif
    return MIN(result, srcAtk);
    #endif 
    #ifdef PC88VERSION
    //TGTDEF = tgtDef;
    //SRCATK = srcAtk;
    __asm 
        // ld ix hl 2 etc
        ld iy, #2
        add iy, sp
        ld l, 1 (iy)
        ld h, 0 (iy)
        ld (_SRCATK), hl
        ld e, 3 (iy)
        ld d, 2 (iy)
        ld (_TGTDEF), de 
        // SRC ATK X 2
        PUSH HL 
        ADD HL,HL
        // DIV BY TGTDEF 

        // DIV...
        
        // ADD SRC ATK
        POP DE 
        ADD HL,DE
        PUSH HL
        // THEN SUB TGTDEF / 2 
        LD HL,(_TGTDEF)
        SRL H 
        RR L 
        PUSH HL 
        POP DE 
        POP HL 
        SBC HL,DE
        // ADD RAND 0-2 TO HL

        // ...
        
        // IF SRCATK IS SMALLER, RETURN THAT
        LD DE,(_SRCATK)
        PUSH HL 
        SBC HL,DE 
        JR C,.RETHL
        POP HL 
        // SRCATK IS SMALLER
        LD HL,(_SRCATK)
        RET
        // AND RETURN HL 
    .RETHL:
        POP HL 
        //RET
        // AND RETURN HL 
    __endasm;
    #endif
}

