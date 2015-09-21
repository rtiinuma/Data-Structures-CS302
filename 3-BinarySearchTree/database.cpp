//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum = 0;                          // Record number

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	acctFile >> acctRec.acctID;

	while( acctFile.good() )
	{
		acctFile >> acctRec.firstName >> acctRec.lastName >> acctRec.balance;
		if( acctFile.good() )
		{
			entry.acctID = acctRec.acctID;
			entry.recNum = recNum;
			index.insert( entry );
		}
		recNum++;

		acctFile >> acctRec.acctID;
	}

    // Output the account IDs in ascending order.
	cout << endl << "Account IDs :" << endl;
	index.writeKeys();

    // Clear the status flags for the database file.

    acctFile.clear();

    // Read an account ID from the keyboard and output the
    // corresponding record.
	cout << endl << "Enter account ID : ";
	while( cin >> searchID )
	{
		acctFile.clear();
		if( index.retrieve( searchID, entry ) )
		{
			acctFile.seekg( bytesPerRecord * entry.recNum );
			acctFile >> acctRec.acctID >> acctRec.firstName; 
			acctFile >> acctRec.lastName >> acctRec.balance;
			cout << ' ' << entry.recNum << " : ";
			cout << acctRec.acctID << ' ';
			cout << acctRec.firstName << ' ' << acctRec.lastName << ' ';
			cout << acctRec.balance << endl;
		}
		else
		{
			cout << "No record with that account ID" << endl;
		}
		cout << "Enter account ID (EOF to quit): ";
	}
	return 0;
}
