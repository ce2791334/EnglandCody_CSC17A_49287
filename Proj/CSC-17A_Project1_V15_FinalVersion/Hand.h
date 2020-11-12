/* 
 * File:   Hand.h
 * Author: Cody England
 * Created on October 24, 2020, 12:33 PM
 * Purpose: Individual structure to hold the cards in the deck,
 * the discard pile, Player 1's hand, and the AI's hand.
 */

#ifndef HAND_H
#define HAND_H

struct Hand{
    
    unsigned char hdSz;  //Number of cards in either hand or deck
    string card;
};

#endif /* HAND_H */

