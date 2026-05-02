#include <iostream>
#include <fstream>
#include <string>
#include "virtual-machine.h"
#include <map>
// Helper functions
bool has_label(std::string line)
{
    return !line.empty() && line.back() == ':' && line.find(' ') == std::string::npos;
}

bool is_number(std::string s)
{
    for (auto c : s)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

bool is_virtual_memory(std::string operand)
{
    if (operand.length() >= 3 && operand[0] == '[' && operand[operand.length() - 1] == ']' && is_number(operand.substr(1, operand.length() - 2)))
    {
        return true;
    }
    std::cerr << "[!] Error: Invalid virtual memory operand format: " << operand << std::endl;
    return false;
}

int get_virtual_memory_address(std::string operand)
{
    std::string var_address = operand.substr(1, operand.length() - 2);
    return std::stoi(var_address);
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//

VirtualMachine::VirtualMachine(std::string path_to_asm)
{
    std::ifstream bytecode_file(path_to_asm);
    if (!bytecode_file.is_open())
    {
        std::cerr << "[!] Error: Could not open bytecode file: " << path_to_asm << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(bytecode_file, line))
    {
        if (line.empty())
            continue;

        if (has_label(line))
        {
            std::string label_name = line.substr(0, line.length() - 1);
            labeles_map[label_name] = lines.size();
            continue;
        }
        lines.push_back(line);
    }

    instructions_memory = new Instruction[lines.size() + 1]; //+1 because HALT may be missing

    REG_AX = new int(0);

    init_VM_memory(lines);
}

void VirtualMachine::init_VM_memory(std::vector<std::string> lines)
{
    for (size_t i = 0; i < lines.size(); ++i)
    {
        std::string line = lines[i];
        std::string label_name;
        size_t space_pos = line.find(' ');

        if (space_pos != std::string::npos)
        {
            instructions_memory[i].opcode = line.substr(0, space_pos);
            std::string operands_str = line.substr(space_pos + 1);

            if (has_label(operands_str))
            {
                label_name = line.substr(space_pos + 1, line.length() - 1);
                labeles_map[label_name] = i + 1; //+1 because i=0 in for
                instructions_memory[i].operands.push_back(label_name);
                continue;
            }

            size_t start = 0;
            size_t end = operands_str.find(',');
            while (end != std::string::npos)
            {
                instructions_memory[i].operands.push_back(trim(operands_str.substr(start, end - start)));
                start = end + 1;
                end = operands_str.find(',', start);
            }
            instructions_memory[i].operands.push_back(trim(operands_str.substr(start)));
        }
        else
        {
            instructions_memory[i].opcode = line;
        }
    }

    virtual_memory_variables.resize(100); // 100 VARIABLES IN DEFAULT
}

void VirtualMachine::execute_action(int (*func)(int, int))
{
    if (REG_SP.size() < 2)
    {
        std::cerr << "[!] Error: Binary instruction requires exactly 2 operands." << std::endl;
        return;
    }
    int right = REG_SP.top();
    REG_SP.pop();

    int left = REG_SP.top();
    REG_SP.pop();

    int result = func(left, right);
    REG_SP.push(result);
}

void VirtualMachine::execute_action(bool (*func)(int, int))
{
    if (REG_SP.size() < 2)
    {
        std::cerr << "[!] Error: logical instruction requires exactly 2 operands." << std::endl;
        return;
    }
    int right = REG_SP.top();
    REG_SP.pop();

    int left = REG_SP.top();
    REG_SP.pop();

    int result = func(left, right);
    REG_SP.push(result);
}

void VirtualMachine::execute_push()
{
    if (REG_IP == nullptr)
    {
        std::cerr << "[!] Error: Instruction pointer is null." << std::endl;
        return;
    }
    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: PUSH instruction requires an operand." << std::endl;
        return;
    }
    if (REG_IP->operands[0] == "ax" && REG_AX == nullptr)
    {
        std::cerr << "[!] Error: Accumulator register is null." << std::endl;
        return;
    }
    int value = (REG_IP->operands[0] == "ax") ? *REG_AX : std::stoi(REG_IP->operands[0]);
    REG_SP.push(value);
}

void VirtualMachine::execute_pop()
{
    if (REG_IP == nullptr)
    {
        std::cerr << "[!] Error: Instruction pointer is null." << std::endl;
        return;
    }
    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: POP instruction requires an operand." << std::endl;
        return;
    }
    if (REG_SP.empty())
    {
        std::cerr << "[!] Error: Stack underflow on POP instruction." << std::endl;
        return;
    }

    if (REG_IP->operands[0] == "ax")
    {
        int value = REG_SP.top();
        REG_SP.pop();
        *REG_AX = value;
    }
    else
    {
        std::cerr << "[!] Error: Unsupported POP operand: " << REG_IP->operands[0] << std::endl;
    }
}

void VirtualMachine::execute_print()
{
    if (REG_IP == nullptr)
    {
        std::cerr << "[!] Error: Instruction pointer is null." << std::endl;
        return;
    }
    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: PRINT instruction requires an operand." << std::endl;
        return;
    }

    if (REG_IP->operands[0] == "ax")
    {
        std::cout << *REG_AX << std::endl;
    }
    else
    {
        std::cerr << "[!] Error: Unsupported PRINT operand: " << REG_IP->operands[0] << std::endl;
    }
}

void VirtualMachine::run()
{
    REG_IP = instructions_memory;

    while (!REG_IP->opcode.empty() && REG_IP->opcode != "HALT")
    {
        if (REG_IP->opcode == "PUSH")
        {
            execute_push();
        }
        else if (REG_IP->opcode == "POP")
        {
            execute_pop();
        }
        else if (REG_IP->opcode == "LOAD")
        {
            execute_load();
        }
        else if (REG_IP->opcode == "WRITE")
        {
            execute_write();
        }
        else if (REG_IP->opcode == "PRINT")
        {
            execute_print();
        }
        else if (REG_IP->opcode == "SUM")
        {
            execute_action([](int a, int b)
                           { return a + b; });
        } else if(REG_IP->opcode == "XOR")
        {
            execute_action([](int a, int b)
                           { return a ^ b; });
        }
        else if (REG_IP->opcode == "LSHIFT")
        {
            execute_action([](int a, int b)
                           { return a << b; });
        }
        else if (REG_IP->opcode == "RSHIFT")
        {
            execute_action([](int a, int b)
                           { return a >> b; });
        }
        else if (REG_IP->opcode == "SUB")
        {
            execute_action([](int a, int b)
                           { return a - b; });
        }
        else if (REG_IP->opcode == "MUL")
        {
            execute_action([](int a, int b)
                           { return a * b; });
        }
        else if (REG_IP->opcode == "DIV")
        {
            execute_action([](int a, int b)
                           { return a / b; });
        }
        else if (REG_IP->opcode == "MOD")
        {
            execute_action([](int a, int b)
                           { return a % b; });
        }
        else if (REG_IP->opcode == "AND")
        {
            execute_action([](int a, int b)
                           { return a & b; });
        }
        else if (REG_IP->opcode == "OR")
        {
            execute_action([](int a, int b)
                           { return a | b; });
        }
        else if (REG_IP->opcode == "CMP")
        {
            execute_compare();
        }
        else if (REG_IP->opcode == "JMP")
        {
            execute_jump([]()
                         { return true; });
        }
        else if (REG_IP->opcode == "JMPEQ")
        { // JUMP IF SP==1
            if (!REG_SP.empty() && REG_SP.top() == 1)
            {
                execute_jump([]()
                             { return true; });
            }
            if (!REG_SP.empty())
                REG_SP.pop();
        }
        else
        {
            std::cerr << "[!] Error: Unknown opcode: " << REG_IP->opcode << std::endl;
        }
        REG_IP++;
    }
}

void VirtualMachine::execute_compare()
{
    if (REG_SP.size() < 2)
    {
        std::cerr << "[!] Error: CMP instruction requires exactly 2 operands." << std::endl;
        return;
    }
    // if(a<b): push a; push b

    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: CMP instruction requires a comparison operator operand." << std::endl;
        return;
    }
    int right = REG_SP.top();
    REG_SP.pop();

    int left = REG_SP.top();
    REG_SP.pop();

    if (REG_IP->operands[0] == "EQ")
    {
        REG_SP.push(left == right);
    }
    else if (REG_IP->operands[0] == "NEQ")
    {
        REG_SP.push(left != right);
    }
    else if (REG_IP->operands[0] == "GT")
    {
        REG_SP.push(left > right);
    }
    else if (REG_IP->operands[0] == "LW")
    {
        REG_SP.push(left < right);
    }
    else if (REG_IP->operands[0] == "GTEQ")
    {
        REG_SP.push(left >= right);
    }
    else if (REG_IP->operands[0] == "LWEQ")
    {
        REG_SP.push(left <= right);
    }
    else if (REG_IP->operands[0] == "AND")
    {
        REG_SP.push(left && right);
    }
    else if (REG_IP->operands[0] == "OR")
    {
        REG_SP.push(left || right);
    }
    else if (REG_IP->operands[0] == "NOT")
    {
        REG_SP.push(!left);
    }
    else if (REG_IP->operands[0] == "XOR")
    {
        REG_SP.push(left ^ right);
    }
    else
    {
        std::cerr << "[!] Error: Unsupported CMP operator: " << REG_IP->operands[0] << std::endl;
        return;
    }
}

void VirtualMachine::execute_load()
{
    if (REG_IP == nullptr)
    {
        std::cerr << "[!] Error: Instruction pointer is null." << std::endl;
        return;
    }
    if (REG_IP->operands.size() < 2)
    {
        std::cerr << "[!] Error: LOAD instruction requires an two operand." << std::endl;
        return;
    }
    if (REG_IP->operands[0] == "ax" && is_virtual_memory(REG_IP->operands[1]))
    {
        *REG_AX = virtual_memory_variables[get_virtual_memory_address(REG_IP->operands[1])];
    }
    else
    {
        std::cerr << "[!] Error: Unsupported LOAD operands: " << REG_IP->operands[0] << ", " << REG_IP->operands[1] << std::endl;
    }
}

void VirtualMachine::execute_write()
{
    if (REG_IP == nullptr)
    {
        std::cerr << "[!] Error: Instruction pointer is null." << std::endl;
        return;
    }
    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: WRITE instruction requires an operand." << std::endl;
        return;
    }
    if (is_virtual_memory(REG_IP->operands[0]) && REG_IP->operands[1] == "ax")
    {
        if (REG_AX == nullptr)
        {
            std::cerr << "[!] Error: Accumulator register is null." << std::endl;
            return;
        }
        if (get_virtual_memory_address(REG_IP->operands[0]) > virtual_memory_variables.size())
        {
            // std::cout<<"New memory..\n";
            virtual_memory_variables.resize(get_virtual_memory_address(REG_IP->operands[0]) + virtual_memory_variables.size());
        }
        virtual_memory_variables[get_virtual_memory_address(REG_IP->operands[0])] = *REG_AX;
    }
    else
    {
        std::cerr << "[!] Error: Unsupported WRITE operands: " << REG_IP->operands[0] << ", " << REG_IP->operands[1] << std::endl;
    }
}

void VirtualMachine::execute_jump(bool (*condition)())
{
    if (REG_IP->operands.empty())
    {
        std::cerr << "[!] Error: JUMP instruction requires a label operand." << std::endl;
        return;
    }
    std::string label = REG_IP->operands[0];
    int addr_label = labeles_map[label] - 1; // beacause in run() we do REG_IP++ after execute_jump()

    if (condition())
    {
        REG_IP = &instructions_memory[addr_label];
    }
}
