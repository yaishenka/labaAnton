#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
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

    std::vector<std::pair<string, CallInDataSet>> prepairData () {
        std::vector<std::pair<string, CallInDataSet>> data;
        for (auto it = _data.begin(); it != _data.end(); ++it) {
             if (it->second._count <= 3) {
                 data.push_back(std::make_pair(it->first, it->second));
             }
        }
        return data;
    }

    void output(){
        FM output_file("output.txt", 'w', 't');
        std::vector<std::pair<string, CallInDataSet>> out = prepairData();
        output_file.write_c(out.size());
        output_file.write_c('\n');
        for (auto p : out){
            output_file.write_c(p.first);
            output_file.write_c(' ');
            output_file.write_c(p.second._sumPrice);
            output_file.write_c(' ');
            output_file.write_c(p.second._sumPeriod);
            output_file.write_c('\n');
        }
    }
};
