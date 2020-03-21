#ifndef __CONFIG_H
#define __CONFIG_H

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <cassert>

namespace ramulator
{

class Config {

private:
    std::map<std::string, std::string> options;
    int channels;
    int ranks;
    int subarrays;
    int cpu_tick;
    int mem_tick;
    int core_num = 0;
    long expected_limit_insts = 0;
    long warmup_insts = 0;

public:
    Config() {}
    Config(const std::string& fname);
    void parse(const std::string& fname); // defined in Config.cpp
    // overload [] to use ' ["variable"] = value ' syntax
    std::string operator [] (const std::string& name) const {
      if (options.find(name) != options.end()) {
        return (options.find(name))->second;
      } else {
        return "";
      }
    }

    // check if a certain variable key is present
    bool contains(const std::string& name) const {
      if (options.find(name) != options.end()) {
        return true;
      } else {
        return false;
      }
    }

    // if option in config not yet set, set that variable option to specified value
    void add (const std::string& name, const std::string& value) {
      if (!contains(name)) {
        options.insert(make_pair(name, value));
      } else {
        printf("ramulator::Config::add options[%s] already set.\n", name.c_str());
      }
    }

    // write private member
    void set_core_num(int _core_num) {core_num = _core_num;}

    //return private members
    int get_channels() const {return channels;}
    int get_subarrays() const {return subarrays;}
    int get_ranks() const {return ranks;}
    int get_cpu_tick() const {return cpu_tick;}
    int get_mem_tick() const {return mem_tick;}
    int get_core_num() const {return core_num;}
    long get_expected_limit_insts() const {return expected_limit_insts;}
    long get_warmup_insts() const {return warmup_insts;}

    bool has_l3_cache() const {
      if (options.find("cache") != options.end()) {
        const std::string& cache_option = (options.find("cache"))->second;
        return (cache_option == "all") || (cache_option == "L3");
      } else {
        return false;
      }
    }
    bool has_core_caches() const {
      if (options.find("cache") != options.end()) {
        const std::string& cache_option = (options.find("cache"))->second;
        return (cache_option == "all" || cache_option == "L1L2");
      } else {
        return false;
      }
    }
    bool is_early_exit() const {
      // the default value is true
      if (options.find("early_exit") != options.end()) {
        if ((options.find("early_exit"))->second == "off") {
          return false;
        }
        return true;
      }
      return true;
    }
    bool calc_weighted_speedup() const {
      return (expected_limit_insts != 0);
    }
    bool record_cmd_trace() const {
      // the default value is false
      if (options.find("record_cmd_trace") != options.end()) {
        if ((options.find("record_cmd_trace"))->second == "on") {
          return true;
        }
        return false;
      }
      return false;
    }

    // discern whether need to print on terminal
    bool print_cmd_trace() const {
      // the default value is false
      if (options.find("print_cmd_trace") != options.end()) {
        if ((options.find("print_cmd_trace"))->second == "on") {
          return true;
        }
        return false;
      }
      return false;
    }
};


} /* namespace ramulator */

#endif /* _CONFIG_H */

