#include "Record.h"

Record::Record(void)
{
	// �R���X�g���N�^
	//cout << "Record()���Ă΂�܂����B" << endl;
}


Record::~Record(void)
{
	// �f�X�g���N�^
	//cout << "~Record()���Ă΂�܂����B" << endl;
}

void Record::SetValue(string paramName, string value){
	// Insert to map.
	this->values.insert(pair<string, string>(paramName, value));
}

string Record::GetValue(string paramName){
	map<string, string>::iterator it;
	string result;

	it = this->values.find(paramName);
	if (it != values.end()) {
		// Set value.
		result = (string)it->second;
	} else {
		// Set empty string.
		result = "";
	}

	return result;
}
