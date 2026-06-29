#ifndef DATASTORE_H
#define DATASTORE_H

#include <map>
#include <string>
#include <fstream>

using namespace std;

class DataStore {
public:
	DataStore();
	~DataStore();

	pair<string, int> Find(const string& key) const;
	map<string, int> FindAll() const;
private:
	const string INPUT_FILE = "inputs.txt";
	const string DATA_STORE_FILE = "frequency.dat";

	map<string, int> data;
	void LoadData();
	void LoadDefaultData();
	void Save();
};

#endif // DATASTORE_H