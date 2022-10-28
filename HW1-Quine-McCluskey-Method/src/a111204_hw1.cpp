#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <climits>

#define BITSETLEN 8

using namespace std;

//class for Prime Implicants
class PI {
    private:
        string label;
        int value;
        int mask;
        int numIntersect = 0;
        vector<int> mpos;
        vector<int> piCover;
        string V;
        bool prime = true; // true: * / false: |
        bool covering = false;
        
    public:
        PI(int v, int m, string s) { value = v; mask = m; V = s; };
        PI(int v, int m, string s, vector<int> p) {
            value = v; mask = m; V = s; mpos = p; 
        };
        ~PI() {};

        string GetLabel() { return label; };
        int GetValue() { return value; };
        int GetMask() { return mask; };
        string GetV() { return V; };
        bool GetPrime() { return prime; };
        bool GetCovering() { return covering; };
        vector<int> GetMpos() { return mpos; };
        vector<int> GetPiCover() { return piCover; };

        void MposPushBack(int m) { mpos.push_back(m); };
        void PiCoverPushBack(int m) { piCover.push_back(m); };
        void SetPrime(bool flag) { prime = flag; };
        void SetCovering(bool flag) { covering = flag; };
        void SetV(string V) { this->V = V; };
        void SetLabel(string label) { this->label = label; };
        bool operator<(const PI& rhs) const {
            return V < rhs.V;
        }
};

struct PIcmp {
    bool operator() (const PI* lhs, const PI* rhs) const {
        return *lhs < *rhs;
    }
};

//class for Quine-McCluskey
class QM {
    private:
        int numVariables;
        set<int> onSet;
        set<int> dcSet;
        set<int> allSet;
        set<PI*, PIcmp> pset;
        multimap<int, PI*> table;
        multimap<int, PI*> candidate;
        multimap<int, PI*> column;

        set<PI*> garbage;

    public:
        QM() {};
        ~QM() {
            for (auto p : pset)
                delete p;
            for (auto p : garbage)
                delete p;
        };

        void ReadInputFile(const char* filename);
        void GenOutputFile(const char* filename);

        void GenPrimaryImplicant();
        void ColumnCovering();

        void Print();
        void PrintTable();
        void PrintCandidate();
        void PrintPrime();
        void PrintPset();
};

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        cout << "./a.out [input file] [output file]" << endl;
        exit(-1);
    }

    QM Qm;
    Qm.ReadInputFile(argv[1]);

    Qm.GenPrimaryImplicant();
    Qm.ColumnCovering();

    Qm.GenOutputFile(argv[2]);

    return 0;
}

void QM::ReadInputFile(const char* filename) {
    int num;
    bool on = false;
    bool dc = false;
    string line;

    ifstream input(filename);
    if (input.fail()) {
        cout << "Failed at opening input file: " << filename << endl;
        exit(-1);
    }

    while (!input.eof()) {
        input >> line;
        if (line == ".i") {
            input >> this->numVariables;
        }
        else if (line == ".m") {
            on = true;
        }
        else if (line == ".d") {
            dc = true;
            on = false;
        }
        else {
            if (on) 
                onSet.insert(stoi(line));
            else if (dc)
                dcSet.insert(stoi(line));

            int num = stoi(line);
            int cnt = bitset<BITSETLEN>(num).count();
            allSet.insert(num);
            table.insert({cnt, new PI(num, 0, bitset<BITSETLEN>(num).to_string())});
        }
    }

    input.close();
}

void QM::GenOutputFile(const char* filename) {
    int cnt = 0;
    ofstream output(filename);
    if (output.fail()) {
        cout << "Failed at opening output file: " << filename << endl;
        exit(-1);
    }

    output << ".p " << pset.size() << endl;
    for (auto p : pset) {
        if (cnt++ < 15) {
            string slice = p->GetV().substr(BITSETLEN - numVariables, BITSETLEN);
            output << slice << endl;
        }
    }
    output << endl;

    output << ".mc " << "0" << endl;
    //for (auto :)
    
    output << "literal=" << "0" << endl;

    output.close();
}

void QM::Print() {
    cout << "onSet: " << endl;
    for (auto i : onSet)
        cout << i << " " << bitset<BITSETLEN>(i) << " " << bitset<BITSETLEN>(i).count() << endl;

    cout << "dcSet: " << endl;
    for (auto i : dcSet)
        cout << i << " " << bitset<BITSETLEN>(i) << " " << bitset<BITSETLEN>(i).count() << endl;

    cout << "allSet: " << endl;
    for (auto i : allSet)
        cout << i << " " << bitset<BITSETLEN>(i) << " " << bitset<BITSETLEN>(i).count() << endl;
}

bool cmp(int a, int b) {
    return bitset<BITSETLEN>(a).count() < bitset<BITSETLEN>(b).count();
}
//sort(this->allSet.begin(), this->allSet.end(), cmp);

void QM::GenPrimaryImplicant() {

    for (int run = 0; run < numVariables - 1; ++run) {
        for (int i = 0; i < numVariables; ++i) {
            auto rangeA = table.equal_range(i);
            auto rangeB = table.equal_range(i + 1);

            for (auto j = rangeA.first; j != rangeA.second; ++j) {
                for (auto k = rangeB.first; k != rangeB.second; ++k) {
                    int tmpA = j->second->GetValue();
                    int tmpB = k->second->GetValue();
                    bitset<BITSETLEN> mask = tmpA ^ tmpB;
                    bitset<BITSETLEN> same = tmpA & tmpB;
                    bitset<BITSETLEN> check = j->second->GetMask() ^ k->second->GetMask();
                    
                    if (mask.count() == 1 && check.none()) {

                        j->second->SetPrime(false);
                        k->second->SetPrime(false);
                        mask |= j->second->GetMask();

                        string tmp = same.to_string();
                        vector<int> record;
                        size_t idx = 0;
                        while (idx < mask.size()) {
                            if(mask.test(idx)) {
                                tmp[(BITSETLEN - 1) - idx] = '-';
                                record.push_back(idx);
                            }
                            ++idx;
                        }
                        candidate.insert({same.count(), new PI((int)same.to_ulong(), (int)mask.to_ulong(), tmp, record)});
                    }
                }
            }
        }
        
        for (auto it : table)
            if (it.second->GetPrime())
                pset.insert(it.second);
            else
                garbage.insert(it.second);

        table.clear();
        table = candidate;
    }

    table.clear();
    candidate.clear();
}

void QM::ColumnCovering() {

    int cnt = 1;
    int literal = 0;
    int minLiteral = INT_MAX;
    vector<vector<PI*>> P;
    vector<PI*> essential;
    set<int> already;

    for (auto p : pset) {
        //cout << p->GetV() << endl;

        int setCnt = bitset<4>(p->GetMask()).count();
        int num = pow(2, setCnt);

        string l("P" + to_string(cnt++));
        p->SetLabel(l);

        //cout << p->GetV() << endl;
        for (int i = 0; i < num; ++i) {
            bitset<BITSETLEN> ref = i;
            bitset<BITSETLEN> tmp;
            tmp.reset();

            for (auto j : p->GetMpos()) {
                for (int k = 0; k < setCnt; ++k) {
                    if (ref.test(k))
                        tmp.set(p->GetMpos()[k]);
                }
            }
            int cover = tmp.to_ulong() | p->GetValue();
            //cout << "cover: " << cover << endl;
            p->PiCoverPushBack(cover);
            column.insert({cover, p});
        }
    }

    /*
     *for (auto p : pset) {
     *    cout << "p cover: " << p->GetPiCover().size() << endl;
     *    for (auto c : p->GetPiCover()) {
     *        cout << c << endl;
     *    }
     *}
     */

    /*
     *cout << "column:" << endl;
     *for (auto i : column) {
     *    cout << i.first << " " << i.second->GetLabel() << endl;
     *}
     */


    set<int>::iterator on = onSet.begin();
    for (;on != onSet.end(); ++on) {
        
        if (column.count(*on) == 1) {
            auto f = column.find(*on);
            essential.push_back(f->second);
            //cout << "mini " << f->second->GetLabel() << " " << f->second->GetV() << endl;
            f->second->SetCovering(true);

            auto tmp = f->second->GetPiCover();
            for (auto i : tmp) {
                //cout << i << endl;

                set<int>::iterator del = onSet.find(i);
                if (del != onSet.end())
                    on = onSet.erase(del);

                auto range = column.equal_range(i);
                for (multimap<int, PI*>::iterator it = range.first; it != range.second; ) {
                    //cout << "c " << it->second->GetLabel() << endl;
                    it = column.erase(it);
                }
            }
        }
    }


    for (auto i : essential) 
        cout << i->GetLabel() << " " << i->GetV() << endl;

    cout << "---" << endl;

    for (auto o : onSet) {
        cout << o << endl;
        auto range = column.equal_range(o);
        for (multimap<int, PI*>::iterator it = range.first; it != range.second; ++it) { 
            cout << it->second->GetLabel() << " " << it->second->GetV() << endl;
        }
        /*
         *multimap<int, PI*>::iterator it = range.first;
         *cout << "( " << it->second->GetLabel() << " " << it++->second->GetV();
         *for (; it != range.second; ++it) { 
         *    cout << " + " << it->second->GetLabel() << " " << it->second->GetV();
         *}
         *cout << " )" << endl;
         */
    }
}

void QM::PrintTable() {
    cout << "table: " << endl;
    for (auto i : table) {
        cout << i.first << " " << bitset<BITSETLEN>(i.second->GetValue());
        cout << " " << i.second->GetPrime() << endl;
    }
}

void QM::PrintCandidate() {
    cout << "candidate: " << endl;
    for (auto i : candidate) {
        cout << i.first << " " << bitset<BITSETLEN>(i.second->GetValue());
        cout << " - " << bitset<BITSETLEN>(i.second->GetMask());
        cout << " = " << i.second->GetV();
        cout << " " << i.second->GetPrime() << endl;
    }
}

void QM::PrintPset() {
    cout << "pset: " << endl;
    for (auto i : pset) {
        cout << i->GetV() << " ";
        cout << i->GetPrime() << " ";
        cout << i->GetCovering() << " ";
        cout << bitset<BITSETLEN>(i->GetValue()) << " ";
        cout << bitset<BITSETLEN>(i->GetMask()) << endl;
    }
}
