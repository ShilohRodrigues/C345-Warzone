#ifndef COMMAND_PROCESSING //include guard
#define COMMAND_PROCESSING

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>
#include <string>
#include "LoggingObserver.h"

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

    Command getCommand(int index);
	  bool validate(Command cmd);
    void stringToLog(std::ostream &out) const override;

  protected:
    virtual string readCommand();
    void saveCommand(string cmd);

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
    string readCommand() override;

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

#endif //COMMAND_PROCESSING