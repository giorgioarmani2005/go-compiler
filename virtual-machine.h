#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

struct Instruction
{
    std::string opcode;
    std::vector<std::string> operands;
};

typedef Instruction *InstructionRegister;
typedef Instruction *Memory;
typedef std::stack<int> RegisterStack;
typedef int *AccamulatorRegister;

class VirtualMachine
{
public:
    VirtualMachine(std::string path_to_bytecode);
    void run();

private:
    std::map<std::string, int> labeles_map;

    Memory instructions_memory = nullptr;

    std::vector<int> virtual_memory_variables;

    InstructionRegister REG_IP = nullptr;
    RegisterStack REG_SP;
    AccamulatorRegister REG_AX = nullptr;

    void init_VM_memory(std::vector<std::string> lines);
    void extend_virtual_memory(int add_size);

    void execute_action(int (*func)(int, int));
    void execute_action(bool (*func)(int, int));

    void execute_push();
    void execute_pop();
    void execute_print();
    void execute_compare();
    void execute_load();
    void execute_write();

    void execute_jump(bool (*condition)());
};