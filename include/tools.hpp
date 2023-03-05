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
      auto tailsCount = static_cast<double>(
          std::count(result.begin(), result.end(), "Tails"));
      auto headsCount = static_cast<double>(
          std::count(result.begin(), result.end(), "Heads"));
      print("\n\nHeads: {:.1f}%\n",
            headsCount / static_cast<double>(result.size()) * 100);
      print("Tails: {:.1f}%\n",
            tailsCount / static_cast<double>(result.size()) * 100);
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
    std::map<char, string> providers = {
        {'w', "Web"}, {'t', "Tools"}, {'f', "Files"}};
    print("\n1: Default Search provider = {}\n",
          providers[static_cast<char>(tolower(DEFAULT_PROVIDER[0]))]);
    print("\n2: Default File search location = {}\n", DEFAULT_FILE_SEARCH);
    print("\n3: Default Web Search Engine = {}\n\n", WEB_SEARCHENGINE);
    string choice = prompt("Settings: Choose a setting to change");
    if (choice == "1") {
      while (true) {
        string provider =
            prompt("Choose a default search provider (Web, Files, Tools)");
        char providerKey = static_cast<char>(tolower(provider[0]));
        if (providers.find(providerKey) != providers.end()) {
          DEFAULT_PROVIDER = providerKey;
          print("\nSuccessfully changed Search Provider to {}\n",
                providers[providerKey]);
          break;
        } else {
          print("No such provider!");
        }
      }
    } else if (choice == "3") {
      while (true) {
        string _raw_engine =
                   prompt("Choose a Search Engine (Google, DuckDuckGo, Bing)"),
               engine;
        for (auto i : _raw_engine) engine += static_cast<char>(tolower(i));

        if (engine == "duckduckgo") {
          WEB_SEARCHENGINE = "duckduckgo";
          break;
        } else if (engine == "google") {
          WEB_SEARCHENGINE = "google";
          break;
        } else if (engine == "bing") {
          WEB_SEARCHENGINE = "bing";
          break;
        } else {
          print("No such search engine!\n");
        }
      }
      print("Successfully changed Web Search Engine to {}\n", WEB_SEARCHENGINE);
    } else {
      print("\nNo such setting\n");
    }
  }
};
}  // namespace tools
#endif