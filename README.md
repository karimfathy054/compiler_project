# Compiler Generator Project

This project is a compiler generator implemented in C++. It is divided into two main phases: the lexical phase and the parsing phase. Together, these phases create a fully functional compiler that can process input files based on user-defined rules.

---

## 📋 Features

### **Phase 1: Lexical Analysis**
- **Input:** Lexical rules.
- **Output:** Tokens and lexemes from the input file, or error messages if the input is invalid.
- **Process:**
  1. Generate an NFA (Non-deterministic Finite Automaton) from the lexical rules.
  2. Convert the NFA to a DFA (Deterministic Finite Automaton).
  3. Convert DFA to minimized DFA.
  4. Read the input file character by character.
  5. Output tokens and their corresponding lexemes.
  6. Error Handling: Recover from lexical errors, print detailed error messages, and continue processing the input.

---

### **Phase 2: Parsing**
- **Input:** Grammar rules (productions).
- **Output:** Leftmost derivation (parse tree) for the input file.
- **Process:**
  1. **Grammar Preprocessing:**
     - Convert the grammar into LL(1) format by:
       - Removing left recursion.
       - Applying left factoring.
  2. Build the **First** and **Follow** sets for each non-terminal.
  3. Construct the parsing table.
  4. Parse the input file using the lexical analysis phase.
  5. Output the productions and their leftmost derivations during the construction of the parse tree.
  6. Error Handling: Recover from parsing errors, print detailed error messages, and attempt to continue parsing the input.

---

## 🛠️ Usage

1. **Define Rules:**
   - Specify lexical rules for the tokens.
   - Provide grammar rules (productions) in a format suitable for LL(1) parsing.
2. **Compile Input:**
   - Input a text file containing the program/code to be compiled.
   - The project processes the input using the defined rules.
3. **Output:**
   - Tokens and lexemes.
   - Parse tree (leftmost derivation).

---

## 📚 How It Works
- **Lexical Analysis Phase:**
  The lexer converts the input file into a series of tokens while identifying and recovering from errors, ensuring robust processing.

- **Parsing Phase:**
  The parser builds a parse tree using LL(1) grammar rules and displays the step-by-step derivations. It also identifies and recovers from parsing errors to ensure the process can proceed as far as possible.

---

## 👥 Team Members
This project was developed by:
- **Karim Fathy**
- **Omar Tarek**
- **Marshelino Maged**
