#include <map>
#include <string>
#include <iostream>

using namespace std;

class Record
{
public:
	Record(void);
	virtual ~Record(void);

	void Record::SetValue(string paramName, string value);
	string Record::GetValue(string paramName);

protected:
	map<string, string> values;
};
