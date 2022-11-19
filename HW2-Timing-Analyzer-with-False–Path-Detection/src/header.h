#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <cmath>
#include <climits>
#include <cstring>
#include <regex>

using namespace std;
enum cellType { PI, PO, NAND, NOR, INV};
enum netType { IN, OUT, WIRE };

class Net;

class Cell {
    private:
        string name;
        int instanceNum;
        cellType type;
        vector<Net*> input;
        Net* output;
        double inputCapacitance = 0;
        double outputLoading = 0;

        double inputTransitionTime = 0;
        double outputTransitionTime = 0;

        double propagationDelay = 0; //look up table
        double pathDelay = 0; //from pi to this cell
        double longestDelay = 0;
        double shortestDelay = 0;
                              
        int inDegree = 0;
        bitset<1> value = 0;

    public:
        Cell(string name, cellType type) {
            this->name = name;
            this->type = type;
            regex num_regex("\\d+");
            smatch n;
            if (regex_search(name, n, num_regex))
                this->instanceNum = stoi(n.str());
        }
        Cell(string name, cellType type, bitset<1> value) {
            this->name = name;
            this->type = type;
            this->value = value;
            /*
             *regex num_regex("\\d+");
             *smatch n;
             *if (regex_search(name, n, num_regex))
             *    this->instanceNum = stoi(n.str());
             */
        }
        ~Cell() {}
        string GetName() { return name; }
        cellType GetType() { return type; }
        int GetInstanceNum() { return instanceNum; }

        void AddInput(Net* n) { input.push_back(n); }
        void AddOutput(Net* n) { output = n; }
        vector<Net*> GetAllInput() { return input; }
        Net* GetInput(int i) { return input[i]; }
        Net* GetOutput() { return output; }

        double GetInputCapacitance() { return inputCapacitance; }
        double GetOutputLoading() { return outputLoading; }
        double GetInputTransitionTime() { return inputTransitionTime; }
        double GetOutputTransitionTime() { return outputTransitionTime; }
        double GetPropagationDelay() { return propagationDelay; }
        double GetPathDelay() { return pathDelay; }
        double GetLongestDelay() { return longestDelay; }
        double GetShortestDelay() { return shortestDelay; }
        void SetInputCapacitance(double loading) { inputCapacitance = loading; }
        void SetOutputLoading(double loading) { outputLoading = loading; }
        void SetInputTransitionTime(double t) { inputTransitionTime = t; }
        void SetOutputTransitionTime(double t) { outputTransitionTime = t; }
        void SetPropagationDelay(double d) { propagationDelay = d; }
        void SetPathDelay(double d) { pathDelay = d;  }
        void AddPathDelay(double d) { pathDelay += d; }
        void SetLongestDelay(double d) { longestDelay = d; }
        void SetShortestDelay(double d) { shortestDelay = d; }

        int GetInDegree() { return inDegree; }
        void SetInDegree(int d) { inDegree = d; }
        void IncrInDegree() { ++inDegree; }
        void DecrInDegree() { --inDegree; }

        bitset<1> GetValue() { return value; }
        void SetValue(bitset<1> b) { value = b; }
        void ResetValue() { value.reset(); }
};

class Net{
    private:
        string name;
        netType type;
        pair<string, Cell*> preceeding;         //connected output pin of fanin cell
        vector<pair<string, Cell*>> succeeding; //connected input pins of fanout cell
    public:
        Net(string name, netType type) {
            this->name = name;
            this->type = type;
        }
        ~Net() {}

        string GetName() { return name; }
        netType GetType() { return type; }
        void AddSucceding(pair<string, Cell*> p) { succeeding.push_back(p); }
        vector<pair<string, Cell*>> GetSucceding() { return succeeding; }
        void AddPrecceding(pair<string, Cell*> p) { preceeding = p; }
        pair<string, Cell*> GetPrecceding() { return preceeding; }
};

class Lib {
    private:
        string name;
        unordered_map<string, double> capacitance;
        map<string, vector<double>> table;
    public:
        Lib(string name) { this->name = name; }
        ~Lib() {}
        string GetName() { return name; }
        void AddCapacitance(pair<string, double> p) { capacitance.insert(p); }
        double GetCapacitance(string s) { return capacitance[s]; }
        unordered_map<string, double> GetAllCapacitance() { return capacitance; }

        map<string, vector<double>> GetAllTable() { return table; }
        vector<double> GetTable(string name) { return table[name]; }
        void AddTable(string name, double v) { table[name].push_back(v); }

        //find p0, p1, p2, p3 for 2-D Table Interpolation
        vector<double> GetP(string name, int idxI, int idxJ) {
            vector<int> idx;
            vector<double> p(4, 0);
            //cout << "GetP(): " << name << endl;
            vector<int> pos = { 0, 3, 2, 1 };
            int cnt = 0;
            for (int j = idxJ; j <= idxJ + 1; ++j)
                for (int i = idxI; i <= idxI + 1; ++i)
                    p[pos[cnt++]] = table[name][j * 7 + i];

            return p;
        }
};
