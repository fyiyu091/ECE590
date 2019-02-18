#include "utilities.h"
#include <algorithm>

vector<double> sort_by_magnitude(vector<double> &v) {
    std::sort (v.begin(),v.end(),[](double x, double y){return abs(x) < abs(y);});
    return v;
    //std::sort (v.begin(),v.end());
     // Need to figure out how to use lambda function    
}

std::map<string, int> occurrence_map(const string path) {
//void occurrence_map(const string path) {
    // add your code here for question HW5.5
    std::ifstream fs(path);
    std::string line;
    std::map<string, int> mmap;
    bool has_speci = false;
    while(std::getline(fs,line))
    {
        //std::cout << "the word is " << line << '\n';
        // convert string to char *
        int s_length = line.length();
        char c_array[s_length];
        strcpy(c_array, line.c_str());
        char * tk;
        tk = strtok (c_array, " ");
        while (tk != NULL)
        {
            has_speci = false;
            // The segement of convert the token to the correct format
            // To lower case
            for (int i=0; i<string(tk).length(); i++)
            {
                  tk[i] = tolower(tk[i]);
            }
            //std::cout << "the tk is" << ' ' << tk << '\n';

            // Get rid of the punctuation
            // The special case of ."???
            char * tmp = tk;
            int ptr = 0;
            while (*tk)
            {
                if (*tk != ':' && *tk != ',' && *tk != '"' && *tk != '.' && *tk != '!')
                {
                    *(tmp+ptr) = *tk;
                    ptr++;
                }
                tk++;
            }
            *(tmp+ptr) = '\0';
            tk = tmp;

            // Check if the tk has the special 
            for (int i=0; i<string(tk).length(); i++)
            {
                // The judgement for containing the special char
                if (32<= int(tk[i]) && int(tk[i])<=38 || 40<= int(tk[i]) && int(tk[i])<=47 || 60<= int(tk[i]) && int(tk[i])<=64 || 91<= int(tk[i]) && int(tk[i])<=96 || 123<= int(tk[i]) && int(tk[i])<=127)
                {
                    has_speci = true;
                }
            }

            //std::cout << "the tk is" << ' ' << tk << '\n';
            // if the mmap doesn't have tk insert <str(tk):1>
            if (mmap.count(string(tk)) == 0 && has_speci == false)
            {
                mmap.insert(std::pair<string, double>(string(tk),1));
            }
            // if the mmap actually contains tk then count ++
            else if (has_speci == false)
            {
                mmap[string(tk)]++;
            }          
            tk = strtok (NULL, " ");
        }
    }
    return mmap;
}

TypedMatrix<double> read_matrix_csv(const string path) {
    // add code here
    std::ifstream fs(path);
    if (!fs.is_open())
    {
        throw std::invalid_argument("the file can't be opened");
    }
    std::string t_line;
    int row = 0;
    int column = 0;
    int i = 0;
    int j = 0;
    // To determine the size of the matrix
    while (std::getline(fs,t_line))     
    {
        row++;
        std::stringstream lineStream(t_line);
        std::string cell;
        column = 0;
        while (std::getline(lineStream,cell,','))
        {
            column++;
        }
    }
    TypedMatrix<double> results(column, row);
    fs.close();
    
    // The actually read function 
    std::ifstream t_file(path);
    std::string ts_line;
    // Set values into the results matrix
    while(std::getline(t_file,ts_line))
    {
        std::stringstream lineStream(ts_line);
        std::string data;
        j = 0;
        while (std::getline(lineStream,data,','))
        {
               //std::cout << "the data is " << data << '\n';
               //atof has some problem
               if (*data.c_str()=='"')
               {
                   results.set(i, j, atof(data.c_str()+1));
               }
               else
               {
                   results.set(i, j, atof(data.c_str()));
               }
               j++;
        }
        i++;
    }
    return results;
}

void write_matrix_csv(const TypedMatrix<double> &matrix, const string path) 
{
    int row = matrix.rows();
    int column = matrix.cols();
    std::ofstream t_file(path);
    for (int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            t_file << matrix.get(i,j) << ',';
        }
        t_file << '\n';
    }
}