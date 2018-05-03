//
// Created by Антон Донской on 03.05.2018.
//

#include <iostream>
#include "DataSet.h"

using namespace std;

int main(){
    make_bin_file("input.bin");
    DataSet lab;
    lab.input("input.bin");
    lab.output("output.txt");
}