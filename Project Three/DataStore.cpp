#include "DataStore.h"

#include <fstream>
#include <iostream>

// Constructor
DataStore::DataStore() {
	// Attempt to load existing data first.
	this->LoadData();

	// If data is still empty, pull in data from the defaults.
	if (this->data.empty()) {
		this->LoadDefaultData();
	}

	// Save the data to the file.
	this->Save();
}

// Closes the data store file when the object is destroyed.
DataStore::~DataStore() {
	this->Save();
}

// Perform a case-insensitive search for the given key and return the associated value.
pair<string, int> DataStore::Find(const string& key) const {
	// Case insensitive
	string searchKey = key;
	if (!searchKey.empty()) {
		searchKey[0] = toupper(searchKey[0]);
	}

	// Traverse the map to find the key.
	auto it = this->data.find(searchKey);
	if (it != this->data.end()) {
		return *it; // Return the key-value pair if found.
	}
	else {
		throw std::out_of_range("Key not found in data store."); // Throw an exception if the key is not found.
	}
}

// Returns all data from the store as a map.
map<string, int> DataStore::FindAll() const {
	return this->data;
}

// Loads data from the data store file into the map.
void DataStore::LoadData() {
	ifstream inputFile(DATA_STORE_FILE);
	if (inputFile.is_open()) {
		string key;
		int value;

		// Format: [key] [value]
		while (inputFile >> key >> value) {
			this->data[key] = value;
		}
		inputFile.close();
	}
}

// Populates the map with default data
void DataStore::LoadDefaultData() {
	// Clear the map before loading default data
	this->data.clear();

	ifstream inputFile(INPUT_FILE);

	if (inputFile.is_open()) {
		string key;
		int value;

		// Each line contains a key name. Map keys to number of occurences.
		while (inputFile >> key) {
			if (this->data.find(key) != this->data.end()) {
				this->data[key]++;
			}
			else {
				this->data[key] = 1;
			}
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

// Saves the map data to the data store file.
void DataStore::Save() {
	ofstream outputFile(DATA_STORE_FILE);
	if (outputFile.is_open()) {
		for (const auto& pair : this->data) {
			outputFile << pair.first << " " << pair.second << endl;
		}
		outputFile.close();
	}
	else {
		cout << "Unable to write to file" << endl;
	}
}