#ifndef INTERNAL_HPP
#define INTERNAL_HPP
#include <include.hpp>
#include <iostream>

fmt::v9::color COLOR = color::lawn_green;
vector<string> TOOLS;
void init(vector<string> options)
{
    print("\n");
    for (int i = 0; i < options.size(); i++)
    {
        print("{}: {}\n", i + 1, options[i]);
    }
#ifdef USE_EMOJI
    print(fg(color::dim_gray), "{}: Settings ⚙️", options.size() + 1);
#else
    print(fg(color::dim_gray), "{}: Settings", options.size() + 1);
#endif
    print("\n\n");
    TOOLS = options;
}

void loading(const string& animation, float speed)
{
    float useconds = speed * 1000000 / 4;
    std::cout << animation << std::flush;
    usleep(useconds);
    std::cout << "." << std::flush;
    usleep(useconds);
    std::cout << "." << std::flush;
    usleep(useconds);
    std::cout << "." << std::flush;
    usleep(useconds);
    std::cout << std::endl;
}

// Taken from: https://www.tutorialspoint.com/how-to-check-if-input-is-numeric-in-cplusplus
bool isNumeric(string str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; // when one non-numeric value is found, return false
    return true;
}

string prompt(string prompt)
{
    std::signal(SIGINT, [](int handler) {
        std::cout << std::endl;
        loading("Exiting", 0.25);
        exit(0);
    });

    while (true)
    {
        string userInput;
        print("{} {}  ", prompt, fmt::format(fg(COLOR), ">>"));
        std::getline(std::cin >> std::skipws, userInput);
        if (std::cin.eof())
        {
            loading("Exiting", 0.25);
            exit(1);
        }
        else if (userInput == "")
        {
            COLOR = fmt::color::lawn_green;
        }
        else if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            COLOR = fmt::color::lawn_green;
        }
        else if ((userInput == "0") || (userInput == "exit"))
        {
            loading("Exiting", 0.25);
            return "0";
        }
        else if ((userInput == "cls") || (userInput == "clear"))
        {
            system("clear");
            COLOR = fmt::color::lawn_green;
        }
        else
        {
            return userInput;
        }
    }
}
#endif