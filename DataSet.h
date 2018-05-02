#include <iostream>
#include <fstream>
#include <string>
#include "DateTime.h"
struct PhoneNumber {
	char _phoneNumber[16];
}
struct Call {
public:
    char _FIO[51];
    PhoneNumber _phoneNumber;
    DateTime _startTime;
    int _periodInSeconds;
    float _pricePerMinute;
};

struct CallInDataSet {
public:
    float _sumPrice = 0;
    int _sumPeriod = 0;
    int _count = 0;
};

struct DataSet {
public:
	std::map<PhoneNumber, std::pair<CallInDataSet, int>> _data;
    void add(Call current) {
    	if (_data.find(current._phoneNumber) == _data.end()) {
    		_data[current._phoneNumber].second = 0;
    	}	
		_data[current._phoneNumber].second++;
		_data[current._phoneNumber].first._sumPeriod += current._periodInSeconds;
		_data[current._phoneNumber].first._sumPrice += (current._pricePerMinute / 60 * current._periodInSeconds);
    }
};

