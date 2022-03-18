#include "hunt.h"
#include <stdio.h>
#include <math.h>

uint64_t get_bit(uint64_t nr, uint64_t i)
{

    uint64_t res = -1;

    uint64_t mask;


    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */
        mask = 1UL << i;
        if ((mask & nr) != 0) {
            res = 1;
        } else {
            res = 0;
        }
    
    return res;
}

uint64_t activate_bit(uint64_t nr, uint64_t i)
{

    uint64_t res = 0xF;

    uint64_t mask;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    mask = 1 << i;
    if ((mask & nr) != 0) {
        res = nr;
    } else {
        res = mask | nr;
    }

    return res;
}

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /* TODO 
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = 0, i, bit, contor = 0, numarbit = -1;

    for (i = 0 ; i <= 63 ; i++) {
        bit = get_bit(memory, i);
        numarbit += 1;
        if (bit == 1 && contor < 5) {
            contor += 1;
        } else if (bit == 0) {
            contor = 0;
        }
        if (contor == 5) {
            break;
        }
    }

    for (i = numarbit +1 ; i <= numarbit +16 ; i++) {
        bit = get_bit(memory, i);
        if (bit == 1) {
            res = activate_bit(res, i - (numarbit + 1));
        }
    }

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = 0, contor = 0, numarbit = 0;
    uint64_t bit, i;
    for (i = 63 ; i >= 0 ; i--) {
        bit = get_bit(memory, i);
        numarbit += 1;
        if (bit == 1 && contor < 3) {
            contor += 1;
        } else if (bit == 0) {
            contor = 0;
        }
        if (contor == 3) {
            break;
        }
    }
    numarbit = 63 - numarbit -16;
    for (i = numarbit +1 ; i <= numarbit +16 ; i++) {
        bit = get_bit(memory, i);
        if (bit == 1) {
            res = activate_bit(res, i - (numarbit + 1));
        }
    }
    

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */


    uint16_t res = -1;
    res = spell ^ key;
   

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = 0, i, activebits = 0, value = 0;

    for (i = 0 ; i <= 31 ; i++) {
        if (get_bit(enemy, i) == 1) {
            activebits += 1;
        }
    }
    if (activebits % 2 == 0) {
        res = activate_bit(res, 31);
        res = activate_bit(res, 28);
        value = (enemy & (1 - enemy));
        for (i = 0 ; i <=31 ; i++) {
            if (get_bit(value, i) == 1) {
                res = activate_bit(res, i);
            }
        }
    }
    if (activebits % 2 != 0) {
        res = activate_bit(res, 30);
        res = activate_bit(res, 29);
        value = pow(2, 17) - enemy;
        for (i = 0 ; i <=31 ; i++) {
            if (get_bit(value, i) == 1) {
                res = activate_bit(res, i);
            }
        }
    }


    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    
    /*
        Opeartiile intre variabile se fac de fiecare data intre 3 biti 
        Cate un bit de pe acelasi index de la 
        -antibodies_low
        -antibodies_high
        -cocktail
        deci am atribuit pe rand valoarea 1 sau 0 fiecareia si am ajuns la concluzia ca
        antibodies_low = 0
        antibodies_high = cocktail.
    */
    uint32_t res = 0, antibodies_high, antibodies_low;
    antibodies_low = 0;
    antibodies_high = cocktail;
    res = res | antibodies_high;
    res = res << 16;
    res = res | antibodies_low;

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = 0, tree = 0, x = 0, y = 0;
    uint64_t i, contor = 0;

    for (i = 0 ; i <= 63 ; i++) {
        if (get_bit(map, i) == 1) {
            contor += 1;
            tree += 1; 
          }
        if (get_bit(map, i) == 0) {
            contor = 0;
        } 
        if (contor > 4) {
            x = 1;
        }
        if (contor == 4) {
            y = 1;
        }
    }
    if (tree == 0) {
        res = 0;
    } else if (x == 0 && y == 1) {
        res = 0;
    }

    if (get_bit(map, 31) ==  1 && get_bit(map, 32) == 1 && tree == 2) {
        res = 1;
    }

    if (tree == 64) {
        res = 2;
    }

    if (tree == 0 || tree == 64 || 
    (get_bit(map, 31) ==  1 && get_bit(map, 32) == 1 && tree == 2) || 
    (x == 0 && y == 1) ) {
        } else {
        res = 3;
    }

    
    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = 1, i, contor = 31;

    for (i = 31 ; i >= 0 ; i--) {
        contor -= 1;
        if (get_bit(map, i) == 1) {
            break;
        }
    }
    for (i = contor ; i >= 0 ; i--) {
        if (get_bit(map, i) == 0) {
            res += 1; 
        } else {
            break;
        }
    }

    
    return res;
}
