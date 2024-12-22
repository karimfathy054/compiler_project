#ifndef DFAMINIMIZERPARTITIONING_H
#define DFAMINIMIZERPARTITIONING_H

#include "DFAState.h"

class DFAMinimizerPartitioning {
private:
    DFAState* start_state;
    std::vector<DFAState*> all_states;
    
    std::vector<DFAState*> get_all_states(DFAState* start_state);
    std::unordered_map<std::string, std::vector<DFAState*>> split_on_accepting_states(std::vector<DFAState*> all_states);
public:
    DFAMinimizerPartitioning(DFAState* start_state);
    DFAState* minimize();
};

#endif // DFAMINIMIZERPARTITIONING_H