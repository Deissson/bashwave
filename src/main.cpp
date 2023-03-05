#include <include.hpp>
#include <internal.hpp>
#include <settings.hpp>
#include <tools.hpp>

int main()
{
    print(fg(color::blue_violet),
          "This project is under development! Please be patient, It will be released when it will be finished.\n");
    vector<string> options = {tools::flipACoin::NAME, tools::magicball::NAME, tools::search::NAME};
    init(options);
    int runTimes = 0;
    while (true)
    {
        if (runTimes == 5)
        {
            init(options);
            runTimes = 0;
        }

        string i = prompt("Choose an option");

        if (i == "0")
        {
            return 0;
        }
        else if (i == "ls")
        {
            init(options);
            runTimes = 0;
        }
        else if (i == "1")
        {
            COLOR = color::lawn_green;
            tools::flipACoin::flip();
        }
        else if (i == "2")
        {
            COLOR = color::lawn_green;
            tools::magicball::shake();
        }
        else if (i == "3")
        {
            COLOR = color::lawn_green;
            tools::search::go();
        }
        else if (i == "4")
        {
            COLOR = color::lawn_green;
            settings::show();
        }
        else if (
            i.empty())
        {
            COLOR = color::lawn_green;
        }
        else
        {
            print("\nInvalid Option!\n\n");
            COLOR = color::crimson;
        }
        runTimes++;
    }
}