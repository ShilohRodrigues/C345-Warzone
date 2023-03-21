#ifndef COMMAND_PROCESSING //include guard
#define COMMAND_PROCESSING

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>
#include <string>
#include "LoggingObserver.h"
#include "GameEngine.h"

using namespace std;

class CommandProcessor;
class FileCommandProcessorAdapter;
class Command;
class FileLineReader;

class Command : public virtual Subject, public virtual ILoggable {
  
  public:
    Command(string c);
    ~Command();
    Command& operator=(const Command& c);
    Command(const Command &c);
    friend ostream& operator<<(ostream& strm, const Command& c);
    void saveEffect(string e);
    string getName();

    //Part 5
    void stringToLog(std::ostream &out) const override;
  private:
    string command;
    string effect;

};

//Target Class
class CommandProcessor: public virtual Subject, public virtual ILoggable {

  public:
    CommandProcessor();
    ~CommandProcessor();
    CommandProcessor& operator=(const CommandProcessor& cp);
    CommandProcessor(const CommandProcessor &cp);
    friend ostream& operator<<(ostream& strm, const CommandProcessor& cp);

    Command getCommand(GameEngine &game);
	  bool validate(Command cmd, GameEngine &game);
    void stringToLog(std::ostream &out) const override;

  protected:
    virtual Command readCommand();
    void saveCommand(Command cmd);

  private: 
    vector<Command> commands;

};

//Adapter Class (Adapts FileLineReader to the CommandProcessor)
class FileCommandProcessorAdapter : public CommandProcessor {
  
  public:
    FileCommandProcessorAdapter(string filename);
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& fp);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fp);
    friend ostream& operator<<(ostream& strm, const FileCommandProcessorAdapter& fp);
  
  protected:
    Command readCommand() override;

  private:
    shared_ptr<FileLineReader> flr;

};

//Adaptee Class
class FileLineReader {

  public:
    FileLineReader();
    FileLineReader(string filename);
    ~FileLineReader();
    FileLineReader& operator=(const FileLineReader& f);
    FileLineReader(const FileLineReader &f);
    friend ostream& operator<<(ostream& strm, const FileLineReader& f);
    string readLineFromFile();

  private:
    shared_ptr<ifstream> file;

};

int CommandProcessingDriverDemo(GameEngine &game, string fileName);

#endif //COMMAND_PROCESSING