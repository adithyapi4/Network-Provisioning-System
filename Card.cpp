#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>
#include "Payment.h"
#include "Card.h"

void Card::get_payment_details()
{
    std::cout << "Enter your card number: ";
    std::cin >> card_no;
    std::cout << "Enter the expiry: ";
    std::cin >> expiry;
    std::cout << "Enter card holder's name: ";
    std::cin >> card_holder_name;

    validate_card_details();
}

void Card::validate_card_details()
{
    int i{};
    unsigned int card_no_sum{};
    int card_no_int[20];
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    int MM = localTime->tm_mon + 1;
    int YY = (localTime->tm_year + 1900) % 100;

    if ((card_no.length() > 19) || (card_no.length() < 12))
    {
        validity = false;
    }

    if (expiry.length() != 5 || expiry[2] != '/')
    {
        validity = false;
    }

    int card_MM = ((expiry[0] - '0') * 10) + (expiry[1] - '0');
    int card_YY = ((expiry[3] - '0') * 10) + (expiry[4] - '0');

    if (!((card_MM > 0) && (card_MM < 13)))
    {
        validity = false;
    }

    if (!((card_YY >= 0) && (card_YY < 100)))
    {
        validity = false;
    }

    if (card_YY == YY)
    {
        if (card_MM < MM)
        {
            validity = false;
        }
    }
    else if (card_YY < YY)
    {
        validity = false;
    }
    else
    {
        validity = true;
    }

    for (char c : card_no)
    {
        int digit = (c - '0');
        if (!((digit >= 0) && (digit <= 9)))
        {
            validity = false;
        }
        card_no_int[i++] = digit;
    }
    card_no_int[i] = -1;

    for (int j = i - 2; j >= 0; j -= 2)
    {
        card_no_int[j] *= 2;
        if (card_no_int[j] > 9)
        {
            card_no_int[j] -= 9;
        }
    }

    for (--i; i >= 0; i--)
    {
        card_no_sum += card_no_int[i];
    }

    if ((card_no_sum % 10) != 0)
    {
        validity = false;
    }
    else
    {
        validity = true;
    }
}

bool Card::make_payment()
{
    if (validity == false)
    {
        return false;
    }

    std::cout << "Enter the CVV: ";
    std::cin >> std::ws;
    std::cin >> cvv;

    std::cout << "Please wait while we process your transaction..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Transaction Successful!" << std::endl;
    return true;
}