#include <iostream>
#include <fstream>
#include <string>
#include "DateTime.h"


struct PhoneNumber {
	char _phoneNumber[16];
};
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

struct hash<PhoneNumber>
{
    size_t operator()(const PhoneNumber& x) const {
        return std::hash<string>()(string(x._phoneNumber));
    }
};

struct DataSet {
public:
	std::map<PhoneNumber, CallInDataSet> _data;
    void add(Call current) {	
		_data[current._phoneNumber]._count++;
		_data[current._phoneNumber]._sumPeriod += current._periodInSeconds;
		_data[current._phoneNumber]._sumPrice += (current._pricePerMinute / 60 * current._periodInSeconds);
    }
};

