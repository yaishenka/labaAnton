#include "FM.h"

explicit FM::FM(char *file_name_t, char mode_t = 'r', char type_t = 't') {
    open_file(file_name_t, mode_t, type_t);
}

void FM::open_file(char *file_name_t, char mode_t = 'r', char type_t = 't') {
    if (mode_t == 'w') {
        if (type_t == 't') {
            stream.open(file_name_t, fstream::out);
        } else if (type_t == 'b') {
            stream.open(file_name_t, fstream::out | fstream::binary);
        } else {
            throw ("Wrong type_m. Use 't' or 'b' ");
        }
    } else if (mode_t == 'r') {
        if (type_t == 't') {
            stream.open(file_name_t, fstream::in);
        } else if (type_t == 'b') {
            stream.open(file_name_t, fstream::in | fstream::binary);
        } else {
            throw ("Wrong type_m. Use 't' or 'b' ");
        }
    } else {
        throw ("Wrong mode. Use 'r' or 'w' ");
    }
    mode = mode_t;
    type_m = type_t;
    file_name = file_name_t;
}

~FM::FM() {
    stream.close();
}

template<class T>
void FM::read_struct_binary(T CurrentStructure) {
    if (type_m == 'b' && mode == 'r') {
        stream.read((char *) &CurrentStructure, sizeof(CurrentStructure));
    } else {
        throw ("Wrong type_m or mode. Use mode 'r' and type_m 'b' ");
    }
}

template<class T>
void FM::write_struct_binary(T CurrentStructure) {
    if (type_m == 'b' && mode == 'w') {
        stream.write((char *) &CurrentStructure, sizeof(CurrentStructure));
    } else {
        throw ("Wrong type_m or mode. Use mode 'w' and type_m 'b' ");
    }
}

template<typename T>
void FM::get_c(T &tmp) {
    if (mode == 'r') {
        if (type_m == 't') {
            stream >> tmp;
        } else {
            stream.read((char *) &tmp, sizeof(T));
        }
    } else {
        throw ("Wrong mode. Use mode 'r'");
    }

}

template<typename T>
void FM::get_c_text(T &tmp) {
    if (mode == 'r') {
        if (type_m == 't') {
            stream >> tmp;
        }
    } else {
        throw ("Wrong mode. Use mode 'r'");
    }
}

void FM::write_c(int tmp) {
    if (mode == 'w') {
        if (type_m == 't') {

            stream << tmp;
        } else {
            stream.write((char *) &tmp, sizeof(T));
        }
    } else {
        throw ("Wrong mode. Use mode 'w'");
    }
}
void FM::write_c(double tmp) {
    if (mode == 'w') {
        if (type_m == 't') {

            stream << tmp;
        } else {
            stream.write((char *) &tmp, sizeof(T));
        }
    } else {
        throw ("Wrong mode. Use mode 'w'");
    }
}
void FM::write_c(float tmp) {
    if (mode == 'w') {
        if (type_m == 't') {

            stream << tmp;
        } else {
            stream.write((char *) &tmp, sizeof(T));
        }
    } else {
        throw ("Wrong mode. Use mode 'w'");
    }
}



void FM::close_file(bool for_renaming = false) {
    stream.close();
    if (!for_renaming) {
        mode = NULL;
        type_m = NULL;
    }
}

void FM::rename_file(char *new_name) {
    int result;
    this->close_file();
    result = rename(file_name, new_name);

    if (result != 0) {
        throw ("Error renaming file");
    }
    file_name = new_name;
    this->open_file(file_name, mode, type_m);
}

void FM::delete_file() {
    this->close_file();
    if (remove(file_name) != 0)
        throw ("Error deleting file");
}

template<typename T>
void FM::text2bin(string new_file_name = "", bool delete_file = false) {
    if (new_file_name == "") {
        new_file_name = (string) file_name + bin_extention;
    }
    fstream bf(new_file_name, fstream::out | fstream::binary);
    while (stream) {
        T tmp;
        stream >> tmp;
        bf.write((char *) &tmp, sizeof(T));
    }
    bf.close();
    if (delete_file) {
        stream.close();
        this->delete_file();
    }
}

template<typename T>
void FM::bin2txt(string new_file_name = "", bool delete_file = false) {
    if (new_file_name == "") {
        new_file_name = (string) file_name + txt_extention;
    }
    fstream bf(new_file_name, fstream::in | fstream::binary);
    while (stream) {
        T tmp;
        stream.read((char *) &tmp, sizeof(T));
        bf << tmp;
    }
    bf.close();
    if (delete_file) {
        stream.close();
        this->delete_file();
    }
}
};