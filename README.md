
# RISC-V CPU with 5-Stage Pipelining (Simulator in C++)

## 📌 Overview
This project implements a **simulator for a 32-bit RISC-V CPU** with a classic 5-stage pipeline:
1. Instruction Fetch (IF)
2. Instruction Decode (ID)
3. Execute (EX)
4. Memory Access (MEM)
5. Write Back (WB)

The simulator models **pipeline hazards, forwarding logic, and branch handling**. It allows measurement of **CPI (cycles per instruction)** with and without pipelining.

---

## 🛠 Features
- Implements **RISC-V instructions**: `ADD`, `SUB`, `LOAD`, `STORE`, `BEQ`.
- 5-stage pipeline with **hazard detection & forwarding**.
- **Control hazard handling** with pipeline flush.
- Performance metrics: **stalls, CPI, execution cycles**.
- Extensible design to add new instructions.

---

## ⚙️ Architecture
Pipeline stages and registers:

