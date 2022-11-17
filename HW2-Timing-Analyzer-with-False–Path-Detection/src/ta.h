#ifndef TA_H
#define TA_H
#include "header.h"

// Timing Analyzer with False Path Detection
class TimingAnalyzer {
    private:
        map<string, Cell*> pis;
        map<string, Cell*> cells;
        map<string, Net*> nets;
        unordered_map<string, Lib*> libs;

        vector<string> inputSeq;
        vector<vector<int>> patterns;
        vector<double> index_1;
        vector<double> index_2;

    public:
        TimingAnalyzer() {}
        ~TimingAnalyzer() {
            for (auto i : pis)
                delete i.second;
            for (auto i : cells)
                delete i.second;
            for (auto i : nets)
                delete i.second;
            for (auto i : libs)
                delete i.second;
        }
        void ReadInputFile(const char* netlistFile, const char* patFile, const char* libFile);
            void ReadNetList(const char* netlistFile);
            void ReadPat(const char* patFile);
            void ReadLib(const char* libFile);

        void GenOutputFile(const char* netlistFile);
            void GenOutputLoad(string caseName);
            void GenOutputDelay(string aseName);
            void GenOutputPath(string caseName);

        double LookUp(string cell, string tableName);
        double Interpolation(double cReq, double sReq, pair<double, double> s, pair<double, double> c, vector<double> p);
        void CalOutputLoading();
        void CalDelay(vector<int> pattern);
        void CalTransition(string name);
};

#endif
