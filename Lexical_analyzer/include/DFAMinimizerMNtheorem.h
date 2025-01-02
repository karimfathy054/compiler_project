#ifndef DFAMINIMIZERMNTHM_H
#define DFAMINIMIZERMNTHM_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "DFAState.h"

class DFAMinimizerMNtheorem {
    private:
        std::unordered_map<int,DFAState*> id_state_map;
        std::unordered_map<DFAState*,int> state_id_map;
        std::unordered_set<DFAState*> final_states;
        
    public:
        DFAMinimizerMNtheorem(DFAState* start_state);
        bool mark_cell(DFAState* first_state , DFAState* second_state);

        void minimize();

};

#endif