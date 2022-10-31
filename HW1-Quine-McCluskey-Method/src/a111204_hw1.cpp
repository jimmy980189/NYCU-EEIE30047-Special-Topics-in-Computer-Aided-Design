#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <unordered_map>
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
        int literal;
        int numIntersect = 0;
        vector<int> mpos;
        set<int> piCover;
        string V;
        bool prime = true; // true: * / false: |
        bool covering = false;
        bool deleted = false;
        
    public:
        PI(int v, int m, string s) { value = v; mask = m; V = s; };
        PI(int v, int m, string s, vector<int> p) {
            value = v; mask = m; V = s; mpos = p; 
        };
        ~PI() {};

        string GetLabel() { return label; };
        string GetV() { return V; };
        int GetValue() { return value; };
        int GetMask() { return mask; };
        int GetLiteral() { return literal; };
        bool GetPrime() { return prime; };
        bool GetCovering() { return covering; };
        bool GetDeleted() { return deleted; };
        vector<int> GetMpos() { return mpos; };
        set<int> GetPiCover() { return piCover; };

        void MposPushBack(int m) { mpos.push_back(m); };
        void PiCoverPushBack(int m) { piCover.insert(m); };
        void DeletePiCover(int m) { piCover.erase(m); }
        void SetLiteral(int l) { literal = l; };
        void SetPrime(bool flag) { prime = flag; };
        void SetCovering(bool flag) { covering = flag; };
        void SetV(string V) { this->V = V; };
        void SetLabel(string label) { this->label = label; };
        void SetDeleted(bool flag) { deleted = flag; };
        bool FindCover(int f) {
            return piCover.find(f) != piCover.end();
        }
        bool operator<(const PI& rhs) const {
            return V < rhs.V;
        }

        // return true if lhs is included in rhs
        // lhs is a subset of rhs if and only if lhs intersect rhs = lhs
        bool IsCoverIncludedIn(set<int> uncover, PI* rhs) {
            for (auto i : piCover)
                if ((uncover.find(i) != uncover.end()) && !rhs->FindCover(i))
                    return false;

            if (piCover.size() == rhs->GetPiCover().size())
                return false;

            return true;
        }

        void PrintCover() {
            cout << "cover: " << piCover.size() << " { ";
            for (auto i : piCover)
                cout << i << " ";
            cout << "}" << endl;
        };
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
        int literal = 0;
        set<int> onSet;
        set<int> dcSet;
        set<int> allSet;
        set<int> uncover;
        set<int> check;
        set<PI*, PIcmp> pset;
        set<PI*, PIcmp> essential;
        multimap<int, PI*> uncoverSet;
        multimap<int, PI*> table;
        multimap<int, PI*> candidate;
        multimap<int, PI*> column;

        set<PI*> garbage; // for collecting all new PI*

    public:
        QM() {};
        ~QM() {
            for (auto p : garbage)
                delete p;
        };

        void ReadInputFile(const char* filename);
        void GenOutputFile(const char* filename);

        void GenPrimaryImplicant();
        void InitColumn();
        void ColumnCovering();
        void Reduce(int r);
        int RowReduction();
        int FindEssential();

        void Print();
        void PrintOnSet();
        void PrintTable();
        void PrintCandidate();
        void PrintPrime();
        void PrintPset();
        void PrintColumn();
        void PrintUncover();
        void PrintEssential();
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
            PI* tmp = new PI(num, 0, bitset<BITSETLEN>(num).to_string());
            table.insert({cnt, tmp});
            garbage.insert(tmp);
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

    output << ".mc " << essential.size() << endl;
    for (auto e : essential) {
        string slice = e->GetV().substr(BITSETLEN - numVariables, BITSETLEN);
        output << slice << endl;
    }
    
    output << "literal=" << literal << endl;

    output.close();
}

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
                        candidate.insert({same.count(), new PI((int) same.to_ulong(), (int) mask.to_ulong(), tmp, record)});
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
    for (auto it : candidate)
        garbage.insert(it.second);

    table.clear();
    candidate.clear();
}

void QM::ColumnCovering() {

    int min = INT_MAX;

    InitColumn();
    uncover = onSet;

    while (uncover.size() > 1) {
        FindEssential();

        if (uncover.size() > 1) {
            RowReduction();
        }
    }

    if (uncover.size() == 1) {
        PI* tmp = NULL;
        for (auto i : column)
            if (i.second->GetLiteral() < min) {
                min = i.second->GetLiteral();
                tmp = i.second;
            }

        literal += tmp->GetLiteral();
        check.insert(*uncover.begin());
        essential.insert(tmp);
    }
}

void QM::InitColumn() {
    int cnt = 1;
    int num = 0;
    int cover = 0;
    int setCnt = 0;

    for (auto p : pset) {

        setCnt = bitset<BITSETLEN>(p->GetMask()).count();
        num = pow(2, setCnt);

        string l("P" + to_string(cnt++));
        p->SetLabel(l);
        p->SetLiteral(numVariables - setCnt);

        for (int i = 0; i < num; ++i) {
            bitset<BITSETLEN> ref = i;
            bitset<BITSETLEN> tmp;
            tmp.reset();

            for (int k = 0; k < setCnt; ++k)
                if (ref.test(k))
                    tmp.set(p->GetMpos()[k]);

            cover = tmp.to_ulong() | p->GetValue();

            if (dcSet.find(cover) == dcSet.end()) {
                p->PiCoverPushBack(cover);
                column.insert({cover, p});
            }
        }
    }
}

void QM::Reduce(int r) {
    int minLiteral = INT_MAX;

    multimap<int, PI*>::iterator f;

    auto range = column.equal_range(r);
    for (multimap<int, PI*>::iterator it = range.first; it != range.second; ++it) {
        if (it->first < minLiteral) {
            minLiteral = it->first;
            f = it;
        } 
    }

    f->second->SetCovering(true);
    essential.insert(f->second);
    literal += f->second->GetLiteral();

    auto tmp = f->second->GetPiCover();
    for (auto i : tmp) {
        check.insert(i);

        set<int>::iterator del = uncover.find(i);
        if (del != uncover.end())
            uncover.erase(del);

        auto range = column.equal_range(i);
        for (multimap<int, PI*>::iterator it = range.first; it != range.second; ) {
            it->second->DeletePiCover(i);
            it = column.erase(it);
        }
    }
}

int QM::FindEssential() {
    int numDel = 0;
    int max = INT_MIN;

    for (auto on : onSet) {
        int tmp = column.count(on);
        if (tmp > max)
            max = tmp;

        if (tmp == 1) {
            ++numDel;
            Reduce(on);
        }
    }

    if (numDel == 0) {
        Reduce(max);
    }

    onSet = uncover;

    return numDel;
}

int QM::RowReduction() {
    set<int> del;
    int reduce = 0;

    for (auto i : column) {
        for (auto j : column) {
            if (i.second != j.second && i.second->IsCoverIncludedIn(uncover, j.second)) {
                ++reduce;
                i.second->SetDeleted(true);
                del.insert(i.first);
                break;
            }
        }
    }

    for (multimap<int, PI*>::iterator it = column.begin(); it != column.end(); )
        if (it->second->GetDeleted())
            it = column.erase(it);
        else 
            ++it;

    return reduce;
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

void QM::PrintOnSet() {
    cout << "on-set: ";
    for (auto i : onSet)
        cout << i << " ";
    cout << endl;
}

void QM::PrintUncover() {
    cout << "uncover: ";
    for (auto i : uncover)
        cout << i << " ";
    cout << endl;
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

void QM::PrintColumn() {
    cout << "column: " << column.size() << endl;
    for (auto i : column) {
        cout << i.first << " " << i.second->GetLabel() << " ";
        cout << i.second->GetDeleted() << " ";
        cout << i.second->GetV() << " ";
        i.second->PrintCover();
    }
}

void QM::PrintPset() {
    cout << "pset: " << pset.size() << endl;
    cout << "Label V Prime Covering Literal" << endl;
    for (auto i : pset) {
        cout << i->GetLabel() << " ";
        cout << i->GetV() << " ";
        cout << i->GetPrime() << " ";
        cout << i->GetCovering() << " ";
        cout << i->GetLiteral() << " ";
        cout << bitset<BITSETLEN>(i->GetValue()) << " ";
        cout << bitset<BITSETLEN>(i->GetMask()) << endl;
        i->PrintCover();
    }
}

void QM::PrintEssential() {
    cout << "essential: " << essential.size() << endl;
    cout << "Label V Prime Covering Literal" << endl;
    for (auto i : essential) {
        cout << i->GetLabel() << " ";
        cout << i->GetV() << " ";
        cout << i->GetPrime() << " ";
        cout << i->GetCovering() << " ";
        cout << i->GetLiteral() << " ";
        cout << bitset<BITSETLEN>(i->GetValue()) << " ";
        cout << bitset<BITSETLEN>(i->GetMask()) << endl;
        i->PrintCover();
    }
}
