// The Gamblers Production
//File: Blackjack.cpp
//Author: Christian, Henry, William
//Date: 04-01-2026
//Course: C++ Programming, CIS251
//Assignment: Group Project
//Description: Writing a C++



#include <iostream>
#include <cstdlib> // for random numbers
#include <ctime> // for time to help random number stay random
#include <cctype> // for toupper
#include <string> // for string
using namespace std;

// Functions
int GetsCardValue();
string GetsCardName(int value);
// Variable used to convert numbers to symbols
string GetCardSymbol(int value);

int PlayHand(bool IsDealer);
char getChoice();

int main()
{
    // Random number generator
    srand(time(0));
   
    char Again;
    int totalchips = 100;
    int playerWin = 0;
    int dealerWin = 0;
    int bet = 0;

    do
    {
        cout << "\n====================================\n";
        cout << " BLACKJACK GAME\n";
        cout << "====================================\n\n";

        // Betting system -Henry/William
        cout << "You start with " << totalchips << " chips\n";
        cout << "Choose your amount to bet (minimum bet: 10): ";
        cin >> bet;

        if (bet < 10)
        {
            cout << "You must bet 10 or more.\n";
            cout << "Play again? (Y/N): ";
            cin >> Again;
            Again = toupper(Again);
            continue;
        }

        if (bet > totalchips)
        {
            cout << "You don't have enough chips!\n";
            cout << "Play again? (Y/N): ";
            cin >> Again;
            Again = toupper(Again);
            continue;
        }

        totalchips = totalchips - bet;
        cout << "Your current number of chips is: " << totalchips << "\n\n";

        // Gives the player information -William
        cout << "Dealer's turn (one card hidden)...\n";
        int DealersTotal = PlayHand(true); // Dealer plays with hidden first card
       
        cout << "\nYour turn...\n";
        int YourTotal = PlayHand(false);

        // Results
        cout << "\n====================================\n";
        cout << "RESULTS:\n";
        cout << "Your total: " << YourTotal << endl;
        cout << "Dealer total: " << DealersTotal << endl;

        // Checks if the player won or the dealer
        playerWin = 0;
        dealerWin = 0;

        if (YourTotal > 21)
        {
            cout << "You busted! Dealer wins.\n";
            dealerWin = 1;
        }
        else if (DealersTotal > 21)
        {
            cout << "Dealer busted! You win!\n";
            playerWin = 1;
        }
        else if (YourTotal > DealersTotal)
        {
            playerWin = 1;
            dealerWin = 0;
            cout << "You win!\n";
        }
        else if (DealersTotal > YourTotal)
        {
            playerWin = 0;
            dealerWin = 1;
            cout << "Dealer wins.\n";
        }
        else
        {
            cout << "It's a tie (push)!\n";
            totalchips += bet;
        }

        // Update chips based on win/loss
        if (playerWin == 1)
        {
            bet = bet * 2;
            totalchips = totalchips + bet;
            cout << "You won " << bet << " chips!\n";
        }
        else if (dealerWin == 1)
        {
            cout << "You lost your bet.\n";
        }

        cout << "You now have " << totalchips << " chips.\n";

        // Adds a replay function
        cout << "\nPlay again? (Y/N): ";
        cin >> Again;
        Again = toupper(Again);
       
    } while (Again == 'Y' && totalchips >= 10);

    // The credits
    cout << "\n Made by The Gamblers for The Gamblers!\n";
    cout << "\n Thanks for playing\n";
    return 0;
}

// Returns the value to transfer to cards.
int GetsCardValue()
{
    int value = rand() % 13 + 1; // 1 to 13

    if (value >= 10) 
        return 10;
    else if (value == 1) 
        return 11;
    else
        return value;
}

// Returns the card symbol instead of numbers Christian/William
string GetCardSymbol(int value)
{
    if(value==1)  return "🂡";
    else if(value==2) return "🂢";
    else if(value==3) return "🂣";
    else if(value==4) return "🂤";
    else if(value==5) return "🂥";
    else if(value==6) return "🂦";
    else if(value==7) return "🂧";
    else if(value==8) return "🂨";
    else if(value==9) return "🂩";
    else if(value==10)return "🂪";
    else if(value==11)return "🂫";
    else if(value==12)return "🂭";
    else if(value==13)return "🂮";
    return "";
}

/* Card images
This ones the back of a card for the dealer
🂠
1 = 🂡
2 = 🂢
3 = 🂣
4 = 🂤
5 = 🂥
6 = 🂦
7 = 🂧
8 = 🂨
9 = 🂩
10 =🂪
11 = 🂫
12 = 🂭
13 = 🂮
Bet: [Number]
Minimum bet 10
*/

// Returns a simple string name for the card also detects if number = ace
string GetsCardName(int value)
{
    if (value == 11)
        return "Ace";
    else if (value == 10)
        return "10";
    else
        return to_string(value);
}

// Plays one hand (player or dealer) - William
int PlayHand(bool IsDealer)
{
    int total = 0;
    int NumberAces = 0;
    bool FirstCard = true;
    int cardValue;
   
    // Starter cards
    for (int i = 0; i < 2; i++)
    {
        cardValue = GetsCardValue();
        total += cardValue;
        if (cardValue == 11) NumberAces++;
       
        if (IsDealer && FirstCard)
        {
            cout << "Dealer shows: 🂠\n";
            FirstCard = false;
            continue;
        }
        else
        {
            // Exact format you requested: You drew: 🂪 (10 points)
            cout << (IsDealer ? "Dealer" : "You") 
                 << " drew: " << GetCardSymbol(cardValue)
                 << " (" << cardValue << " points)\n";
        }
    }
   
    // Adjust aces
    while (total > 21 && NumberAces > 0)
    {
        total -= 10;
        NumberAces--;
    }
   
    // Continue drawing
    while ((IsDealer && total < 17) || (!IsDealer && total <= 21))
    {
        if (!IsDealer)
        {
            cout << "Your current total: " << total << endl;
            char choice = getChoice();
            if (choice != 'H')
                break;
        }
       
        cardValue = GetsCardValue();
        total += cardValue;
        if (cardValue == 11) NumberAces++;
       
        cout << (IsDealer ? "Dealer" : "You")
             << " drew: " << GetCardSymbol(cardValue)
             << " (" << cardValue << " points)\n";
       
        while (total > 21 && NumberAces > 0)
        {
            total -= 10;
            NumberAces--;
        }
       
        if (total > 21)
            break;
    }
   
    if (IsDealer)
        cout << "Dealer final total: ?";
    else
        cout << "Your final total: " << total << endl;
   
    return total;
}

// Ask Hit or Stand choice - William
char getChoice()
{
    char choice;
    do
    {
        cout << "Hit (H) or Stand (S)? ";
        cin >> choice;
        choice = toupper(choice);
    } while (choice != 'H' && choice != 'S');
   
    return choice;
}



