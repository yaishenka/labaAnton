#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "DateTime.h"
#include "FM.h"

using namespace std;

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
template <>
struct hash<PhoneNumber> {
    size_t operator()(const PhoneNumber &x) const {
        return std::hash<string>()(string(x._phoneNumber));
    }
};

struct DataSet {
private:
    int n;
    DateTime T1{}, T2{};
public:
    std::map<PhoneNumber, CallInDataSet> _data;

    void add(Call current) {
        _data[current._phoneNumber]._count++;
        _data[current._phoneNumber]._sumPeriod += current._periodInSeconds;
        _data[current._phoneNumber]._sumPrice += (current._pricePerMinute / 60 * current._periodInSeconds);
    }

    void input(){
        FM input_file("input.bin", 'r', 'b');
        input_file.get_c_bin<int>(n);
        input_file.get_c_bin<DateTime>(T1);
        input_file.get_c_bin<DateTime>(T2);
        for(int i(0); i<this->n; ++i){
            Call tmp{};
            input_file.read_struct_binary(tmp);
            add(tmp);
        }
        input_file.close_file();
    }

    void output(){
        FM output_file("output.txt", 'w', 't');

    }
};
