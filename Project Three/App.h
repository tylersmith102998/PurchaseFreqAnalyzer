#ifndef APP_H 
#define APP_H 

#include <functional>
#include <string>
#include <map>

#include "DataStore.h"

using namespace std;

class App {
public:
	App();
	void Run();
private:
	struct Command {
		string label;
		function<void(App&)> action;
	};
	map<int, Command> commands;

	bool isRunning = true;

	DataStore dataStore;

	void InitCommands();

	void PrintMenu();

	template<typename T>
	T GetInput(const string& prompt);

	void Search();
	void PrintFrequencies();
	void PrintHistogram();
	void ExitProgram();
};

#endif // APP_H