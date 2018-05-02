#include <iostream>
#include <fstream>
#include <string>
#include "DateTime.h"

struct Call {
public:
    char _FIO[51];
    char _phoneNumber[16];
    DateTime _startTime;
    int _periodInSeconds;
    float _pricePerMinute;
};

struct CallInDataSet {
public:
	char _phone[16];
    float _sumPrice = 0;
    int _sumPeriod = 0;
    int _count = 0;
};

struct DataSet {
public:
    CallInDataSet *array = new CallInDataSet[10000];
    int size = 0;

    void add(My current) {
        int ex = exsist(current.phone_number);
        if (ex != -1) {
            array[ex].count += 1;
            array[ex]._sumPeriod += current._periodInSeconds;
            array[ex]._sumPrice += (current._pricePerMinute / 60 * current._periodInSeconds);

        } else {
            array[size].count = 1;
            array[size]._sumPeriod = current._periodInSeconds;
            array[size]._sumPrice = (current._pricePerMinute / 60 * current._periodInSeconds);
        }
    }

    int exsist(char phone[16]) {
        for (int i(0); i < size; ++i) {
            if (array[i].phone == phone) {
                return i;
            }
        }
        return -1;
    };
};

