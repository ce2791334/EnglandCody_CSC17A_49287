/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on October 25, 2020, 5:31 PM
 * Purpose: Game of Mao
 * Version: 15 - Final version. Cleanup and remove display of AI hand
 */

//System libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Format Library
#include <cstdlib>   //Random Function Library
#include <ctime>     //Time Library to Set Seed
#include <cstring>   //String library
#include <fstream>   //File library
using namespace std;
//User Libraries
#include "Cards.h"      
//Global Constants
//Only Universal Physics/Math/Conversions found here
//No Global Variables
//Higher Dimension arrays requiring definition prior to prototype only.
// - None

//Function Prototypes
//Create the deck
Cards *deck(const unsigned char);
Cards *dealP1(fstream &,Cards *,const unsigned char);   //Deal Player 1 hand 
Cards *dealAI(fstream &,Cards *,const unsigned char);   //Deal AI hand
Cards *dscrdPl(Cards *,const unsigned char);            //Create discard pile
Cards *cpyDeck(Cards *,const unsigned char); //Recreate deck with cards left 
                                             //after dealing
void prntCds(fstream &,Cards *);             //Print hand
void prtTpCd(string);           //Start game by showing 
                                               //the top card off deck
void destroy(Cards *);                         //Delete allocated memory
void wrtBin(fstream &,Cards *);                //Write the hands to files
//Play a card
int playCrd(fstream &,Cards *,Cards *,Cards *,const unsigned char);
//AI's turn to play
int AIplay(fstream &,Cards *,Cards *,Cards *,const unsigned char); 
void swap(Cards *,unsigned char);              //Swap cards to adjust for plays
//Execute if card played follows rules
void goodPly(Cards *,Cards *,unsigned char, unsigned char);  
//Execute if card played doesn't follow rules
void badPly(Cards *,Cards *,unsigned char);    
//This fxn will execute each turn
void gmePlay(fstream &,fstream &,Cards *,Cards *,Cards *,Cards *);
void tests(Cards *,const int,unsigned char &);  //This fxn will execute tests 
                                                //in between turns to simplify 
                                                //gmePlay fxn
void flpDcds(Cards *,Cards *,unsigned char &);  //"Flip over" the discard pile
unsigned char chceMnu(); //Mao specific fxn to choose number based 
                         //on card played
//Test that game rules are followed
unsigned char rules(string,Cards *,unsigned char);

//Execution Begins Here
int main(int argc, char** argv) {
//Set random number seed here when needed
    srand(static_cast<unsigned int>(time(0)));
//Declare variables or constants here
//7 characters or less
    const unsigned char DECK = 52;
    const unsigned char DEALSZ = 12; //This variable could be removed
                                     //but leaving it here allows for easy
                                     //adjustment of starting hand size if
                                     //desired
    fstream P1File;                  //File to hold Player 1's hand
    fstream AIFile;                  //File to hold AI player's hand
    unsigned char key;               //Just used to start the game
    //Start game
    cout << "Welcome to Mao! \nWarning this game is not for the faint "
         << "of heart as you must \nfigure out the rules as you go."
         << "When you play a card, you may \nbe presented with a menu "
         << "of numbers, each of which corresponds to \na particular "
         << "condition of the card you played. Choose wisely!\n"
         << "Hit any key to continue:\n";
    cin >> key;
    //Initialize or input data here 
    //Create the deck before dealing
    Cards *Deck = deck(DECK);                       ////Create1
    //Deal hands
    Cards *P1 = dealP1(P1File, Deck, DEALSZ);       ////Create2
    Cards *AI = dealAI(AIFile, Deck, DEALSZ);       ////Create3
    //Create the deck that will be used throughout the game
    Cards *gmeDeck = cpyDeck(Deck, DECK);           ////Create5
    //Create the discard pile
    Cards *discrd = dscrdPl(gmeDeck, DECK);           ////Create4
    
    //Begin game play
    gmePlay(P1File, AIFile, gmeDeck, P1, AI, discrd);
   
    //Delete allocated memory
    destroy(P1);                            ////Delete1
    destroy(AI);                            ////Delete2
    destroy(discrd);            ////Delete4
    destroy(gmeDeck);          ///Delete5
    //Exit Stage Right
    return 0;
}

//Begin fxn to create the rest of the deck
Cards *deck(const unsigned char Deck)
{
    //Declare variables
    char suit; 
    string face;
    bool dupChk = false; //Flag variable to check for duplicate
                         //cards
    //Allocate memory for the deck after dealing the hands
    Cards *deck = new Cards;
    deck->hand = new Hand[Deck];    //Largest number of cards
                                       //there could be
    //Initialize size of deck
    deck->hand->hdSz = Deck;
    //Loop to assign initial hand
    for (int i = 0; i < Deck; i++)
    {
    //Create a unique random card off the top of deck
    //I chose this method of randomly assigning the cards in the deck 
    //removes the need to shuffle, but may cause program to take longer
    //to run as the loop goes until all cards are unique
      do{
        int rdcrd = rand() % Deck;
        if(rdcrd <= 12)suit = 'S';
        else if(rdcrd <= 25)suit = 'C';
        else if(rdcrd <= 38)suit = 'D';
        else suit = 'H';
        switch(rdcrd % 13+1){
            case 1:face = "A";break;
            case 2:face = "2";break;
            case 3:face = "3";break;
            case 4:face = "4";break;
            case 5:face = "5";break;
            case 6:face = "6";break;
            case 7:face = "7";break;
            case 8:face = "8";break;
            case 9:face = "9";break;
            case 10:face = "T";break;
            case 11:face = "J";break;
            case 12:face = "Q";break;
            case 13:face = "K";break;
            default:cout<<"Bad Condition"<<endl;
        }   
            face.append(1, suit);
            deck->hand[i].card = face;
            //Check if card is a duplicate of one already in deck
            for(int chkDk = 0; chkDk < i; chkDk++)
            {
                if(deck->hand[i].card  == deck->hand[chkDk].card)
                {
                    dupChk = true;
                    break;
                }
                else dupChk = false;
            }
      } while(dupChk); 
    }
    return deck;
}

//Begin function to deal P1 hand
Cards *dealP1(fstream &P1File, Cards *deck, const unsigned char HdSz)
{
    //Allocate memory for a new Player 1 hand
    Cards *dealP1 = new Cards;
    dealP1->hand = new Hand[deck->hand->hdSz];    //Largest number of cards
                                                  //there could be
    //Initialize starting hand size
    dealP1->hand->hdSz = HdSz;
    //Loop to assign initial hand
    for (int i = 0; i < HdSz; i++)
    {
        //Multiply position in deck by 2 to simulate even 
        //dealing between players
        dealP1->hand[i].card = deck->hand[i*2].card;
    }
     //Write hand contents to a binary file
     wrtBin(P1File, dealP1);
    //Adjust size of deck to account for dealt cards
    deck->hand->hdSz = deck->hand->hdSz - HdSz;
    return dealP1;
}

//Begin function to deal AI hand
Cards *dealAI(fstream &AIFile, Cards *deck, const unsigned char HdSz)
{
    //Allocate memory for a new Player 1 hand
    Cards *dealAI = new Cards;
    dealAI->hand = new Hand[deck->hand->hdSz];    //Largest number of cards
                                                  //there could be
    //Initialize starting hand size
    dealAI->hand->hdSz = HdSz;
    //Loop to assign initial hand
    for (int i = 0; i < HdSz; i++)
    {
        //Multiply position in deck by 2 to simulate even 
        //dealing between players
        dealAI->hand[i].card = deck->hand[i*2 + 1].card;
    }
    //Write hand contents to a binary file
    wrtBin(AIFile, dealAI);
    //Adjust size of deck to account for dealt cards
    deck->hand->hdSz = deck->hand->hdSz - HdSz;
    return dealAI;
}

//Begin fxn to write the starting hands to files
void wrtBin(fstream &binFile, Cards *hnd)
{
    hnd->hand[hnd->hand->hdSz + 1].card = hnd->hand[0].card;
    //Open file
    binFile.open("P1.bin",ios::out|ios::binary);
    //Write card to file
    for(unsigned char i = 0 ; i < hnd->hand->hdSz; i++)
    {
    binFile.seekp(i, ios::beg);
    binFile.write(reinterpret_cast<char *>(&hnd->hand[i].card[0]),
            sizeof(char));
    binFile.write(reinterpret_cast<char *>(&hnd->hand[i].card[1]),
            sizeof(char));
    }
    //close file
    binFile.close();
}

//Begin fxn to recreate deck that holds remaining cards after dealing
Cards *cpyDeck(Cards *deck, const unsigned char Deck)
{
    //Allocate memory for a discard pile
    Cards *nDeck = new Cards;
    nDeck->hand = new Hand[Deck];    //Largest number of cards
                                     //there could be
    unsigned char val = Deck - deck->hand->hdSz;
    //Initialize the size of the new deck
    nDeck->hand->hdSz = deck->hand->hdSz;
   //For loop to assign remaining cards in original deck to the new one
    for(unsigned char i = val; i < Deck; i++)
        nDeck->hand[i - val].card = deck->hand[i].card;
    
    //Delete original deck
    destroy(deck);                             ////Delete3
    return nDeck;
}

//Begin fxn to create dynamic discard pile
Cards *dscrdPl(Cards *deck, const unsigned char deckSz)
{
    //Allocate memory for a discard pile
    Cards *discrd = new Cards;
    discrd->hand = new Hand[deckSz];    //Largest number of cards
                                                  //there could be
    //First card in discard pile will be the top card off the deck
    discrd->hand[0].card = deck->hand[0].card;
    //Initialize size of discard pile to 1
    discrd->hand->hdSz = 1;
    //Print the top card
    prtTpCd(discrd->hand[0].card); 
    //Decrement deck size to account for displayed card
    deck->hand->hdSz--;
    return discrd;
}

//Begin function to display the hand
void prntCds(fstream &inBin, Cards *hand)
{
    //Declare fxn variables
    unsigned char crdHt = 2;          //height of card
    //Open file to get hand from
    inBin.open("P1.bin",ios::in|ios::binary);       
    for(unsigned char i = 0 ; i < hand->hand->hdSz; i++)
    {
    inBin.read(reinterpret_cast<char *>(&hand->hand->card[0]), sizeof(char));
    inBin.read(reinterpret_cast<char *>(&hand->hand->card[1]),sizeof(char));
    } 
    //Reset first card to proper value
    hand->hand[0].card = hand->hand[hand->hand->hdSz + 1].card;
    //Display top edge of cards
    for (unsigned char i = 0; i < hand->hand->hdSz; i++)
      cout << " - - -";
      cout << endl;
    //Display card number/suit
    for (unsigned char i = 0; i < hand->hand->hdSz; i++)
    {
        cout << "|" << setw(2);
        //I want to show the number 10
        if (hand->hand[i].card[0] != 'T')
        cout << hand->hand[i].card << setw(4);
        else
            cout << "10" << hand->hand[i].card[1] << setw(3);
    }
      //Close file
      inBin.close();
    //This if statement prevents a display when there are no cards 
    //left in hand
    if (hand->hand->hdSz > 0)
       cout << "|" << endl;
  
    //Display sides of cards
    for (int i = 0; i < crdHt; i++)
    {
        for (int j = 0; j < hand->hand->hdSz; j++)
        cout << "|" << setw(6); 
        
        if (hand->hand->hdSz > 0)
        cout << "|" << endl;
    }
    //Display bottom edge of cards
    for (int i = 0; i < hand->hand->hdSz; i++)
      cout << " - - -";
    cout << endl;
}

//Begin fxn to print the top card of discard pile
void prtTpCd(string card)
{
    //Declare fxn variables
    char crdHt = 2;          //height of card
    string ten;       //To test for card value of 1
    
    //Display "deck"
      cout << " X X X   - - - " << endl; //Top edge
    //Loop to display centers of top of next card in deck
    //and the face of the card shown
    for (int i = 0; i < crdHt + 1; i++)
    {
        for(int j = 0; j < crdHt * 2; j++)
        cout << "X ";  
        cout << "|" << setw(2);
        if(i == 0)
        {
            //Make sure to display '10' rather than 'T'
            if (card[0] != 'T')
                cout << card << setw(4);
            else
                cout << "10" << card[1] << setw(3);
            
            cout << "|" << endl;
        }
        else{
            cout << setw(6) << "|" << endl;
        }
    }
      cout << " X X X   - - - " << endl;
}

//Begin fxn to delete allocated memory
void destroy(Cards *Hand)
{
    delete []Hand->hand;            ///////Delete1
    delete Hand;                    //////Delete2
}

//Begin fxn to play a card
int playCrd(fstream &file, Cards *hand, Cards *dscrd, Cards *deck,
             const unsigned char turn)
{
    //Declare fxn variables
    string play;    //Will hold input value of card user plays
    bool valid = true;  //Boolean value to check that card played is valid
    unsigned char posn; //Will hold the position of the card played
    unsigned char goodCrd; //This variable will hold either 1 or 2 depending
                           //on whether play followed all rules
    //Enter do while loop to ask player for a card as long as they enter an
    //invalid card
    do{
        //Ask player to enter the card they want to play
        cout << endl << "Enter the face value and suit of the card "
             << "you want to play (enter 'T' for 10):" << endl;
        cin >> play;
     
        //Loop to check that card played is one from hand
        for(unsigned char i = 0; i < hand->hand->hdSz; i++)
        {
           //If card isn't in the player's hand
           if(hand->hand[i].card != play) 
               valid = false;
           else
           {
               posn = i;
               valid = true;
               break;
           }
        }
        if(!valid)
        {
            cout << "The card you're trying to play isn't in your hand!"
                 << endl;
        }
    }while(!valid);
    //Checck that play followed rules. If not then penalize with 
    //additional card
    goodCrd = rules(hand->hand[posn].card, dscrd, turn);
    //If 2 then ggod play and proceed normally
    if(goodCrd == '2') //Execute a good play procedure
        goodPly(hand, dscrd, turn, posn);
    else //Execute a bad play procedure
        badPly(hand, deck, posn);
    //Write the new hand to file
    wrtBin(file, hand);
    //Conditional return value of good or bad play
    if(goodCrd == '2')
        return 0;
    else return 1;
}

//Begin fxn to display the card played by the AI
int AIplay(fstream &file, Cards *AI, Cards *dscrd, Cards *deck,
            const unsigned char turn)
{
    //Declare fxn variables
    bool check = false;         //Check if AI has a playable card
    unsigned int indx = 0;     //index to check AI hand for playable card
    //Enter while loop to only play valid card for AI if possible
    while( indx < static_cast<int>(AI->hand->hdSz))
    {
        if(AI->hand[indx].card[0] == dscrd->hand[turn - 1].card[0] 
           || AI->hand[indx].card[1] == dscrd->hand[turn - 1].card[1])
        {
            check = true;
            break;
        }
        indx++;
    }
    //If valid card found then execute a good play procedure
    if(check) 
    {
        cout << "Computer played..." << endl;
        goodPly(AI, dscrd, turn, indx);
    }
    else //Execute a bad play procedure
    {
        badPly(AI, deck, indx);
        cout << "Computer was penalized for not matching "
             << "suit or face value\n";
    }
    //Write the new hand to file
    wrtBin(file, AI);
    //Conditional return value of good or bad play
    if(check)
        return 0;
    else return 1;
}

//Begin swap fxn to adjust hand for card plays
void swap(Cards *hand, unsigned char posn)
{
    for(unsigned char i = posn; i < hand->hand->hdSz; i++)
    {
        string temp = hand->hand[i].card;
        hand->hand[i].card = hand->hand[i + 1].card;
        hand->hand[i + 1].card = temp;
    }
}

//Begin fxn to execute each turn in the game
void gmePlay(fstream &P1File, fstream &AIFile, 
             Cards *deck, Cards *P1, Cards *AI, Cards *dscrd)
{
    //Declare fxn variables
    unsigned char turn = 1;          //Counter representing each turn
    int testVal;                     //This will be use to test if play 
                                     //was good or bad
    //Print initial hands
    prntCds(P1File, P1);
    //Enter do while loop to continue turns until 1 player plays all 
    //cards.  Increment turn counter after each play 
    //(so technically counter represents a half turn)
    do{
        //Play a card
        testVal = playCrd(P1File, P1, dscrd, deck, turn);
        //Test results of Player 1's turn
        tests(deck,testVal,turn);
        //AI's turn
        testVal = AIplay(AIFile, AI, dscrd, deck, turn);
         //Test results of AI's turn
        tests(deck,testVal,turn);
        //Print hand after turn
        prntCds(P1File, P1);
    }while(P1->hand->hdSz > 0 && AI->hand->hdSz > 0);
    if(P1->hand->hdSz == '0')
        cout << "Congratulations, you won!" << endl;
    else
        cout << "Too bad, AI wins :(" << endl;
}

 //Begin fxn to test if game rules are followed during a play
unsigned char rules(string crdPlyd, Cards *dscrd, unsigned char turn)
{
    unsigned char choice; //This will be '2' if all rules are followed 
                       //and '1' if any rule is broken
    //Independent if statements to check each rule of play
    //Rule 1: Cards played must be of either same suit or face value
    if(crdPlyd[0] != dscrd->hand[turn - 1].card[0] && crdPlyd[1] != 
       dscrd->hand[turn - 1].card[1])
    {
        cout << "You were penalized for not matching "
             << "suit or face value\n";
        choice = '1';
        return choice;
    }
    //Rule 2: if an ace is played then '1' must be entered
    if(crdPlyd[0] == 'A')
    {
        choice = chceMnu();
        if(choice != '1')
        {
            cout << "You were penalized for not choosing '1'\n";
            choice = '1';
            return choice;
        }
    }
    //Rule 3: If the suit of top card on discard pile is changed then
    //a '2' must be entered
    if(crdPlyd[0] == dscrd->hand[turn - 1].card[0])
    {
        choice = chceMnu();
        if(choice != '2')
        {
            cout << "You were penalized for not choosing '2'\n";
            choice = '1';
            return choice;
        }
    }
    //Rule 4: If a short run occurs (any 2 values in a row in 
    //increasing order) than a '3' must be entered
    if(turn >= '2')
    if(dscrd->hand[turn - 1].card[0] == dscrd->hand[turn - 2].card[0])
    {
        choice = chceMnu();
        if(choice != '3')
        {
            cout << "You were penalized for not choosing '3'\n";
            choice = '1';
            return choice;
        }
    }  
        //Fulfilled all rules!
        choice = '2';
        return choice;
}

 //Begin fxn that executes if card played follows rules
void goodPly(Cards *hand, Cards *dscrd, unsigned char turn, 
             unsigned char posn)
{       
    //Assign played card to discard pile
    dscrd->hand[turn].card = hand->hand[posn].card;
    prtTpCd(dscrd->hand[turn].card);
    //remove the card played from player's hand
    hand->hand[posn].card = '0';
    swap(hand, posn);
    
    //Decrement hand size
    hand->hand->hdSz--;
}

//Begin fxn that executes if card played doesn't follow rules
void badPly(Cards *hand, Cards *deck, unsigned char posn)
{ 
    //If bad play then penalize by adding a card to player's hand
    //Give card from bottom of deck. Not realistic but 
    //simplest implementation
    hand->hand[hand->hand->hdSz].card = deck->hand[deck->hand->hdSz].card;
    //Increment hand size to account for penalization card 
    //which means decrementing the deck
    hand->hand->hdSz++;
    deck->hand->hdSz--;
}

//Begin fxn to execute tests in between turns
void tests(Cards *deck,const int val,unsigned char &turn)
{
    //Control the turn counter to control top card of discard pile 
    //that's compared to
    if(val == 0)
    turn++;
    //Check if deck is empty b/c then discard pile will be flipped over   
    if(static_cast<int>(deck->hand->hdSz) == 0)
        flpDcds;
}

//Begin fxn to "flip over" the discard pile
void flpDcds(Cards *deck ,Cards *dscrd, unsigned char &turn)
{
    //For loop to assign all discard cards back into deck
    for(unsigned char i = 0; i < turn; i++)
     deck->hand[i].card = dscrd->hand[i].card;
    
    //Reset turn counter now that discard pile has been flipped over
    turn = 1;
}

//Begin fxn to display menu for Player to choose a number 
//to satisfy condition
unsigned char chceMnu()
{
    //Declare fxn variables
    unsigned char choice;
    //Ask Player to choose a number
    cout << "Enter 1, 2, or 3:" << endl;
    cin >> choice;
    
    return choice;
}