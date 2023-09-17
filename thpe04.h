/** *********************************************************************
 * @file
 *
 * @brief   Header files containing prototypes, includes, structs, and template classes.
 * @author Tristan Opbroek
 ***********************************************************************/
#pragma once
#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
using namespace std;
const bool runcatch = false;


/**
 * @brief Holds the data of a card, including it's face value and Suit
 */
struct card
{
    int faceValue; /**< Face value of card in struct, from 0-12, 0 is an Ace*/
    int suit; /**< Suit value of card in struct, from 0-3. 0 is hearts, 1 is diamonds, 2 is spades, and 3 is clubs */
};


/**
 * @brief template implementation of a stack.
 */
template <class type> 
class stacky //Apparently "stack" is a reserved word and it took me an hour to figure that out...
{
public:
    stacky();
    ~stacky();

    bool insert(type item);
    bool remove();
    int size();

    type topCard(); //literally no saftey in this function, if the stack is empty this will crash

private:
    /**
 * @brief Linked list of items of the class's type
 */
    struct node
    {
        type item; /** Current type in node */
        node* next; /** Pointer to next node*/
    };
    node* headptr; /** Pointer to the first node in the List*/

};

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Constructor for the stacky type class
  *
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * @endverbatim
  *****************************************************************************/
template <class type>
stacky<type>::stacky()
{
    headptr = nullptr;
}
/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Inserts a node into a stacky object
  * @param[in] item - item to insert into stack
  * @returns true if successful, and false otherwise
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * data.insert(3); //data now contains 3
  * @endverbatim
  *****************************************************************************/
template <class type>
bool stacky<type>::insert(type item)
{
    node* insert;
    insert = new (nothrow) node;
    if (insert == nullptr)
        return false;
    insert->next = headptr;
    insert->item = item;
    headptr = insert;
    return true;
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Returns an item at the top of the stack
  *
  * @returns Item at the top of stack
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * data.insert(3); //data now contains 3
  * data.insert(5); //data now contains 5, 3
  * int number = data.topCard(); //number is now 5
  * @endverbatim
  *****************************************************************************/
template <class type>
type stacky<type>::topCard()
{
    return headptr->item;
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Returns an item at the top of the stack
  *
  * @returns True if successful, false if not
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * data.insert(3); //data now contains 3
  * data.remove(); //Stack is now empty, 3 was removed
  * @endverbatim
  *****************************************************************************/
template <class type>
bool stacky<type>::remove()
{
    node* temp;
    if (headptr == nullptr)
        return false;
    temp = headptr;
    headptr = temp->next;
    delete temp;
    return true;
}

/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Returns the size of the stack
  *
  * @returns the size of the stack
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * data.insert(3); //data now contains 3
  * data.insert(7); //data now contains 3, 7
  * data.size(); //returns 2.
  * @endverbatim
  *****************************************************************************/
template <class type>
int stacky<type>::size()
{
    node* temp;
    int i;
    if (headptr == nullptr)
    {
        return 0;
    }
    temp = headptr;
    i = 0;
    while (temp != nullptr)
    {
        i++;
        temp = temp->next;
    }
    return i;
}
/** ***************************************************************************
  * @author Tristan Opbroek
  *
  * @par Description:
  * Deconstructor for stacky class.
  *
  * @verbatim
  * stacky<int> data; //created stack of integers.
  * data.insert(3); //data now contains 3
  * data.insert(7); //data now contains 3, 7
  * data.size(); //returns 2.
  * exit(0); //Exits program, memory is freed with this deconstructor
  * @endverbatim
  *****************************************************************************/
template <class type>
stacky<type>::~stacky()
{
    node* temp;
    node* lagTemp;
    if (headptr == nullptr)
        return;
    temp = headptr;
    lagTemp = headptr;
    while (temp != headptr)
    {
        temp = temp->next;
        delete lagTemp;
        lagTemp = temp;
    }
    return;
}


void getCards(queue<card>& player1, ifstream& fin);
void openFile(ifstream& fin, string file);
void getCardsRandom(queue<card>& player, int seed);
bool inQueue(queue<card> player, card newCard);
bool operator==(card card1, card card2);
ostream& operator<<(ostream& out, queue<card> player);
ostream& operator<<(ostream& out, card card1);
void playRound(queue<card>& player1, queue<card>& player2);
void playerPickup(queue<card>& playerWin, queue<card>& playerLose, stacky<card>& disWin, stacky<card>& disLose);
void playerDiscard(queue<card>& player, stacky<card>& playerDis);
void playerDraw(queue<card>& player1, queue<card>& player2, stacky<card>& player1Dis, stacky<card>& player2Dis);