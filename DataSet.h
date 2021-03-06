#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "DateTime.h"



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
    DateTime T1, T2;
public:
    std::map<string, CallInDataSet> _data;

    void add(Call current) {

        if ((T1 <= current._startTime) && (current._startTime <= T2)) {

            _data[string(current._phoneNumber)]._count++;
            _data[string(current._phoneNumber)]._sumPeriod += current._periodInSeconds;
            _data[string(current._phoneNumber)]._sumPrice += ceil(
                    current._pricePerMinute / 60 * current._periodInSeconds);
        }
    }

    void input(char *file_name) {
        ifstream instr(file_name, ios::in | ios::binary);
        instr.read((char *) &n, sizeof(int));
        instr.read((char *) &T1, sizeof(DateTime));
        instr.read((char *) &T2, sizeof(DateTime));

        for (int i(0); i < this->n; ++i) {
            Call tmp{};

            instr.read((char *) &tmp, sizeof(Call));
            add(tmp);
        }
        instr.close();
    }

    vector<std::pair<string, CallInDataSet>> prepairData() {
        vector<std::pair<string, CallInDataSet>> data;
        for (auto &it : _data) {
            if (it.second._count <= 3) {
                data.emplace_back(it.first, it.second);
            }
        }
        return data;
    }

    void output(char *file_name) {
        ofstream instr(file_name, ios::out);
        vector<std::pair<string, CallInDataSet>> out = prepairData();
        instr << out.size() << endl;
        for (auto p : out) {
            instr << p.first << " " << p.second._sumPrice << " " << p.second._sumPeriod << endl;
        }
    }
};

void make_bin_file(char * file_name) {
    ofstream instr(file_name, ios::out | ios::binary);
    int n = 15;
    DateTime T1{Date{1, 4, 2018}, Time{12, 30, 0}};
    DateTime T2{Date{29, 4, 2018}, Time{19, 25, 01}};
    instr.write((char *) &n, sizeof(int));
    instr.write((char *) &T1, sizeof(DateTime));
    instr.write((char *) &T2, sizeof(DateTime));
    Call a[15] = {
            {
                    "Sidorov",
                    "8 936 325-03-15",
                    DateTime{
                            Date{
                                    06,
                                    02,
                                    2017
                            },
                            Time{
                                    11,
                                    59,
                                    01
                            }
                    },
                    60,
                    2.5
            },
            {
                    "Petrov",
                    "8 923 456-35-12",
                    DateTime{
                            Date{
                                    12,
                                    02,
                                    2018
                            },
                            Time{
                                    11,
                                    45,
                                    23
                            }
                    },
                    8000,
                    0.6
            },
            {
                    "Cherniy",
                    "8 911 563-48-75",
                    DateTime{
                            Date{
                                    14,
                                    02,
                                    2018
                            },
                            Time{
                                    03,
                                    34,
                                    00
                            }
                    },
                    1602,
                    1.3
            },
            {
                    "Svistunov",
                    "8 934 364-65-15",
                    DateTime{
                            Date{
                                    27,
                                    02,
                                    2018
                            },
                            Time{
                                    16,
                                    26,
                                    00
                            }
                    },
                    1504,
                    0.2
            },
            {
                    "Kovalev",
                    "8 967 153-64-34",
                    DateTime{
                            Date{
                                    02,
                                    03,
                                    2018
                            },
                            Time{
                                    17,
                                    14,
                                    00
                            }
                    },
                    230,
                    0.7
            },
            {
                    "Krasnov",
                    "8 937 817-55-47",
                    DateTime{
                            Date{
                                    04,
                                    03,
                                    2018
                            },
                            Time{
                                    15,
                                    12,
                                    00
                            }
                    },
                    530,
                    1.2
            },
            {
                    "Kovalev",
                    "8 967 153-64-34",
                    DateTime{
                            Date{
                                    13,
                                    03,
                                    2018
                            },
                            Time{
                                    12,
                                    00,
                                    00
                            }
                    },
                    670,
                    0.7
            },
            {
                    "Svistunov",
                    "8 934 364-65-15",
                    DateTime{
                            Date{
                                    01,
                                    04,
                                    2018
                            },
                            Time{
                                    22,
                                    31,
                                    00
                            }
                    },
                    500,
                    0.2
            },
            {
                    "Sidorov",
                    "8 936 325-03-15",
                    DateTime{
                            Date{
                                    02,
                                    04,
                                    2018
                            },
                            Time{
                                    12,
                                    25,
                                    00
                            }
                    },
                    600,
                    2.5
            },
            {
                    "Ivanov",
                    "8 995 753-84-51",
                    DateTime{
                            Date{
                                    16,
                                    04,
                                    2018
                            },
                            Time{
                                    11,
                                    25,
                                    00
                            }
                    },
                    36000,
                    1.2
            },
            {
                    "Ivanov",
                    "8 995 753-84-51",
                    DateTime{
                            Date{
                                    16,
                                    04,
                                    2018
                            },
                            Time{
                                    22,
                                    05,
                                    00
                            }
                    },
                    2466,
                    1.2
            },
            {
                    "Ivanov",
                    "8 995 753-84-51",
                    DateTime{
                            Date{
                                    17,
                                    04,
                                    2018
                            },
                            Time{
                                    18,
                                    11,
                                    00
                            }
                    },
                    1346,
                    1.2
            },
            {
                    "Kuznecov",
                    "8 937 876-55-55",
                    DateTime{
                            Date{
                                    18,
                                    04,
                                    2018
                            },
                            Time{
                                    11,
                                    23,
                                    00
                            }
                    },
                    235,
                    0.1
            },
            {
                    "Ivanov",
                    "8 995 753-84-51",
                    DateTime{
                            Date{
                                    18,
                                    04,
                                    2018
                            },
                            Time{
                                    17,
                                    56,
                                    00
                            }
                    },
                    1672,
                    1.2
            },
            {
                    "Petrov",
                    "8 923 456-35-12",
                    DateTime{
                            Date{
                                    15,
                                    05,
                                    2018
                            },
                            Time{
                                    19,
                                    34,
                                    00
                            }
                    },
                    1345,
                    0.6
            },
    };
    for (auto &i : a) {
        instr.write((char *) &i, sizeof(Call));
    }
    instr.close();
}

