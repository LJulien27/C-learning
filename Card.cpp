#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

/*char *hearts  = "\x03";  //♥
char *diamond = "\x04";  //♦
char *clubs   = "\x05";  //♣
char *spades  = "\x06";  //♠*/

using namespace std;

class Cards
{
public:
    string suits[4] = {"\x03", "\x04", "\x05", "\x06"};
    string values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    string deck[52];

    void makeDeck()
    {
        for (int x = 0; x < (sizeof(suits) / sizeof(suits[0])); x++)
        {
            for (int y = 0; y < (sizeof(values) / sizeof(values[0])); y++)
            {
                deck[(x * 13) + y] = values[y] + suits[x];
            }
        }
    }

    void shuffleDeck()
    {
        srand(time(NULL));
        int r1;
        string hold;

        for (int x = 0; x < (sizeof(deck) / sizeof(deck[0])); x++)
        {
            r1 = rand() % 52;
            hold = deck[x];
            deck[x] = deck[r1];
            deck[r1] = hold;
        }
    }

    int cardValue(string card, bool x)
    /* takes in the a card and a boolean
    the bool represents whether or not theres an ace with the value of 11 in the hand
    returns 10 for 10, J, Q, K
    returns 11 for A but will return 1 if theres already an A with the value of 11 in the hand */
    {
        if (card.at(1) == '0')
        {
            return 10;
        }
        if (card.at(0) == 'J')
        {
            return 10;
        }
        if (card.at(0) == 'Q')
        {
            return 10;
        }
        if (card.at(0) == 'K')
        {
            return 10;
        }
        if (card.at(0) == 'A' && x == false)
        {
            return 11;
        }
        if (card.at(0) == 'A' && x == true)
        {
            return 1;
        }
        else
        {
            return card.at(0) - 48;
        }
    }

    int blackjack(int money)
    {
        // initialization of variables
        int bet;
        int bands = money;
        int cc = 4;
        bool hit = true;
        int ph = 0;
        int dh = 0;
        bool bj = false;
        bool p11 = false;
        bool d11 = false;
        int pi = 2;
        int di = 2;

        cout << "How much money would you like to bet this round? ";
        cin >> bet;
        cout << "Your cards are: " + deck[0] + " and " + deck[1] << endl;
        ph = ph + cardValue(deck[0], p11);
        if (cardValue(deck[0], p11) == 11)
        {
            p11 = true;
        }
        ph = ph + cardValue(deck[1], p11);
        if (cardValue(deck[1], p11) == 11)
        {
            p11 = true;
        }
        cout << "Your hand is worth: " << ph << endl;
        cout << "I have a: " + deck[2] + " and an unknown card" << endl;
        dh = dh + cardValue(deck[2], d11);
        if (cardValue(deck[2], d11) == 11)
        {
            d11 = true;
        }
        dh = dh + cardValue(deck[3], d11);
        if (cardValue(deck[3], d11) == 11)
        {
            d11 = true;
        }
        if (dh == 21)
        {
            cout << "I have a: " + deck[2] + " and a " + deck[3] + "so I have blackjack I win" << endl;
            bands = bands - bet;
            return bands;
        }

        // determines whether of not player has a blackjack off the start
        if (ph == 21)
        {
            bj = true;
        }

        // player getting choice to pick up cards
        while (ph < 21 && hit)
        {
            cout << "Would you like another card? ";
            cin >> hit;
            if (hit)
            {
                cout << "You picked up: " + deck[cc] << endl;
                ph = ph + cardValue(deck[cc], p11);
                if (cardValue(deck[cc], p11) == 11)
                {
                    p11 = true;
                }
                if (ph > 21 && p11 == true)
                {
                    ph = ph - 10;
                }
                cout << "Your hand is worth: " << ph << endl;
                cc++;
            }
        }
        if (ph > 21)
        {
            cout << "My cards are: " + deck[2] + " and " + deck[3] << endl;
            cout << "You busted I win pause" << endl;
            bands = bands - bet;
            return bands;
        }

        cout << "My cards are: " + deck[2] + " and " + deck[3] << endl;
        cout << "My hand is worth: " << dh << endl;
        // dealer picking up cards
        while (dh < 17)
        {
            cout << "I picked up: " + deck[cc] << endl;
            dh = dh + cardValue(deck[cc], d11);
            if (cardValue(deck[cc], d11) == 11)
            {
                d11 = true;
            }
            if (dh > 21 && d11 == true)
            {
                dh = dh - 10;
            }
            cout << "My hand is worth: " << dh << endl;
            cc++;
        }
        if (dh > 21)
        {
            cout << "I overdrew the cards you win" << endl;
            bands = bands + bet;
            return bands;
        }

        // determine the outcome of the game
        if (bj)
        {
            cout << "Congratulations you win" << endl;
            bands = bands + bet * 1.5;
        }
        else if (ph > dh)
        {
            cout << "Congratulations you win" << endl;
            bands = bands + bet;
        }
        else if (dh > ph)
        {
            cout << "I have won this round" << endl;
            bands = bands - bet;
        }
        else if (ph == dh)
        {
            cout << "We have a draw this round" << endl;
            bands = bands;
        }

        return bands;
    }
};

int main()
{
    cout << "Deck of cards" << endl;
    Cards cards;
    int cash;
    bool game;

    cards.makeDeck();
    cards.shuffleDeck();

    for (int x = 0; x < (sizeof(cards.deck) / sizeof(cards.deck[0])); x++)
    {
        cout << cards.deck[x] + " ";
    }
    cout << endl;
    cout << "Deck size: " << sizeof(cards.deck) / sizeof(cards.deck[0]) << endl;

    cout << "Would you like to play blackjack? ";
    cin >> game;

    cout << "How much money would you like to play with? ";
    cin >> cash;

    while (game)
    {
        cash = cards.blackjack(cash);
        cout << "You have this much money left: " << cash << endl;
        cout << "Would you like to play another round? ";
        cards.shuffleDeck();
        cin >> game;
    }
}
