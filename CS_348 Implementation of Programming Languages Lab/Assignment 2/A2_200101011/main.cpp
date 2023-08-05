/**
 * @file 200101011.cpp
 * @author Akshat Mittal
 * @brief This code aims to implement a two pass assembler for a SIC (Simplified Instructional Computer)
 * that genrates object code file and intermediate file.
 * @version 1.0
 * @date 2023-02-13
 * @note This code is written with the reference of "System Softwares: An Introduction to System Programming" text book.
 */

/**
 * @brief Assumptions made in reference to the text book
 * @details The address space of computer is 24 bits
 * @details Any label can be of maximum 24 characters in size.
 * @details Any character string can be of maximum 24 characters in size.
 */

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
using namespace std;

/**
 * @brief Specify details of the current line read and is used in Instruction class
 */
enum FlagType {
    COMMENT,
    EMPTY_LABEL,
    IN_SYMTAB,
    IN_OPTAB,
    WORD,
    BYTE,
    RESW,
    RESB,
    START,
    END
};

/**
 * @brief Stream to read input file
 */
ifstream input_file;

/**
 * @brief Stream to write output files
 */
ofstream output_file;

/**
 * @brief Hash table to store OPTAB and SYMTAB, i.e. operation table and symbol table.
 * @param write_access Insertion allowed iff it is true
 * @param table stores (key,value) pairs,
 * value is machine code of corresponding opcode in OPTAB and address of correponding label in SYMTAB
 */
class HashTable {
    bool write_access;
    unordered_map <string, int> table;

public:
    HashTable() {
        write_access = true;
    }

    /**
     * @brief Get the value stored corresponding to _key in hash table
     * @param _key Key corresponding to which the value is expected
     * @return Value stored corresponding to _key in hash table
     */
    int GetValue(string _key) {
        auto it = table.find(_key);
        if(it == table.end()) return -1;
        return it->second;
    }

    /**
     * @brief Insert a (key,value) pair in the hash table if write_access is true
     * @param _key Key to be inserted
     * @param _val Value to be inserted
     */
    void Insert(string _key, int _val) {
        if(write_access) {
            table[_key] = _val;
        }
        else {
            cout << "WARNING: OPTAB cannot be modified once initalized! Ignoring the following insertion: (" << _key << ", " << _val << ")" << endl;
        }
    }

    /**
     * @brief Check whether a key exists in the hash table
     * @param _key The key to be searched for
     * @return true if key is present
     */
    bool Search(string _key) {
        return table.find(_key) != table.end();
    }

    /**
     * @brief Set write_access to false to forbid any further Insert attempts to the Hash Table
     */
    void Close() {
        write_access = false;
    }

    /**
     * @brief Print the contents of the Hash Table
     */
    void Print() {
        for (auto u: table) {
            output_file << setfill(' ') << setw(6) << left << u.first << " ";
            output_file << setfill(' ') << setw(6) << right << hex << uppercase << u.second << "\n";
        }
    }
} SymTable, OpTable;

/**
 * @brief Facilitate reading, processing, storing and writing of an input line (in the form of instruction)
 * @param loc address location of the instruction
 * @param label label (if any) of the instruction, empty string if no label is present
 * @param opcode operation code of the instruction
 * @param addr address of operand of the instruction
 * @param line stores the entire instruction
 * @param flags indicates various properties of an instruction
 */
class Instruction {
    int loc;
    string label, opcode, addr, line;
    stringstream ss; // to help in processing strings
    bool flags[10];

public:
    Instruction() {
        label = opcode = line = "";
        addr = "0";
        for(int i = 0; i < 10; i ++) {
            flags[i] = false;
        }
    }

    /**
     * @brief Get the value of a flag of type FlagType
     * @param _flag name of flag
     * @return true if flag is set
     */
    bool GetFlags(FlagType _flag) {
        return flags[_flag];
    }

    /**
     * @brief Get the location of instruction
     * @return int loc object
     */
    int GetLoc() {
        return loc;
    }

    /**
     * @brief Get the label of instruction
     * @return string label object
     */
    string GetLabel() {
        return label;
    }
    
    /**
     * @brief Get the opcode of instruction
     * @return string opcode object
     */
    string GetOpcode() {
        return opcode;
    }

    /**
     * @brief Get the address of operand
     * @return string addr object
     */
    string GetAddr() {
        return addr;
    }

    /**
     * @brief Set the flags object (to be called after reading the instruction)
     */
    void SetFlags() {
        flags[0] = (label == "."); // True if instruction is a comment
        flags[1] = (label == ""); // True if label is EMPTY_LABEL
        flags[2] = SymTable.Search(label); // True if label is in SYMTAB
        flags[3] = OpTable.Search(opcode); // True if opcode is in OPTAB
        flags[4] = (opcode == "WORD");
        flags[5] = (opcode == "BYTE");
        flags[6] = (opcode == "RESW");
        flags[7] = (opcode == "RESB");
        flags[8] = (opcode == "START");
        flags[9] = (opcode == "END");
    }

    /**
     * @brief Read the next line from input_file stream and
     * store the instruction in appropriate member variables
     * (For Ex: label, opcode, addr etc.) after removing trailing whitespaces
     * @param is_intermediate true if input_file stream is from intermediate file
     */
    void Read(bool is_intermediate = false) {
        int cnt = 0;
        getline(input_file, line);
        ss.str("");
        ss.clear();
        ss << line;
        int end = line.find_last_not_of(" \t\r");
        line = line.substr(0, end+1);
        string temp;
        while(ss >> temp) {
            switch(cnt) {
                case 0: {
                    if(temp[0] == '.') {
                        cnt = -1;
                        break;
                    }
                    label = temp;
                } break;
                case 1: opcode = temp;
                break;
                case 2: addr = temp;
                break;
            }
            if(cnt == -1) break;
            cnt ++;
        }
        switch (cnt) {
            case -1: {
                label = ".";
                opcode = ".";
                addr = "0";
            } break;
            case 0: break;
            case 1: {
                if(is_intermediate) {
                    string err_str = "Invalied input: " + line;
                    throw err_str;
                }
                else {
                    opcode = label;
                    addr = "0";
                    label = "";
                }
            } break;
            case 2: {
                if(is_intermediate and label != "END") {
                    loc = stoi(label, 0, 16);
                    addr = "0";
                }
                else {
                    addr = opcode;
                    opcode = label;
                }
                label = "";
            } break;
            case 3: {
                if(is_intermediate) {
                    loc = stoi(label, 0, 16);
                    label = "";
                }
            } break;
            case 4: {
                loc = stoi(label, 0, 16);
                label = opcode;
                opcode = addr;
                addr = temp;
            } break;
            default: {
                string err_str = "Invalid assembly input format: " + line;
                throw err_str;
            }
        }
        SetFlags();
    }

    /**
     * @brief Write the output to intermediate file (intermediate.txt) in Pass 1
     * and output file (output.txt) in Pass 2
     * @param loc_cntr location of instruction
     * @param instr_str machine code of the current instruction
     */
    void Write(int loc_cntr, string instr_str = "") {
        if(loc_cntr == -1) loc_cntr = loc; // if location is not known
        if(!flags[COMMENT]) {
            output_file << setfill('0') << setw(6) << hex << uppercase << loc_cntr << '\t';
        }
        output_file<<line<<endl;
    }

    /**
     * @brief To check whether instruction uses indexed addressing
     * @return true if instruction uses indexed addressing mode
     */
    bool IsIndexed() {
        int n = addr.size();
        return (n >= 2) and (addr[n-1] == 'X') and (addr[n-2] == ',');
    }
};

/**
 * @brief Facilitate various tasks of an assmbler including conversion of an instruction to machine code, writing records to output object file, pass 1 and pass2 of a 2-pass assembler on SIC.
 * @param loc_cntr counter to determine location of current instruction
 * @param text_record_len counter to store length of text record to be written next into output object file
 * @param start_addr starting address of programme
 * @param text_record text record to be written next into output object file (output.txt)
 * @param cur_instr current instruction object
 * @param state stores the states of the AssemblerSIC, NONE - Pass 1 is not finished yet, PASS_1 - Pass 1 is done, PASS_2 - Pass 2 is done
 */
class AssemblerSIC {
    int loc_cntr, text_record_len;
    string start_addr, prog_len, text_record;
    stringstream ss;
    Instruction cur_instr;
    enum ASSEMBLY_STATE {NONE, PASS_1, PASS_2} state;

    public:
    AssemblerSIC() {
        start_addr = "000000";
        text_record = "";
        loc_cntr = 0;
        prog_len = "0";
        state = NONE;
        text_record_len = 0;
    }

    /**
     * @brief Helper function to make address string pretty
     * @param _addr address string of current instruction
     */
    void ConvertAddr(string &_addr) {
        ss.str("");
        ss.clear();
        if(_addr.size() < 6) {
            ss << setfill('0') << setw(6) << _addr;
            ss >> _addr;
        }
    }

    /**
     * @brief Store pretty formatted address given by _val into _addr
     * @param _addr string to store address into
     * @param _val integer value of the address
     */
    void ConvertAddr(string &_addr, int _val) {
        ss.str("");
        ss.clear();
        ss << hex << uppercase << _val;
        ss >> _addr;
        ConvertAddr(_addr);
    }

    /**
     * @brief Assemble the current instruction and generate the machine code
     * @param _opcode operation code
     * @param _x 1 if indexed addressing mode
     * @param _addr address of operand
     * @return string assmbled instruction
     */
    string AssembleInstr(string _opcode, int _x, string _addr) {
        if(state != PASS_1) {
            throw string("Instruction cannot be assembled before Pass 1!");
        }
        if(cur_instr.GetFlags(START)
            or cur_instr.GetFlags(END)
            or cur_instr.GetFlags(RESW)
            or cur_instr.GetFlags(RESB)) return "";

        string instr_str = "";
        int n;
        int opcode_val = OpTable.GetValue(_opcode);
        int addr_val;
        
        repeat:
        n = _addr.size();
        if(SymTable.Search(_addr)) {
            addr_val = SymTable.GetValue(_addr);
        }
        else if(n >= 2 and _addr[n-1] == 'X' and _addr[n-2] == ',') {
            _addr = _addr.substr(0, n-2);
            goto repeat;
        }
        else if(_addr == "0") {
            addr_val = 0;
        }
        else if(cur_instr.GetFlags(BYTE)) {
            if(_addr[0] == 'C') {
                ss.str("");
                ss.clear();
                for(int i = 2; i < n-1; i ++) {
                    ss << hex << uppercase << int(_addr[i]);
                }
                ss >> instr_str;
                return instr_str;
            }
            else if(_addr[0] == 'X') {
                return _addr.substr(2, n-3);
            }
            else {
                throw string("Invalid Operand type: ") + _addr;
            }
        }
        else if(cur_instr.GetFlags(WORD)) {
            addr_val = stoi(_addr);
        }
        else {
            string err_str = "Unknown address format: " + _addr;
            throw err_str;
        }
        if(opcode_val == -1) {
            // opcode validity has been checked in pass 1
            // and hence it is an assmbler directive without any opcode
            // (i.e. either RESW or RESB)
            opcode_val = 0;
        }
        if(addr_val == -1) {
            string err_str = "Invalid Address Symbol: " + _addr;
            throw err_str;
        }
        ConvertAddr(instr_str, (opcode_val<<16) + (_x<<15) + addr_val);
        return instr_str;
    }

    /**
     * @brief Pass 1 of assembler which validates the input,
     * calculates addresses, fills SymTable, calculates length of program
     * and writes into intermediate file (intermediate.txt)
     * @remark the loc_cntr increment can be abstracted to a helper function
     */
    void Pass1() {
        cur_instr.Read();
        if(cur_instr.GetFlags(START)) {
            start_addr = cur_instr.GetAddr();
            ConvertAddr(start_addr);
            loc_cntr = stoi(start_addr, 0, 16);
            cur_instr.Write(loc_cntr);
            cur_instr.Read();
        }
        while(!cur_instr.GetFlags(END)) {
            if(cur_instr.GetFlags(COMMENT)) {
                cur_instr.Write(loc_cntr);
            }
            else {
                if(!cur_instr.GetFlags(EMPTY_LABEL)) {
                    if(cur_instr.GetFlags(IN_SYMTAB)) {
                        string err_str = "Repeated use of label: " + cur_instr.GetLabel();
                        throw err_str;
                    }
                    else {
                        SymTable.Insert(cur_instr.GetLabel(), loc_cntr);
                    }
                }
                cur_instr.Write(loc_cntr);
                if(cur_instr.GetFlags(IN_OPTAB)) {
                    loc_cntr += 3;
                }
                else if(cur_instr.GetFlags(WORD)) {
                    loc_cntr += 3;
                }
                else if(cur_instr.GetFlags(RESW)) {
                    loc_cntr += 3*stoi(cur_instr.GetAddr());
                }
                else if(cur_instr.GetFlags(RESB)) {
                    loc_cntr += stoi(cur_instr.GetAddr());
                }
                else if(cur_instr.GetFlags(BYTE)) {
                    string address = cur_instr.GetAddr();
                    string err_str = "Invalid operand value of BYTE instruction: " + address;
                    int n = address.size();
                    if(n < 3) {
                        throw err_str;
                    }
                    if(address[0] == 'X') {
                        if(n > 5) {
                            throw err_str;
                        }
                        else {
                            loc_cntr += (n - 3) / 2;
                        }
                    }
                    else if(address[0] == 'C') {
                        loc_cntr += n - 3;
                    }
                    else {
                        throw string("Invalid Operand type: ") + address;
                    }
                }
                else {
                    string err_str = "Invalid Operation Code: " + cur_instr.GetOpcode();
                    throw err_str;
                }
            }
            cur_instr.Read();
        }
        cur_instr.Write(loc_cntr);
        ConvertAddr(prog_len, loc_cntr - stoi(start_addr, 0, 16));
        state = PASS_1;
    }

    /**
     * @brief Writes header record to output.txt
     * @param prog_name name of program (if specified in START statement)
     */
    void WriteHeaderRecord(string prog_name = "") { // you are sending null string
        int n = 6 - prog_name.size();
        if(n < 0) prog_name = prog_name.substr(0, 6);
        else {
            while(n--) prog_name.push_back(' ');
        }
        output_file << "H" + prog_name + start_addr + prog_len <<endl;
    }

    /**
     * @brief Writes text record to output.txt
     * @param _instr assembled instruction string
     * @param _start_addr starting address of the instruction if
     * a new text record is to be written in a new line
     */
    void WriteTextRecord(string _instr, int _start_addr = -1) {
        if(_start_addr != -1) { // new record is to be created
            if(text_record.size() != 0) { // text_record contains some instructions
                string siz;
                ConvertAddr(siz, text_record_len / 2);
                text_record.insert(7, siz.substr(4));
                output_file << text_record << endl;
            }
            if(_instr.size() > 0) { // if current instruction has a corresponding machine code
                string addr_str;
                ConvertAddr(addr_str, _start_addr);
                text_record = "T" + addr_str + _instr;
                text_record_len = _instr.size();
            }
            else { // if the current machine code is empty (Ex: RESW, RESB)
                text_record = "";
                text_record_len = 0;
            }
        }
        else {
            text_record += _instr;
            text_record_len += _instr.size();
        }
    }

    /**
     * @brief Write end record to output.txt
     */
    void WriteEndRecord() {
        if(text_record.size() > 0) {
            WriteTextRecord("", 0);
        }
        output_file << "E" << start_addr << endl;
    }

    /**
     * @brief Pass 2 of the assembler which reads from intermediate file (intermediate.txt),
     * generates the object code (output.txt)
     */
    void Pass2() {
        if(state != PASS_1) {
            throw string("Pass 2 cannot be processed before Pass 1!");
        }
        cur_instr.Read(true);
        if(cur_instr.GetFlags(START)) {
            WriteHeaderRecord(cur_instr.GetLabel());
            cur_instr.Read(true);
        }
        else {
            WriteHeaderRecord(cur_instr.GetLabel());
        }
        while(!cur_instr.GetFlags(END)) {
            if(!cur_instr.GetFlags(COMMENT)) {
                string assembled_instr =
                AssembleInstr(
                    cur_instr.GetOpcode(),
                    cur_instr.IsIndexed(),
                    cur_instr.GetAddr()
                );
                if(
                    text_record_len == 0
                    or text_record_len + assembled_instr.size() > 60
                    or assembled_instr.size() == 0
                ) {
                    WriteTextRecord(assembled_instr, cur_instr.GetLoc());
                }
                else {
                    WriteTextRecord(assembled_instr);
                }
            }
            cur_instr.Read(true);
        }
        WriteEndRecord();
        state = PASS_2;
    }

    /**
     * @brief Assemble the input file (input.txt) and produce
     * intermediate file (intermediate.txt) as a result of Pass 1,
     * output files (output.txt) as a result of Pass 2.
     */
    void Assemble() {
        // Pass 1
        input_file.open("input.txt");
        output_file.open("intermediate.txt");
        Pass1();
        input_file.close();
        output_file.close();
        cout << "Pass 1 has finished successfully!\n";

        // Print Symbol Table
        output_file.open("symtab.txt");
        SymTable.Print();
        output_file.close();

        // Pass 2
        input_file.open("intermediate.txt");
        output_file.open("output.txt");
        Pass2();
        input_file.close();
        output_file.close();
        cout << "Pass 2 has finished successfully!\n";
    }
};

/**
 * @brief Load the operation table and close it to prevent any further future insertions by any other part of the code
 */
void LoadOpTable() {
    string opcode, val, line;
    stringstream ss;
    input_file.open("optab.txt");
    while (getline(input_file, line)) {
        ss << line;
        ss >> opcode;
        ss >> val;
        if(opcode == "" or val == "") {
            throw string("Invalid instruction format in optab.txt!");
        }
        OpTable.Insert(opcode, stoi(val, 0, 16));
        ss.clear();
    }
    input_file.close();
    OpTable.Close();
    cout << "Loaded Opcode Table successfully!\n";
}

int main () {
    try {
        LoadOpTable();
        AssemblerSIC sic_assembler;
        sic_assembler.Assemble();
    }
    catch (string err) {
        cerr << "Error: " << err << endl;
    }
}