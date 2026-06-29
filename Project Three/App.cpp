#include "App.h"

#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <iomanip>

// Constructor initializes the command map.
App::App() {
	// Initialize the commands.
	this->InitCommands();
}

// Main loop of the application. Displays the menu and processes user input.
void App::Run() {
	while (this->isRunning) {
		this->PrintMenu();

		// Get user input for menu choice.
		int choice = this->GetInput<int>("Enter your choice: ");

		// Validate the choice and execute the corresponding command.
		auto it = this->commands.find(choice);
		if (it != this->commands.end()) {
			it->second.action(*this);
		} else {
			cout << "Invalid choice. Please try again." << endl;
		}

		cout << endl;
	}
}

// Prints the menu options to the user.
void App::PrintMenu() {
	cout << "Corner Grocer Purchase Frequency Analyzer" << endl << endl;
	cout << "Menu:" << endl;

	// Display the menu options.
	for (const auto& [key, command] : this->commands) {
		cout << key << ". " << command.label << endl;
	}

	cout << endl;
}

// A template function to get user input of any type with a prompt.
template<typename T>
T App::GetInput(const string& prompt) {
	T value;
	cout << prompt;
	cin >> value;
	cout << endl;

	// Ignore excess input to prevent issues with subsequent input.
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Handle input failure (e.g., if the user enters a non-integer when an integer is expected).
	if (cin.fail()) {
		cin.clear(); // Clear the error state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input.
		cout << "Invalid input. Please try again." << endl;
		return this->GetInput<T>(prompt); // Recursively prompt again.
	}

	return value;
}

// Inits commands. I chose this method because it is more extensible later on 
// if we want to add more commands.
void App::InitCommands() {
	this->commands.insert({ 1, { "Search", [](App& app) { app.Search(); }} });
	this->commands.insert({ 2, { "Print Frequencies", [](App& app) { app.PrintFrequencies(); }} });
	this->commands.insert({ 3, { "Print Histogram", [](App& app) { app.PrintHistogram(); }} });
	this->commands.insert({ 4, { "Exit", [](App& app) { app.ExitProgram(); }} });
}

// Searches the data store for a specific term and prints its frequency.
void App::Search() {
	string term = this->GetInput<string>("Enter a search term: ");

	pair<string, int> result;
	try {
		result = this->dataStore.Find(term);
		cout << term << ": " << result.second << endl;
	}
	catch (const std::out_of_range&) {
		cout << "The term '" << term << "' was not found in the data store." << endl;
	}
}

// Prints the frequency of all terms in the data store.
void App::PrintFrequencies() {
	map<string, int> frequencies = this->dataStore.FindAll();

	for (const auto& [key, value] : frequencies) {
		cout << setw(15) << left << key << ": " << value << endl;
	}
}

// Prints a histogram of the frequencies of all terms in the data store.
void App::PrintHistogram() {
	map<string, int> frequencies = this->dataStore.FindAll();

	for (const auto& [key, value] : frequencies) {
		cout << setw(15) << left << key << ": " << string(value, '*') << endl;
	}
}

// Exit.
void App::ExitProgram() {
	this->isRunning = false;
}