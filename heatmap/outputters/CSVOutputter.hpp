CSVOutputter::CSVOutputter(const MyVector<string> &bw, const MyVector<double> &s, const int num)
{
    if(int(s.size()) != num)
        throw std::invalid_argument("sol. vect. size not equal to num in CSVO()");

    bwm_sep.resize(bw.size());
    bwm_sep = bw;

    solution.resize(s.size());
    solution = s;

    n = num;

    ordered_sol.resize(bwm_sep.size());
    is_ordered = false;
}

CSVOutputter::CSVOutputter(const CSVOutputter &csvo)
{
    bwm_sep.resize(csvo.bwm_sep.size());
    bwm_sep = csvo.bwm_sep;

    solution.resize(csvo.solution.size());
    solution = csvo.solution;

    n = csvo.n;

    ordered_sol.resize(csvo.ordered_sol.size());
    is_ordered = csvo.is_ordered;    
}

void CSVOutputter::reset(const MyVector<string> &bw, const MyVector<double> &s, const int num)
{
    if(int(s.size()) != num)
        throw std::invalid_argument("sol. vect. size not equal to num in reset()");

    bwm_sep.resize(bw.size());
    bwm_sep = bw;

    solution.resize(s.size());
    solution = s;

    n = num;

    ordered_sol.resize(bwm_sep.size());
    is_ordered = false;
}

void swap(CSVOutputter &a, CSVOutputter &b)
{
    swap(a.bwm_sep, b.bwm_sep);
    swap(a.solution, b.solution);
    std::swap(a.n, b.n);
    swap(a.ordered_sol, b.ordered_sol);
    std::swap(a.is_ordered, b.is_ordered);
}

CSVOutputter& CSVOutputter::operator=(CSVOutputter csvo)
{
    swap(csvo, *this);
    return *this;
}

MyVector<string>& CSVOutputter::operator()()
{
    if(is_ordered) // if solution is already ordered, return it
        return ordered_sol;
    
    // for each line in the black/white char matrix taken from file
    int unknowns_remaining = n;
    for(size_t curr_line = 0; curr_line < bwm_sep.size(); curr_line++)
    {
        // count the total number of unknowns in the given line
        int num_unknowns_left = 0;
        for(const auto &bw_char : bwm_sep[curr_line])
            num_unknowns_left += (bw_char == 'B') ? 1 : 0;

        // store the amount of unknowns we will order in this line
        int unknowns_this_line = num_unknowns_left;

        // for each character in the given line (both black and white)
        for(size_t i = 0; i < bwm_sep[curr_line].size(); i++)
        {
            // if the character is a W, record a zero for its value
            if(bwm_sep[curr_line][i] == 'W')
                ordered_sol[curr_line] += "0";
            
            // otherwise, record the correct found B value from methods
            if(bwm_sep[curr_line][i] == 'B')
            {
                ordered_sol[curr_line] += 
                    std::to_string(solution[unknowns_remaining - num_unknowns_left]);
                num_unknowns_left--;
            }

            // if we are not at the end of the line, add a comma
            if(i != bwm_sep[curr_line].size() - 1)
                ordered_sol[curr_line] += ",";
        }

        // subtract the total amount of unknowns by amount we fixed this line
        unknowns_remaining -= unknowns_this_line;      
    }
    is_ordered = true; // set ordering to true (to save future computation)
    return ordered_sol; // return ordered string vector, ready to print
}

void CSVOutputter::output_to_file(const string out_file) const
{
    if(!is_ordered)
        throw std::invalid_argument("cant print unsolved outputter to file");
    
    std::ofstream out_stream(out_file);
    for(size_t i = 0; i < ordered_sol.size(); i++)
    {
        out_stream << ordered_sol[i];
        if(i != ordered_sol.size() - 1) 
            out_stream << endl;
    }
}

ostream& operator<<(ostream &out, const CSVOutputter &csvo)
{
    if(!csvo.is_ordered)
        throw std::invalid_argument("cant print unsolved outputter");
    
    for(const auto &line : csvo.ordered_sol)
        out << line << endl;
    
    return out;
}