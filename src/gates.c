#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

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


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    uint64_t mask;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */
    mask = 1UL << i;
    if ((mask & nr) != 0) {
        mask = ~(1UL << i);
        res = (mask & nr);
    } else {
        res = mask | nr;
    }

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    uint64_t mask;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    mask = 1UL << i;
    if ((mask & nr) != 0) {
        res = nr;
    } else {
        res = mask | nr;
    }

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    uint64_t mask;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */
    mask = 1UL << i;
    if ((mask & nr) != 0) {
        mask = ~(1UL << i);
        res = (mask & nr);
    } else {
        res = nr;
    }

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1, x;

    /* TODO - Use the nand gate to implement the and gate */
    x = nand_gate(a, b);
    res = nand_gate(x, x);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */
    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1, x, y;

    /* TODO - Use the previously defined gates to implement the or gate */
    x = nand_gate(a, a);
    y = nand_gate(b, b);
    res = nand_gate(x, y);

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1, x, y, z;

    /* TODO - Use the previously defined gates to implement the xor gate */
    x = nand_gate(a, b);
    y = nand_gate(a, x);
    z = nand_gate(b, x);
    res = nand_gate(y, z);
    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1, sum, carry, x, y, z;


    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    x = xor_gate(a, b);
    sum = xor_gate(x, c);
    y = nand_gate(c, x);
    z = nand_gate(a, b);
    carry = nand_gate(y, z);
    /*Codez suma si carry-ul punand :
    -bitul sumei pe pozitia 0 a bitului res
    -bitul carry-ului pe pozitia 1 a bitului res
    */
    uint8_t mask;
    res = 1;
    if (sum == 1) {
        mask = 1;
        res = res | mask;
    } else {
        mask = ~1;
        res = res & mask;
    }
    if (carry == 1) {
        mask = 1 << 1;
        res = res | mask;
    } else {
        mask = ~(1 << 1);
        res = res & mask;
    }

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1, i, x, y, carry = 0, R, sumafinala = 0;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    for (i = 0 ; i <=63 ; i++) {
        x = get_bit(a, i);
        y = get_bit(b, i);
        R = full_adder(x, y, carry);
        if (get_bit(R, 0) == 1) {
            sumafinala = activate_bit(sumafinala, i);
        }
        if (get_bit(R, 1) == 1) {
            carry = 1;
        } else if (get_bit(R, 1) == 0){
            carry = 0;
        }
        res = sumafinala;
    }
    if (carry == 1) {
        res = 0;
    }
    return res;
}
