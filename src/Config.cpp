#include "Config.h"

using namespace std;
using namespace ramulator;

Config::Config(const std::string& fname) {
  parse(fname);  //function defined below
}

void Config::parse(const string& fname)
{
    ifstream file(fname);

    assert(file.good() && "Bad config file");
    string line;
    while (getline(file, line)) {
        char delim[] = " \t=";
        vector<string> tokens;

        while (true) { // push strings in line into vector
          //size_t : unsigned integer type of the result of sizeof operator. Can store maximum size of theoretically possible object of any type
            size_t start = line.find_first_not_of(delim); 
            //put start to where there are no tabs (the start of word characters)
            if (start == string::npos) // there are no matches (empty file?)
                break;

            size_t end = line.find_first_of(delim, start);
            if (end == string::npos) {
                tokens.push_back(line.substr(start));
                break;
            }

            tokens.push_back(line.substr(start, end - start));
            //substr : first argument- start of character to extract, second argument- number of chacters to extract
            line = line.substr(end);
        }
        
        // empty line
        if (!tokens.size())
            continue;

        // make sure the parsed line isn't a comment line
        if (tokens[0][0] == '#')
            continue;

        // parameter line, make sure they're only two tokens on each line
        assert(tokens.size() == 2 && "Only allow two tokens in one line");

        options[tokens[0]] = tokens[1]; // map variable key and the value from configuration file

        // change data type to int if they are numbers
        if (tokens[0] == "channels") {
          channels = atoi(tokens[1].c_str());
        } else if (tokens[0] == "ranks") {
          ranks = atoi(tokens[1].c_str());
        } else if (tokens[0] == "subarrays") {
          subarrays = atoi(tokens[1].c_str());
        } else if (tokens[0] == "cpu_tick") {
          cpu_tick = atoi(tokens[1].c_str());
        } else if (tokens[0] == "mem_tick") {
          mem_tick = atoi(tokens[1].c_str());
        } else if (tokens[0] == "expected_limit_insts") {
          expected_limit_insts = atoi(tokens[1].c_str());
        } else if (tokens[0] == "warmup_insts") {
          warmup_insts = atoi(tokens[1].c_str());
        }
    }
    file.close();
}


