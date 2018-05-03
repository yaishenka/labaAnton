//
// Created by Антон Донской on 03.05.2018.
//

#include "DataSet.h"

int main(){
    make_bin_file(const_cast<char *>("input.bin"));
    DataSet lab;
    lab.input(const_cast<char *>("input.bin"));
    lab.output(const_cast<char *>("output.txt"));
}