#include "communication.h"
#include "util_comm.h"

#include <stdio.h>

uint8_t get_bit(uint8_t nr, uint8_t i)
{

    uint8_t C = -1;

    uint8_t mask;

    /* TODO
     *
     * "C" should be 1 if the bit is active, else 0
     */
        mask = 1UL << i;
        if ((mask & nr) != 0) {
            C = 1;
        } else {
            C = 0;
        }
    
    return C;
}

uint8_t activate_bit(uint8_t nr, uint8_t i)
{

    uint8_t C = 0xFF;

    uint8_t mask;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */
    mask = 1UL << i;
    if ((mask & nr) != 0) {
        C = nr;
    } else {
        C = mask | nr;
    }

    return C;
}


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch('R' - 64);
    send_squanch('I' - 64);
    send_squanch('C' - 64);
    send_squanch('K' - 64);
}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t cod[5], i;

    cod[0] = recv_squanch();
    cod[1] = recv_squanch();
    cod[2] = recv_squanch();
    cod[3] = recv_squanch();
    cod[4] = recv_squanch();

    for(i = 0 ; i <= 4 ; i++) {
        cod[i] += 64; 
        fprintf(stdout, "%c", cod[i]);
    }
    
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    uint8_t cod[10], i;
    for (i = 0 ; i <= 9 ; i++) {
        cod[i] = recv_squanch();
    }
    for (i = 0 ; i <= 9 ; i++) {
        send_squanch(cod[i]);
        send_squanch(cod[i]);
    }
}

/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */

    uint8_t lungime = 10, cod[10], i;
    lungime = lungime << 2;
    cod[0] = 'H' - 64;
    cod[1] = 'E' - 64;
    cod[2] = 'L' - 64;
    cod[3] = 'L' - 64;
    cod[4] = 'O' - 64;
    cod[5] = 'T' - 64;
    cod[6] = 'H' - 64;
    cod[7] = 'E' - 64;
    cod[8] = 'R' - 64;
    cod[9] = 'E' - 64;
    send_squanch(lungime);
    for (i = 0 ; i <= 9 ; i++) {
        send_squanch(cod[i]);
    }

}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t x, i, bit[8] = {0};

    x = recv_squanch();
    for(i = 2 ; i <=5 ; i++) {
        bit[i] = get_bit(x,i);
    }
    x = 0;
    for(i = 2 ; i <=5 ; i++) {
        if (bit[i] == 1) {
            x = activate_bit(x, i - 2);
        }
    }

    fprintf(stdout, "%u", x);

    uint8_t cod;

    for (i =0 ; i <= x - 1 ; i++) {
        cod = recv_squanch();
        cod = cod + 64;
        fprintf(stdout, "%c", cod );
    }
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */

    uint8_t lungime, i, bit[8] = {0};
    lungime = recv_squanch();
    for(i = 2 ; i <=5 ; i++) {
        bit[i] = get_bit(lungime,i);
    }
    lungime = 0;
    for(i = 2 ; i <=5 ; i++) {
        if (bit[i] == 1) {
            lungime = activate_bit(lungime, i - 2);
        }
    }
    uint8_t cod, caracter[11];

    for (i =0 ; i <= lungime - 1 ; i++) {
        cod = recv_squanch();
        cod = cod + 64;
    }
    if (cod == 'P') {
        uint8_t lungimetrimisa = 10;
        lungimetrimisa = lungimetrimisa << 2;
        send_squanch(lungimetrimisa);
        caracter[0] = 'P' - 64;
        caracter[1] = 'I' - 64;
        caracter[2] = 'C' - 64;
        caracter[3] = 'K' - 64;
        caracter[4] = 'L' - 64;
        caracter[5] = 'E' - 64;
        caracter[6] = 'R' - 64;
        caracter[7] = 'I' - 64;
        caracter[8] = 'C' - 64;
        caracter[9] = 'K' - 64;
        for(i = 0 ; i <= 9 ; i++) {
        send_squanch(caracter[i]);
        }
    } else {
        uint8_t lungimetrimisa = 11;
        lungimetrimisa = lungimetrimisa << 2;
        send_squanch(lungimetrimisa);
        caracter[0] = 'V' - 64;
        caracter[1] = 'I' - 64;
        caracter[2] = 'N' - 64;
        caracter[3] = 'D' - 64;
        caracter[4] = 'I' - 64;
        caracter[5] = 'C' - 64;
        caracter[6] = 'A' - 64;
        caracter[7] = 'T' - 64;
        caracter[8] = 'O' - 64;
        caracter[9] = 'R' - 64;
        caracter[10] = 'S' - 64;

        for(i = 0 ; i <= 10 ; i++) {
        send_squanch(caracter[i]);
        }
    }
}

/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

    uint8_t i, bitc1[4], bitc2[4], octetfinal = 0;
    for (i = 0 ; i <= 3 ; i++) {
        bitc1[i] = get_bit(c1, i);
    }
    for (i = 0 ; i <= 3 ; i++) {
        bitc2[i] = get_bit(c2, i);
    }
    for (i = 0 ; i<= 3 ; i++) {
        if (bitc2[i] == 1) {
            octetfinal = activate_bit(octetfinal, i * 2);
        }
        
    }
    for (i = 0 ; i<= 3 ; i++) {
        if (bitc1[i] == 1) {
            octetfinal = activate_bit(octetfinal, (i * 2) + 1);
        }
    }
    send_squanch(octetfinal);
}


uint8_t decode_squanch2(uint8_t c)
{
    /* TODO 
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = 2, i, caracter = 0, bitc;

    for(i = 0 ; i<= 7 ; i++) {
        bitc = get_bit(c, i);
        if (i % 2 == 0 && bitc == 1) {
            caracter = activate_bit(caracter, i / 2);
        } else if (i == 1 && bitc ==1) {
            caracter = activate_bit(caracter, 4);
        } else if (i == 3 && bitc ==1) {
            caracter = activate_bit(caracter, 5);
        } else if (i == 5 && bitc ==1) {
            caracter = activate_bit(caracter, 6);
        } else if (i == 7 && bitc ==1) {
            caracter = activate_bit(caracter, 7);
        }
    }
    res = caracter;
    
    return res;
}
