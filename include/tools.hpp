#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <include.hpp>

namespace tools {
class flipACoin {
 public:
  static constexpr string NAME = "Flip A Coin";
  static constexpr string CLINAME = "coinflip";
  static void flip() {
    vector<string> result;
  TIMES:
    string times = prompt("How many times toss a coin?");
    long int t;
    if (!isNumeric(times)) {
      print("\n{}: This tool only accepts numbers!\n\n",
            fmt::format(fg(color::crimson), "ERR"));
      goto TIMES;
    } else {
      t = stoi(times);
    }
    switch (t) {
    case 0:
      return;

    case 1:
      coinflip(1);
      break;

    default:
      for (int i = 0; i < t; i++) {
        string flop = coinflip(0.5);
        result.push_back(flop);
      }
      print("--------------------\n");
      for (auto& i : result) {
        print("{}\t", i);
      }
      double tailsCount = std::count(result.begin(), result.end(), "Tails");
      double headsCount = std::count(result.begin(), result.end(), "Heads");
      print("\n\nHeads: {:.1f}%\n", headsCount / result.size() * 100);
      print("Tails: {:.1f}%\n", tailsCount / result.size() * 100);
      print("\n");
      break;
    }
  }

 private:
  static string coinflip(float speed) {
    string choice[] = {"Heads", "Tails"};
    if (!DISABLE_LOADING) loading("Flipping", speed);
    string flip = choice[rand() % 2];
    if (!DISABLE_LOADING) print("{}\n", flip);
    return flip;
  }

 protected:
  static inline bool DISABLE_LOADING = false;
  static void settings() {
    int i;
    print("\n1: Disable Loading per flip = {}\n\n", DISABLE_LOADING);
  OPTIONS:
    string options = prompt("Settings: Choose an option to change");
    if (!isNumeric(options)) {
      print("\n{}: This tool only accepts numbers!\n\n",
            fmt::format(fg(color::crimson), "ERR"));
      goto OPTIONS;
    } else {
      i = stoi(options);
    }
    if (i == 1) {
      if (!DISABLE_LOADING)
        DISABLE_LOADING = true;
      else
        DISABLE_LOADING = false;
      print("\nChanged Disable Loading per flip to {}\n\n", DISABLE_LOADING);
    } else {
      print("\nNo such option\n");
    }
  }
};

class magicball {
 public:
  static constexpr string NAME = "Magic 8 Ball";
  static constexpr string CLINAME = "8ball";

  static void shake() {
    string question = prompt("Enter your question");
    vector<int> state = {1, 2, 3};
    vector<string> choice_positive = {"It is certain.", "Most likely.",
                                      "Outlook good.", "Without a doubt.",
                                      "Yes."};
    vector<string> choice_unsure = {
        "Reply hazily, try again.", "Ask again later.",
        "Better not tell you now.", "Cannot predict now.",
        "Concentrate and ask again."};
    vector<string> choice_negative = {"Don't count on it.", "My reply is no.",
                                      "My sources say no.",
                                      "Outlook not so good.", "Very doubtful."};
    switch (state[rand() % state.size()]) {
    case 1:
      print("{}\n", choice_positive[rand() % choice_positive.size()]);
      break;
    case 2:
      print("{}\n", choice_unsure[rand() % choice_unsure.size()]);
      break;
    case 3:
      print("{}\n", choice_negative[rand() % choice_negative.size()]);
      break;
    }
  }
};

class search {
 public:
  static constexpr string NAME = "Search";
  static constexpr string CLINAME = "search";

  static void go() {
    string search = prompt("Enter your search");
    if (search[0] == '!' && search.size() >= 2) {
      std::string command = search.substr(1, 1);
      switch (command[0]) {
      case 'w': {
        web();
        break;
      }
      case 'f': {
        files();
        break;
      }
      case 't': {
        tools();
        break;
      }
      default: {
        files();
        break;
      }
      }
    }
  }

 private:
  static void web() {
    string web = prompt(
        fmt::format("Search through the web (engine: {})", WEB_SEARCHENGINE));
  }
  static void files() {
    string files = prompt(fmt::format(
        "Search through your files (location: {})", DEFAULT_FILE_SEARCH));
  }
  static void tools() { string tools = prompt("Search through your tools"); }

 protected:
  static inline string DEFAULT_PROVIDER = "f";
  static inline string WEB_SEARCHENGINE = "google";
  static inline string DEFAULT_FILE_SEARCH = "home";

  static void settings() {
    switch (DEFAULT_PROVIDER[0]) {
    case 'w':
      print("\n1: Default Search provider = Web\n");
      break;
    case 'f':
      print("\n1: Default Search provider = Files\n");
      break;
    case 't':
      print("\n1: Default Search provider = Tools\n");
      break;
    default:
      print("\n1: Default Search provider = Unknown\n");
      break;
    }
    string choice = prompt("Settings: Choose a setting to change");
    print("\n2: Default File search location = {}\n", DEFAULT_FILE_SEARCH);
    print("\n3: Default Web Search Engine = {}\n", WEB_SEARCHENGINE);
    while (choice == "1") {
      string provider =
          prompt("Choose a default search provider (Web, Files, Tools)");
      switch (tolower(provider[0])) {
      case 'w':
        DEFAULT_PROVIDER = "w";
        break;
      case 'f':
        DEFAULT_PROVIDER = "f";
        break;
      case 't':
        DEFAULT_PROVIDER = "t";
        break;
      default:
        print("No such provider");
        break;
      }
    }
    print("\nSuccessfully changed Search Provider\n");
  }
};
}  // namespace tools
#endif