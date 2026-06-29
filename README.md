# PurchaseFreqAnalyzer
Uses an input file to store and analyze purchase frequency of items

## Summary
This project takes in files from input.txt and creates a representation of that data in-memory for analyzing item purchase frequency. It stores its loaded data into a .dat file for later use.

## What was done well
I decoupled the DataStore from the App so that the App only needs to be concerned with how to find data within. The DataStore handles loading and saving the data automatically.

## Where could I enhance the code? How would it make it more efficient, secure, etc?
I could add in the ability to add new data, or make it so if it detects there is different data in the input file, then it would overwrite its existing data store so that we could consistently feed in new data without having to delete the old saved data.

## Which pieces did I find most challenging to write?
I found it most challenging to write my App controller's modular command system. It is a bit complex mapping actions to function calls and making it all update the menu by just adding a new command, mainly due to having to decypher what types are needed for this functionality. To overcome this, I seeked out help from Google to find a reference to the C++ documentation which helped me get it working.

## What skills from this project will be transferable to other projects or course work?
Thinking about things as isolated units, and abstracting inner functionality away from classes and components that use them is probably most beneficial. 

## How did I make this program maintainable, readable, and adaptable?
I made the commands modular, which allows the ability to expand the program later when we want to add the ability to add new items to the data store. It is maintainable by this principle, too. The comments I left throughout gives a rough overview of what each piece does, and is easy to follow along.
