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
void Command::saveEffect(string e) {
  effect = e;
}

///////////// CommandProcessor class implementations /////////////////////
//Constructor
CommandProcessor::CommandProcessor() {
  
}
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
Command CommandProcessor::getCommand(int index) {
  if (index < 0 || index >= commands.size()) return Command("");
  return commands[index];
}
//Read command from the console
string CommandProcessor::readCommand() {
  string cmd;
  getline(cin, cmd);
  return cmd;
}
//Save a command in the vector of commands
void CommandProcessor::saveCommand(string cmd) {
  commands.push_back(*(new Command(cmd)));
}
//Check if the command is valid
bool CommandProcessor::validate(Command cmd) {
  //// TO DO
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
string FileCommandProcessorAdapter::readCommand() {
  return flr->readLineFromFile();
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
  
  //Need to do copy constructor !!!!!!!!!!!!!

}
//Assignment Operator
FileLineReader& FileLineReader::operator=(const FileLineReader& f) {

  //Need to do assignment operator !!!!!!!!!!!!!

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
  else return "All commands have been read.";
}


//Driver for Demonstration
int CommandProcessingDriverDemo(string fileName = "") {

    CommandProcessor* cp;
    string cmd;

    if (fileName != "") {
        cp = new FileCommandProcessorAdapter(fileName);
    } 
    else {
        cp = new CommandProcessor();
        cout << "Enter a command: ";
        //cmd = cp->readCommand();
    }

    delete cp;
    return 0;
}