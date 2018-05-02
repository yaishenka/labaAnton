#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include "DateTime.h"
#include "FM.h"

using namespace std;

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
    float _sumPrice = 0;
    int _sumPeriod = 0;
    int _count = 0;
};


struct DataSet {
private:
    int n;
    DateTime T1{}, T2{};
public:
    std::map<string, CallInDataSet> _data;

    void add(Call current) {
        if (T1 <= current._startTime && current._startTime <= T2) {
            _data[string(current._phoneNumber)]._count++;
            _data[string(current._phoneNumber)]._sumPeriod += current._periodInSeconds;
            _data[string(current._phoneNumber)]._sumPrice += ceil(current._pricePerMinute / 60 * current._periodInSeconds);
        }
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
