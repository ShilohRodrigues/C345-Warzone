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
void Command::stringToLog(std::ostream &out) const {
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
void CommandProcessor::stringToLog(std::ostream &out) const {
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

#include "CommandProcessing.h"

// ... (rest of the code)
/*The function is used to parse commands for running our tournament */
bool CommandProcessor::parseTournamentCommand(const std::string& command) {
    //Declaring our ssObject
    std::stringstream ssObject(command);
    std::string token, mapFilesStr, playerStrategiesStr;
    int numGames = 0, maxTurns = 0;

    //verifying if users input is tournament
    ssObject >> token;
    if (token != "tournament") return false;

    //If tournament mode,
    while (ssObject >> token) {
        if (token == "-M") {
            ssObject >> mapFilesStr;
            //I'm not sure if we need to can use the mapValidater in map.h or would we need to implement a new one?
            cout << "-M works" << endl;
            // TODO: Validate mapFilesStr
        } else if (token == "-P") {
            ssObject >> playerStrategiesStr;
            cout << "-P works" << endl;
            //@shiloh need to figure out if we can use player validater by eugenie or need to figure out some other way.
            // TODO: Validate playerStrategiesStr
        } else if (token == "-G") {
            ssObject >> numGames;
            if (numGames < 1 || numGames > 5) return false;
        } else if (token == "-D") {
            ssObject >> maxTurns;
            if (maxTurns < 10 || maxTurns > 50) return false;
        } else {
            return false; // Unknown token
        }
    }

    // Check if all required parameters are set
    if (mapFilesStr.empty() || playerStrategiesStr.empty() || numGames == 0 || maxTurns == 0) {
        return false;
    }

    // If everything is valid, return true
    return true;
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