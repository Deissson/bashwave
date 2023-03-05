#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <include.hpp>
#include <internal.hpp>
#include <tools.hpp>

using namespace tools;

class settings : public flipACoin, public search {
 public:
  static void show() {
    int j;
    print("\n\n");
    for (int i = 0; i < TOOLS.size(); i++) {
      print("{}: {}'s Settings \n", i + 1, TOOLS[i]);
    }
    print(fg(color::dim_gray), "{}: About Bashwave\n\n", TOOLS.size() + 1);
  CHOOSE:
    string choose = prompt("Settings: Choose a tool");
    if (!isNumeric(choose)) {
      print("\n{}: This tool only accepts numbers!\n\n",
            fmt::format(fg(color::crimson), "ERR"));
      goto CHOOSE;

    } else {
      j = stoi(choose);
    }

    switch (j) {
    case 0:
      return;
    case 1:
      flipACoin::settings();
      break;
    case 3:
      search::settings();
      break;
    case 4:
      print("yet another tool set\n");
      break;
    default:
      print("\nNo setting for this tool.\n\n");
    }
  };
};
#endif