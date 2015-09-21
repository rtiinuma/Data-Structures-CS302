#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "HashTable.cpp"

class TestData {
  public:
    TestData();
    void setKey(const string& newKey);
	void setPassword( const string& newPassword );
    string getKey() const;
	string getPassword() const;
    static unsigned int hash(const string& str);

  private:
    string key;
    string password;
    static int count;
};

int TestData::count = 0;

TestData::TestData()
{
	key = "0";
	password = "0";
}

void TestData::setKey(const string& newKey) 
{
    key = newKey;
}

void TestData::setPassword( const string& newPassword )
{
	password = newPassword;
}

string TestData::getPassword() const
{
	return password;
}
string TestData::getKey() const 
{
    return key;
}


unsigned int TestData::hash(const string& str) 
{
    unsigned int val = 0;

    for (int i = 0; i < str.length(); ++i) {
	val += str[i];
    }

    return val;
}

int main() 
{
	ifstream fin;
	HashTable< TestData, string> accountTable( 8 );
	string firstName, passw;
	TestData accountInfo;

	fin.clear();
	fin.open( "password.dat" );
	while( fin.good() )
	{
		fin >> firstName;
		fin >> passw;
		if( fin.good() )
		{
			accountInfo.setKey( firstName );
			accountInfo.setPassword( passw );
			accountTable.insert( accountInfo );
		}
	}

	accountTable.showStructure();

	cout << "Login: ";
	while( cin >> firstName )
	{
		cout << "Password: ";
		cin >> passw;
		if( accountTable.retrieve( firstName, accountInfo ) )
		{
			if( accountInfo.getPassword() == passw )
			{
				cout << "Authentication successful" << endl;
			}
			else
			{
				cout << "Authentication failure" << endl;
			}
		}
		else
		{
			cout << "Authentication failure" << endl;
		}
		cout << "Login: ";


	}
	

    return 0;
}

