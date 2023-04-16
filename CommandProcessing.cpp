#include "CommandProcessing.h"
using namespace std;

///////////// Command class implementations /////////////////////
//Constructor
Command::Command(string c) {
  command = c;
}
//Destructor
Command::~Command() {

}
//Copy constructor
Command::Command(const Command &c) {
  command = c.command;
  effect = c.effect;
}
//Assignment Operator
Command& Command::operator=(const Command& c) {
  if(this == &c) return *this;
  this->command = c.command;
  this->effect = c.effect;
  return *this;
}
//Insertion stream
ostream& operator<<(ostream &strm, const Command &c) {
  return strm << "Command: " << c.command << ", Effect: " << c.effect << endl;
}
//Save effect method
void Command::stringToLog(ostream &out) const {
    out << "Command: Saved Effect";
}
void Command::saveEffect(string e) {
  effect = e;
  notify(this);
}
string Command::getName() {
  return command;
}

///////////// CommandProcessor class implementations /////////////////////
//Constructor
CommandProcessor::CommandProcessor() {  }
//Destructor
CommandProcessor::~CommandProcessor() {

}
//Copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor &cp) {
  commands = cp.commands;
}
//Assignment Operator
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& cp) {
  if(this == &cp) return *this;
  this->commands = cp.commands;
  return *this;
}
//Insertion stream
ostream& operator<<(ostream &strm, const CommandProcessor &cp) {
  strm << "Command List: ";
  for(auto &cmd : cp.commands) {
    strm << cmd << "; ";
  }
  return strm;
}
//Return specific command 
Command CommandProcessor::getCommand(GameEngine &game) {
  
  Command cmd = this->readCommand();
  if (!(cmd.getName() == "End of file")) {
    saveCommand(cmd);
    if (!validate(cmd, game)) cmd.saveEffect("Invalid Command");
  }
  return cmd.getName();

}
//Read command from the console
Command CommandProcessor::readCommand() {
  string cmd;
  getline(cin, cmd);
  return  *(new Command(cmd));
}
void CommandProcessor::stringToLog(ostream &out) const {
    out << "Commands Effect: Save Command";
}
//Save a command in the vector of commands
void CommandProcessor::saveCommand(Command cmd) {
  commands.push_back(cmd);
  notify(this);
}
//Check if the command is valid
bool CommandProcessor::validate(Command cmd, GameEngine &game) {
  
  if (game.getState()->checkCommand(cmd.getName())) return true;
  else return false;

}

//Helper function to split strings by the separator char.
vector<string> split1(string str, char separator) {
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

///////////// FileCommandProcessorAdapter class implementations /////////////////////
//Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filename) {
  flr = make_shared<FileLineReader>(filename);
}
//Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {

}
//Copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fp) {
  flr = make_shared<FileLineReader>(*fp.flr);
}
//Assignment Operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& fp) {
  if(this == &fp) return *this;
  this->flr = fp.flr;
  return *this;
}
//Insertion stream
ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &fp) {
  return strm << "";
}
//Reads the next command in the file
Command FileCommandProcessorAdapter::readCommand() {
  return *(new Command(flr->readLineFromFile()));
}
 
///////////// FileLineReader class implementations /////////////////////
//Constructor
FileLineReader::FileLineReader() {
  file = nullptr;
}
FileLineReader::FileLineReader(string filename) {
  file = make_shared<ifstream>(filename);
}
//Destructor
FileLineReader::~FileLineReader() {
  
}
//Copy constructor
FileLineReader::FileLineReader(const FileLineReader &f) {
  file = nullptr;
}
//Assignment Operator
FileLineReader& FileLineReader::operator=(const FileLineReader& f) {
  file = f.file;
  return *this;
}
//Insertion stream
ostream& operator<<(ostream &strm, const FileLineReader &cp) {
  return strm << "";
}
//Read next line in the file
string FileLineReader::readLineFromFile() {
  string line = "";
  if (file != nullptr && getline(*file, line)) return line;
  else return "End of file";
}

int CommandProcessingDriverDemo(GameEngine &game, string fileName) {

  CommandProcessor* cp;
  string cmd;
  bool file;

  if (fileName != "") {
    file = true;
    cp = new FileCommandProcessorAdapter(fileName);
  } 
  else {
    file = false;
    cp = new CommandProcessor();
  }

  while(true) {

    //print current state of the game 
    cout << game << endl << endl;

    if (!file) cout << "Enter a command to continue: ";
    else cout << "Reading next command from file.." << endl;

    //Get entered command
    Command c = cp->getCommand(game);

    if (c.getName() == "quit" || c.getName() == "End of file") break;

    cout << "Command entered: " << c.getName() << endl;
    
    cout << "Validating command.." << endl;
    if (!cp->validate(c, game)) {
      cout << "You entered an invalid command." << endl << endl;
      continue;
    }

    //Enter tournament mode
    if (c.getName().find("tournament") != string::npos) {
      //Parse and validate command 
      vector<string> maps, players;
      int numGames = 0, maxTurns = 0;

      // Parse the command
      string command = c.getName();
      istringstream iss(command);
      vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>{});

      // Parse the tokens
      for (int i = 1; i < tokens.size(); i += 2) {
          string token = tokens[i];
          string arg = tokens[i + 1];
          if (token == "-M") {
              // Parse ListOfMaps
              string delimiter = ",";
              size_t pos = 0;
              while ((pos = arg.find(delimiter)) != string::npos) {
                  string map = arg.substr(0, pos);
                  maps.push_back(map);
                  arg.erase(0, pos + delimiter.length());
              }
              maps.push_back(arg);
              if (maps.size() < 1 || maps.size() > 5) {
                  cout << "Invalid tournament command" << endl;
                  return 0; // invalid number of maps
              }
          } else if (token == "-P") {
              // Parse ListOfPlayers
              string delimiter = ",";
              size_t pos = 0;
              while ((pos = arg.find(delimiter)) != string::npos) {
                  string player = arg.substr(0, pos);
                  players.push_back(player);
                  arg.erase(0, pos + delimiter.length());
              }
              players.push_back(arg);
              if (players.size() < 2 || players.size() > 4) {
                  cout << "Invalid tournament command" << endl;
                  return 0; // invalid number of players
              }
          } else if (token == "-G") {
              // Parse NumberOfGames
              try {
                  numGames = stoi(arg);
                  if (numGames < 1 || numGames > 5) {
                      cout << "Invalid tournament command" << endl;
                      return 0; // invalid number of games
                  }
              } catch (...) {
                  return false; // invalid number format
              }
          } else if (token == "-D") {
              // Parse maxNumberOfTurns
              try {
                  maxTurns = stoi(arg);
                  if (maxTurns < 10 || maxTurns > 50) {
                      cout << "Invalid tournament command" << endl;
                      return 0; // invalid number of turns
                  }
              } catch (...) {
                  cout << "Invalid tournament command" << endl;
                  return 0; // invalid number format
              }
          } else {
              cout << "Invalid tournament command" << endl;
              return 0; // invalid token
          }
      }
      
      runTournamentMode(game, maps, players, numGames, maxTurns);
      return 0;
    }

    cout << "Command is valid!" << endl;
    int status = game.nextState(c.getName());
    if (status == 0 && c.getName() == "gamestart") {
      cout << endl << "Entering assign reinforcement phase." << endl << endl;
      break;
    } 

  }

  if (file) cout << "All commands have been read from the file." << endl;

  return 0;
}

void runTournamentMode(GameEngine &game, vector<string> maps, vector<string> players, int numGames, int maxTurns) {

  //Loop for each map
  for (auto &map:maps) {
    //Loop for each game
    for (int i=0; i<numGames; i++) {
      //Load the current map
      if (game.nextState("loadmap " + map) == 1) {
        cout << "Invalid map name entered. Quitting tournament mode." << endl;
        return;
      }
      //Validate the map
      if (game.nextState("validatemap") == 1) {
        cout << "Map could not be validated. Quitting tournament mode." << endl;
        return;
      }
      //Add players
      for (auto &player:players) {
        if (game.nextState("addplayer") == 1) {
          cout << "Player could not be added. Quitting tournament mode." << endl;
          return;
        }
      }

      //Start the game
      game.nextState("gamestart");

      game.resetGame();

    }
  }

}