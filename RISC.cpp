#include <bits/stdc++.h>
using namespace std;

struct Instruction {
    string type; // e.g. "ADD", "SUB", "LOAD"
    int rd, rs1, rs2, imm;
};

struct PipelineReg {
    Instruction inst;
    int aluResult = 0, memData = 0;
    bool valid = false;
};

vector<int> registers(32, 0);
vector<int> memory(1024, 0);
queue<Instruction> instrMem;

void IF_stage(PipelineReg &reg, queue<Instruction> &instrMem) {
    if (!instrMem.empty()) {
        reg.inst = instrMem.front();
        reg.valid = true;
        instrMem.pop();
        cout << "  IF: Fetched " << reg.inst.type << "\n";
    }
}

void ID_stage(PipelineReg &reg) {
    if (reg.valid) {
        cout << "  ID: Decoding " << reg.inst.type << "\n";
    }
}

void EX_stage(PipelineReg &reg) {
    if (!reg.valid) return;
    if (reg.inst.type == "ADD") {
        reg.aluResult = registers[reg.inst.rs1] + registers[reg.inst.rs2];
    } else if (reg.inst.type == "SUB") {
        reg.aluResult = registers[reg.inst.rs1] - registers[reg.inst.rs2];
    } else if (reg.inst.type == "LOAD") {
        reg.aluResult = reg.inst.rs1 + reg.inst.imm; // address calc
    } else if (reg.inst.type == "STORE") {
        reg.aluResult = reg.inst.rs1 + reg.inst.imm; // address calc
    }
    cout << "  EX: Executing " << reg.inst.type << "\n";
}

void MEM_stage(PipelineReg &reg) {
    if (!reg.valid) return;
    if (reg.inst.type == "LOAD") {
        reg.memData = memory[reg.aluResult];
    } else if (reg.inst.type == "STORE") {
        memory[reg.aluResult] = registers[reg.inst.rs2];
    }
    cout << "  MEM: " << reg.inst.type << "\n";
}

void WB_stage(PipelineReg &reg) {
    if (!reg.valid) return;
    if (reg.inst.type == "ADD" || reg.inst.type == "SUB") {
        registers[reg.inst.rd] = reg.aluResult;
    } else if (reg.inst.type == "LOAD") {
        registers[reg.inst.rd] = reg.memData;
    }
    cout << "  WB: " << reg.inst.type;
    if (reg.inst.rd != 0)
        cout << " -> R" << reg.inst.rd << " = " << registers[reg.inst.rd];
    cout << "\n";
}

int main() {
    // Initialize registers for testing
    registers[2] = 10;
    registers[3] = 5;

    // Example program
    instrMem.push({"ADD", 1, 2, 3, 0}); // R1 = R2 + R3
    instrMem.push({"SUB", 4, 1, 2, 0}); // R4 = R1 - R2

    PipelineReg IF, ID, EX, MEM, WB;

    for (int cycle = 1; cycle <= 8; cycle++) {
        cout << "Cycle " << cycle << ":\n";

        WB_stage(WB);
        MEM_stage(MEM);
        EX_stage(EX);
        ID_stage(ID);
        IF_stage(IF, instrMem);

        // shift pipeline registers
        WB = MEM;
        MEM = EX;
        EX = ID;
        ID = IF;
        IF.valid = false; // reset IF for next cycle

        cout << "---------------------------\n";
    }

    cout << "\nFinal Register Values:\n";
    for (int i = 0; i < 8; i++) {
        cout << "R" << i << " = " << registers[i] << "\n";
    }
}

