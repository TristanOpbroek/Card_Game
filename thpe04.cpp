/** *********************************************************************
 * @file
 *
 * @brief   Main runtime of the solution
 * @author Tristan Opbroek
 ***********************************************************************/
#pragma once
#define CATCH_CONFIG_RUNNER
#include "thpe04.h"
#include "..//catch.hpp"
using namespace std;

 /**********************************************************************
 *
 * @mainpage THPE04 - Game of War
 *
 * @section CSC 215 M02
 *
 * @authors Tristan Opbroek
 *
 * @date December 9th, 2022
 *
 * @par Instructor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         Classroom Building - Room 205
 *
 * @section program_section Program Information
 *
 * @details This program plays a virtual game of "War" with decks of cards given from a file, or randomly generated using rules outlined in thpe04.
 * 
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      none - a straight compile and link with no external libraries.
 *
 * @par Usage:
 *  @verbatim
 *  minimal run:
 *  c:\> thpe04.exe -runType -arg1 -arg2
 *
 * where -runType is the specified format for getting decks; -s for random generation with Seed, and -f for file input
 *       -arg1 is a specified seed or file for player 1
 *       -arg2 is a specified seed or file for player 2
 *
 *
 *  @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug The program can't deal with impossibly big seed values
 *
 * @par Modifications and Development Timeline:
 *  Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/101078202/csc215f22programs/-/commits/main">
 *
 ***********************************************************************/

 /** ***************************************************************************
   * @author Tristan Opbroek
   *
   * @par Description:
   * Main runtime of program
   *
   * @param[in] argc - number of arguments provided to the program
   * @param[in] argv - Array of arguments provided to the program
   * @returns 0 on program exit.
   *****************************************************************************/
int main(int argc, char** argv)
{
    if (runcatch)
    {
        Catch::Session session;
        int returnCode;
        returnCode = session.run(argc, argv);
        if (returnCode != 0)
            cout << "A Test case failed" << endl;
        return 0;
    }
    ifstream fin;
    string temp;
    queue<card> player1;
    queue<card> player2;
    int counter = 0;
    //Command line arguments
    if (argc != 4)
    {
        cout << "Invalid Startup!" << endl;
        cout << "Usage:" << endl;
        cout << "thpe04.exe -runType ar1 ar2" << endl;
        cout << endl;
        cout << "-runType:" << endl;
        cout << "        -s for seeds" << endl;
        cout << "        -f for files" << endl;
        cout << "ar1:" << endl;
        cout << "    seed number for player 1 given -s as first argument" << endl;
        cout << "    file for player 1 given -f as first argument" << endl;
        cout << "ar2:" << endl;
        cout << "    seed number for player 2 given -s as first argument" << endl;
        cout << "    file for player 2 given -f as first argument" << endl;
        return 0;
    }
    //------------------------------------------------------------------------------------

    temp = argv[1];
    
    if (temp == "-f") //Get Cards
    {
        openFile(fin, argv[2]);
        getCards(player1, fin);
        fin.close();
        openFile(fin, argv[3]);
        getCards(player2, fin);
    }

    else if (temp == "-s")
    {
        getCardsRandom(player1, stoi(argv[2]));
        getCardsRandom(player2, stoi(argv[3]));
    }
    else
    {
        cout << "Invalid Startup!" << endl;
        return 0;
    }
    //------------------------------------------------

    while (player1.size() != 0 && player2.size() != 0)
    {
        playRound(player1, player2);
        counter++;
    }
    if (player2.size() == 0)
    {
        cout << "Player 1 wins after " << counter << " rounds." << endl;
        cout << "Player 1 hand: " << player1 << endl;
        cout << "Player 2 hand: " << player2 << endl;
        return 0;
    }
    if (player1.size() == 0)
    {
        cout << "Player 2 wins after " << counter << " rounds." << endl;
        cout << "Player 1 hand: " << player1 << endl;
        cout << "Player 2 hand: " << player2 << endl;
        return 0;
    }
}


/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Retrieves a list of cards from a file and loads them into a queue of cards.
  *
  * @param[in] player - Queue of cards to load into from file
  * @param[in] fin - ifstream to load cards from.
  * 
  * @par Example
  * @verbatim
  * ifstream fin; //contains valid ifstream of card data
  * queue<card> player; //Player data to write deck to
  * getCards(player, fin) //Player now contains all of the cards from fin.
  *@endverbatim
  *****************************************************************************/
void getCards(queue<card>& player, ifstream& fin)
{
    string temp;
    card tempCard;
    while (fin >> temp)
    {
        tempCard.faceValue = stoi(temp) % 13;
        tempCard.suit = stoi(temp) / 13;
        player.push(tempCard);
    }
}

/** ***************************************************************************
  * @author Tristan Opbroek
  * @author Roger Schrader
  *
  * @par Description:
  * Generates a list of cards for a player via a random seed
  *
  * @param[in] player - Queue of cards to load into.
  * @param[in] seed - seed for random number generator
  * @verbatim
  * int seed; //Seed to use for random generation
  * queue<card> player; //Player data to write deck to
  * getCardsRandom(player, seed) //Player now contains random cards generated with seed.
  * @endverbatim
  *****************************************************************************/
void getCardsRandom(queue<card>& player, int seed)
{
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 51);
    card tempCard;
    int temp;
    for (int i = 0; i < 52; i++)
    {
        do
        {
            temp = distribution(generator);
            tempCard.faceValue = temp % 13;
            tempCard.suit = temp / 13;
        } 
        while (inQueue(player, tempCard) == true);
        player.push(tempCard);
    }
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Opens a file and assigns it to an ifstream
  *
  * @param[in] fin - ifstream to open the file to
  * @param[in] file - file to open
  * @par Example
  * @verbatim  
  * ifstream fin; //valid ifstream
  * string file = "cardData.cards"; //File you want to assign to fin
  * openFile(fin, file); //fin now reads from cardData.cards
  * @endverbatim
  *****************************************************************************/
void openFile(ifstream& fin, string file)
{
    fin.open(file);
    if (!fin.is_open())
    {
        cout << "Unable to open deck file " << file << endl;
        exit(0);
    }
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Checks if a card already exists in a queue of cards.
  *
  * @param[in] player - Deck of cards
  * @param[in] newCard - Card to add to deck
  *
  * @returns True if card is already in queue
  * @returns False if card isn't already in queue
  * @par Example
  * @verbatim
  * queue<card> player; //Contains [8H, 6S, 2C]
  * newCard = 8H; //8H, would be represented with the data inside the struct, not 8H specifically.
  * inQueue(player, newCard) //True, because newCard exists inside Queue already.
  * @endverbatim
  *****************************************************************************/
bool inQueue(queue<card> player, card newCard)
{
    long long int i = player.size();
    if (i == 0)
        return false;
    while (i > 0)
    {
        if (player.front() == newCard)
            return true;
        player.pop();
        i--;
    }
    return false;
}

/*****************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Overloads the == operator of the cards struct
  *
  * @param[in] card1 - first card to compare
  * @param[in] card2 - second card to compare
  *
  * @returns True if cards are equal
  * @returns False if cards aren't equal
  * @par Example
  * @verbatim
  * card card1;
  * card card2;
  * card1.faceValue = 3;
  * card1.suit = 0;
  * card2.faceValue = 3;
  * card2.suit = 0;
  * return card1 == card2; //returns True
  * @end verbatim
  *****************************************************************************/
bool operator==(card card1, card card2)
{
    if (card1.faceValue == card2.faceValue &&
        card1.suit == card2.suit)
        return true;
    return false;
}

/*****************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Overloads the << operator of ostreams for cards
  *
  * @param[in] out - ostream to output to
  * @param[in] card1 - Card to output
  *
  * @returns ostream with data - could be any type of stream.
  * 
  * @par Example
  * @verbatim
  * card1 card;
  * card1.faceValue = 3;
  * card1.suit = 0;
  * cout << card1; //prints "3H " To the console
  * @endverbatim
  *****************************************************************************/
ostream &operator<<(ostream& out, card card1)
{
    string suit;
    switch (card1.suit)
    {
    case 0:
        suit = "H";
        break;
    case 1:
        suit = "D";
        break;
    case 2:
        suit = "C";
        break;
    case 3:
        suit = "S";
        break;
    }
    out << card1.faceValue << suit;
    return out;
    
}
/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Overloads the << operator of ostreams for queues of cards
  *
  * @param[in] out - ostream to output to
  * @param[in] player - Queue of cards to output
  *
  * @returns ostream with data - could be any type of stream.
  * @par Example
  * @verbatim
  * queue<card> player; //Contains cards 25, 33
  * cout << player; //Prints "12D 33S " to the console
  * @endverbatim
  *****************************************************************************/
ostream &operator<<(ostream& out, queue<card> player)
{
    long long int j = player.size();
    string suit;
    int tempSuit;
    for (int i = 0; i < j; i++)
    {
        tempSuit = player.front().suit;
        switch (tempSuit)
        {
        case 0:
            suit = "H";
            break;
        case 1:
            suit = "D";
            break;
        case 2:
            suit = "C";
            break;
        case 3:
            suit = "S";
            break;
        }
        out << player.front().faceValue << suit << " ";
        player.pop();
    }
    return out;
}
/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Plays a round of the game of war given two players' decks
  *
  * @param[in] player1 - Player 1 deck of cards
  * @param[in] player2 - Player 2 deck of cards
  *
  * @par Example
  * @verbatim
  * queue<card> player1; //contains card 33
  * queue<card> player2; //contains card 11
  * playRound(player1, player2);
  * cout << player1; //outputs "" to the console
  * cout << player2; //outputs "33 11 " to the console
  * @endverbatim
  *****************************************************************************/
void playRound(queue<card>& player1, queue<card>& player2)
{
    int minCards;
    int player1Face;
    int player2Face;
    stacky<card> player1Dis;
    stacky<card> player2Dis;
    playerDiscard(player1, player1Dis);
    playerDiscard(player2, player2Dis);
    player1Face = player1Dis.topCard().faceValue;
    player2Face = player2Dis.topCard().faceValue;

    //Player 1 wins, picks up discard piles
    if (player1Face > player2Face)
    {
        playerPickup(player1, player2, player1Dis, player2Dis);
        return;
    }
    //Player 2 wins, picks up discard piles
    if (player2Face > player1Face)
    {
        playerPickup(player2, player1, player2Dis, player1Dis);
        return;
    }
   
    //If cards are equal
    do 
    {
        minCards = (int)min(player1.size(), player2.size());
        if (minCards == 0) //If out of cards
        {
            playerDraw(player1, player2, player1Dis, player2Dis);
            return;
        }
        for (int i = min(minCards, 3); i > 0; i--)
        {
            playerDiscard(player1, player1Dis);
            playerDiscard(player2, player2Dis);
        }
        player1Face = player1Dis.topCard().faceValue;
        player2Face = player2Dis.topCard().faceValue;
    } while (player1Face == player2Face);

    if (player1Face > player2Face)
    {
        playerPickup(player1, player2, player1Dis, player2Dis);
        return;
    }
    //Player 2 wins, picks up discard piles
    if (player2Face > player1Face)
    {
        playerPickup(player2, player1, player2Dis, player1Dis);
        return;
    }
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Simulates players picking up their hands after a round win.
  *
  * @param[in] playerWin - Deck round-winning player
  * @param[in] playerLose - deck of round-losing player
  * @param[in] disWin - Discarded deck of winning player
  * @param[in] disLose - Discarded deck of losing player
  *
  * @par Example
  * @verbatim
  * queue<card> playerWin; //contains card 33
  * stacky<card> disWin; //contains card 22
  * stacky<card> disLose; //contains card 3
  * queue<card> playerLose; //contains card 11
  * playerPickup(playerWin, playerLose, disWin, disLose);
  * cout << playerWin; //outputs "33 3 2" to the console (formatted with types)
  * cout << playerLose; //outputs "11 " to the console (formatted with types)
  * @endverbatim
  *****************************************************************************/
void playerPickup(queue<card>& playerWin, queue<card>& playerLose, stacky<card>& disWin, stacky<card>& disLose)
{
    int j = disLose.size();
    for (int i = 0; i < j; i++)
    {
        playerWin.push(disLose.topCard());
        disLose.remove();
    }
    j = disWin.size();
    for (int i = 0; i < j; i++)
    {
        playerWin.push(disWin.topCard());
        disWin.remove();
    }
    return;
}
/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Simulates a player discarding a card
  *
  * @param[in] player - Deck of player
  * @param[in] playerDis - Discard deck of player
  *
  * @par Example
  * @verbatim
  * queue<card> player; //contains card 33
  * stacky<card> playerDis; //contains nothing
  * playerDiscard(player, playerDis)
  * cout << player; //outputs ""
  * cout << playerDis; //outputs "33 " to the console (formatted with types)
  * @endverbatim
  *****************************************************************************/
void playerDiscard(queue<card>& player, stacky<card>& playerDis)
{
    playerDis.insert(player.front());
    player.pop();
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Simulates players picking up their own discard piles after a draw
  *
  * @param[in] player1 - Deck of player1
  * @param[in] player2 - Deck of player2
  * @param[in] player1Dis - Discard deck of player1
  * @param[in] player2Dis - Discard deck of player2
  *
  * @par Example
  * @verbatim
  * queue<card> player1; //contains card 33
  * queue<card> player2; //contains card 10
  * stacky<card> player1Dis; //contains 3
  * stacky<card> player2Dis; //contains 7
  * playerDraw(player1,player2, player1Dis, player2Dis);
  * cout << player1; //outputs "33 3 " to the console (formatted with types)
  * cout << player2; //outputs "10 7 " to the console (formatted with types)
  * @endverbatim
  *****************************************************************************/
void playerDraw(queue<card>& player1, queue<card>& player2, stacky<card>& player1Dis, stacky<card>& player2Dis)
{
    int j = player1Dis.size();
    for (int i = 0; i < j; i++)
    {
        player1.push(player1Dis.topCard());
        player1Dis.remove();
    }
    j = player2Dis.size();
    for (int i = 0; i < j; i++)
    {
        player2.push(player2Dis.topCard());
        player2Dis.remove();
    }
}