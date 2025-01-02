#ifndef DFADecoder_H
#define DFADecoder_H

#include <iostream>
#include <string>
#include "DFAState.h"

class DFADecoder {
private:
    DFAState* dfa_start_state;
    std::string input;
    int line_number;
    int i;
public:
    DFADecoder(DFAState* dfa_start_state, std::string input, int line_number);
    std::pair<std::string, std::string> next_token();
};

#endif // DFADecoder_H