#include <iostream>
#include <fstream>
#include <string>
class FM {
public:
	explicit FM(char *file_name_t, char mode_t = 'r', char type_t = 't');
	~FM();
	void open_file(char *file_name_t, char mode_t = 'r', char type_t = 't');
	
	template<class T>
    void read_struct_binary(T CurrentStructure);
    void write_struct_binary(T CurrentStructure);
    void get_c(T &tmp);
    void get_c_text(T &tmp);
    void write_c(int tmp);
    void write_c(double tmp);
    void write_c(float tmp);

    fstream *get_pointer() {return &stream; }
    
    void close_file(bool for_renaming = false);
    void rename_file(char *new_name);
    void delete_file();

    template<class T>
    void text2bin(string new_file_name = "", bool delete_file = false);
    void bin2txt(string new_file_name = "", bool delete_file = false)


private:
	fstream stream;
    char mode{};
    char type_m{};
    char *file_name{};
    string bin_extention = ".bin";
    string txt_extention = ".txt";
}