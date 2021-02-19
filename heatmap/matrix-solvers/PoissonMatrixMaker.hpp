void find_jth_unknown(const MyVector<string> bwm_sep, const int des_j, int &j_i, int &j_j)
{
    if(des_j < 0)
        throw std::out_of_range("des_j value in find_jth_unknown negative");
        
    int num_black = -1;
    for(int i = int(bwm_sep.size() - 1); i >= 0; i--)
    {
        for(int j = 0; j < int(bwm_sep[i].size()); j++)
        {
            num_black += (bwm_sep[i][j] == 'B') ? 1 : 0;
            if(num_black == int(des_j))
            {
                j_i = i;
                j_j = j;
                return;
            }
        }
    }
    throw std::out_of_range("could not find jth unknown, there aren't j unknowns");
}

int get_unknown_dist(const MyVector<string> bwm_sep, const int first_i, 
    const int first_j, const int sec_i)
{
    // if index values are out of range, throw relevant error
    if(first_i < 0 || first_i >= int(bwm_sep.size()))
        throw std::out_of_range("first_i in get_unknown_dist out of range");
    if(first_j < 0 || first_j >= int(bwm_sep[0].size()))
        throw std::out_of_range("first_j in get_unknown_dist out of range");
    if(sec_i < 0 || sec_i >= int(bwm_sep.size()))
        throw std::out_of_range("sec_i in get_unknown_dist out of range");

    int dist = 0;
    // if the first 'B' value is closer to the beginning, iterate up to second 'B'
    if(first_i > sec_i)
    {
        for(int j = first_j + 1; j < int(bwm_sep[first_i].size()); j++)
            dist += (bwm_sep[first_i][j] == 'B') ? 1 : 0;
        for(int j = 0; j <= first_j; j++)
            dist += (bwm_sep[sec_i][j] == 'B') ? 1 : 0;
    }
    // if the second 'B' value is closer to the beginning, iterate down to second 'B'
    else
    {
        for(int j = first_j - 1; j >= 0; j--)
            dist += (bwm_sep[first_i][j] == 'B') ? 1 : 0;
        for(int j = int(bwm_sep[first_i].size() - 1); j >= first_j; j--)
            dist += (bwm_sep[sec_i][j] == 'B') ? 1 : 0;
    }
    return dist;
}

MyMatrix<double> calc_poisson_matrix(const string bw_matrix, MyVector<string> &bwm)
{
    // open up black and white matrix
    std::ifstream input_file;
    input_file.open(bw_matrix);
    
    // count the number of lines and number of unknowns in file, and also
    // save the contents of the file to a string vector for later usage
    string bw_line;
    int num_unknowns = 0;
    int num_lines = 0;
    MyVector<string> bwm_sep(0);
    while(getline(input_file, bw_line))
    {
        bwm_sep.resize(num_lines + 1);
        for(size_t i = 0; i < bw_line.size(); i++)
            num_unknowns += (bw_line[i] == 'B') ? 1 : 0;
        bwm_sep[num_lines] = bw_line;
        num_lines++;
    }
    input_file.close();

    // initialize n x (n+1) augmented matrix, where n = num_unknowns, and
    // the b portion of [A b] augmented matrix all set to zero (since boundaries
    // are always equivalent to zero and only boundaries are in solution vector)
    MyMatrix<double> poisson_system(num_unknowns, num_unknowns);

    // along the main diagonal of the system, assign a 1; along the b vector
    // of the augmented [A b] matrix, assign a 0
    for(size_t i = 0; i < poisson_system.rows(); i++)
        poisson_system[i][i] = 1;

    // for each unknown (a 'B'), look to all 4 adjacent char to see if it is
    // a B, if it is update that information so that adjacent char contributes
    // to the overall solution of that given unknown (add a -1/4)
    int largest_dist = 0;
    for(int j = 0; j < int(poisson_system.rows()); j++)
    {
        int jth_unknown_i, jth_unknown_j = 0;
        find_jth_unknown(bwm_sep, j, jth_unknown_i, jth_unknown_j);

        // examine the letter to the right
        if(jth_unknown_j + 1 < int(bwm_sep[jth_unknown_i].size()))
        {
            if(bwm_sep[jth_unknown_i][jth_unknown_j + 1] == 'B') 
                poisson_system[j][j + 1] = -0.25;
        }

        // examine the letter to the left
        if(jth_unknown_j - 1 >= 0)
        {
            if(bwm_sep[jth_unknown_i][jth_unknown_j - 1] == 'B')
                poisson_system[j][j - 1] = -0.25;
        }

        // examine the letter below
        if(jth_unknown_i + 1 < int(bwm_sep.size()))
        {
            if(bwm_sep[jth_unknown_i + 1][jth_unknown_j] == 'B')
            {
                int dist = get_unknown_dist(bwm_sep, jth_unknown_i, jth_unknown_j, jth_unknown_i + 1);
                poisson_system[j][j - dist] = -0.25;

                if(dist > largest_dist)
                    largest_dist = dist;
            }
        }

        // examine the letter above
        if(jth_unknown_i - 1 >= 0)
        {
            if(bwm_sep[jth_unknown_i - 1][jth_unknown_j] == 'B')
            {
                int dist = get_unknown_dist(bwm_sep, jth_unknown_i, jth_unknown_j, jth_unknown_i - 1);
                poisson_system[j][j + dist] = -0.25;

                if(dist > largest_dist)
                    largest_dist = dist;
            }
        }
    }

    bwm.resize(bwm_sep.size());
    bwm = bwm_sep;
    
    return poisson_system;
}

MyVector<double> calc_poisson_vector(const int rows, const double val)
{
    if(rows < 0)
        throw std::out_of_range("cant make poisson b vect of neg. size");

    MyVector<double> b(rows);
    for(size_t i = 0; i < b.size(); i++)
        b[i] = val;
    return b;
}