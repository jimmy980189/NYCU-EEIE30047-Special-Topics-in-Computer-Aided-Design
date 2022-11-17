#include "ta.h"
#define MAX_LINE_LENGTH 2048

extern string studentID;

void TimingAnalyzer::ReadInputFile(const char* netlistFile, const char* patFile, const char* libFile) {
    ReadNetList(netlistFile);
    ReadPat(patFile);
    ReadLib(libFile);
}

void TimingAnalyzer::ReadNetList(const char* netlistFile) {
    ifstream fNetlist(netlistFile);
    if (fNetlist.fail()) {
        cout << "Failed to open file: " << netlistFile << endl;
        exit(-1);
    }

    cout << "-----------------------------" << endl;
    cout << "Start parsing input netlist" << endl;
    cout << "netlist filename: " << netlistFile << endl;
    cout << "verilog: " << endl;
    cout << "-----------------------------" << endl;

    string line;
    regex replace_regex("(\\/\\/.*)|(\\/\\*[^*\\/]*\\*\\/)|(^\\s+)");
    regex openComment_regex("\\/\\*[^\\*\\/]*$");
    regex closeComment_regex("([^\\*\\/]*\\*\\/)");
    regex space_regex("(\\s+)");
    regex word_regex("\\w+");
    regex cell_regex("(NOR2\\w*)|(NAND\\w*)|(INV\\w*)");
    regex pin_regex("(output)|(input)|(wire)");
    smatch firstWord;
    bool comment = false;

    while(getline(fNetlist, line)) {
        line = regex_replace(line, replace_regex, "");
        //cout << line << endl;
        line = regex_replace(line, space_regex, " ");
        //cout << line << endl;
        Cell* c;
        cellType type;

        if (line.size()) {
            if (regex_search(line, firstWord, pin_regex)) {
                cout << line << endl;
                netType type;
                if (firstWord.str() == "input")
                    type = IN;
                else if (firstWord.str() == "output")
                    type = OUT;
                if (firstWord.str() == "wire")
                    type = WIRE;

                Net* n;
                auto words_begin = sregex_iterator(line.begin() + firstWord.str().length(), line.end(), word_regex);
                for (sregex_iterator i = words_begin; i != sregex_iterator(); ++i) {
                    string name = (*i).str();
                    n = new Net(name, type);
                    nets.insert({name, n});
                }
            }
            //else if (regex_search(line, firstWord, cell_regex)) {
            else {
                //cout << "LINE: " << line << endl;
                if (comment && !regex_search(line, firstWord, closeComment_regex)) { 
                    cout << "comment continue " << line << endl;
                    continue; 
                }

                if (regex_search(line, firstWord, openComment_regex)) {
                    comment = true;
                    cout << "FOUND open: " << line << " " << comment << endl;
                }
                else if (regex_search(line, firstWord, closeComment_regex)) {
                    comment = false;
                    cout << "FOUND close: " << line << " " << comment << endl;
                    continue;
                }

                cout << line << endl;

                if (regex_search(line, firstWord, cell_regex)) {
                    if (line.substr(0, 3) == "NAN")
                        type = NAND;
                    else if (line.substr(0, 3) == "NOR")
                        type = NOR;
                    else if (line.substr(0, 3) == "INV")
                        type = INV;

                    auto words_begin = sregex_iterator(line.begin() + firstWord.str().length(), line.end(), word_regex);
                    if (words_begin != sregex_iterator()) {
                        string name = (*words_begin).str();
                        c = new Cell(name, type);
                        cells.insert({name, c});
                        ++words_begin;
                    }
                }
                    
                int cnt = 0;
                auto words_begin = sregex_iterator(line.begin(), line.end(), word_regex);
                for (sregex_iterator i = words_begin; i != sregex_iterator(); ++i) {
                    string pin = (*i++).str();
                    string net = (*i).str(); 
                    if (pin == "ZN") {
                        c->AddOutput(nets[net]);
                        nets[net]->AddPrecceding(pair<string, Cell*>(pin, c));
                        if(nets[net]->GetType() == OUT)
                            c->SetOutputLoading(0.03);
                    }
                    else if ((pin == "I") || (pin == "A1") || (pin == "A2")) {
                        c->AddInput(nets[net]);
                        nets[net]->AddSucceding(pair<string, Cell*>(pin, c));
                        if (nets[net]->GetType() != IN)
                            c->IncrInDegree();
                    }
                    /*
                     *else if (pin == "I") {
                     *    nets[net]->AddSucceding(pair<string, Cell*>(pin, c));
                     *}
                     *else if (pin == "A1") {
                     *    nets[net]->AddSucceding(pair<string, Cell*>(pin, c));
                     *}
                     *else if (pin == "A2") {
                     *    nets[net]->AddSucceding(pair<string, Cell*>(pin, c));
                     *}
                     */
                }
            }
        }
    }

    cout << "-------[output]-------" << endl;
    cout << " ---> " << endl;
    for (auto i : cells) {
        cout << i.second->GetName() << " " << i.second->GetType() << ": ";
        cout << i.second->GetOutput()->GetName() << " " << i.second->GetInDegree() << endl;
    }
    cout << " <--- " << endl;
    for (auto i : cells) {
        cout << i.second->GetName() << " " << i.second->GetType() << ": ";
        for (auto j : i.second->GetAllInput())
            cout << j->GetName() << " ";
        cout << endl;
    }

    cout << "---" << endl;

    for (auto i : nets) {
        cout << i.second->GetName() << " " << i.second->GetType() << ": ";
        for (auto j : i.second->GetSucceding())
            cout << j.second->GetName() << " (" << j.first << ") ";
        cout << endl;
    }

    fNetlist.close();
}

void TimingAnalyzer::ReadPat(const char* patFile) {
    ifstream fPat(patFile);
    if (fPat.fail()) {
        cout << "Failed to open file: " << patFile << endl;
        exit(-1);
    }

    cout << "----START READ PAT----" << endl;

    string line;
    regex word_regex("\\w+");
    int cnt = 0;

    while(getline(fPat, line)) {
        //if (cnt++ > 0) 
        cout << "LINE:" << line << endl;
        regex replace_regex("(\\/\\/.*)|(\\/\\*[^*\\/]*\\*\\/)|(^\\s+)");
        line = regex_replace(line, replace_regex, "");
        auto words_begin = sregex_iterator(line.begin(), line.end(), word_regex);
        if (cnt == 0)
            ++words_begin;
        else
            patterns.push_back(vector<int>());
        int idx = 0;
        for (sregex_iterator i = words_begin; i != sregex_iterator(); ++i, ++idx) {
            string tmp = (*i).str();
            //cout << "l: " << tmp << endl;
            if (cnt == 0)
                inputSeq.push_back(tmp);
            else if (cnt > 0 && (*i).str() != "end")
                patterns[cnt - 1].push_back(stoi(tmp));
                //cout << cnt << " " << inputSeq[idx] << ": " << tmp << endl;
        }
        ++cnt;
    }
    patterns.pop_back();

    cout << "----check----" << endl;
    for (auto i : inputSeq)
        cout << i << endl;

    for (auto i : patterns) {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }


    fPat.close();
}

void TimingAnalyzer::ReadLib(const char* libFile) {
    ifstream fLib(libFile);
    if (fLib.fail())  {
        cout << "Failed to open file: " << libFile << endl;
        exit(-1);
    }

    cout << "----Start Parsing Lib----" << endl;

    regex word_regex("\\w+");
    regex float_regex("0.[\\d]+");
    regex replace_regex("(\\/\\/.*)|(\\/\\*.*\\*\\/)|(\\s+)");
    regex space_regex("(\\s+)");
    regex find_regex("(cell\\(.*\\))|(pin\\(.*\\))|(capacitance:0.[\\d]+)|(0.[\\d]+)");
    smatch s;

    string line;
    string cell;
    string pin;
    Lib* lib;
    int cnt = 0;
    int vCnt = 0;
    int tableCnt = 0;
    double tmp = 0;
    vector<string> cellName = { "NOR2X1", "INVX1", "NANDX1" };
    vector<string> tableName = { "rise_power", "fall_power", "cell_rise", 
        "cell_fall", "rise_transition", "fall_transition" };

    while(getline(fLib, line)) {
        line = regex_replace(line, replace_regex, "");
        if (line.size() > 1) {
            //cout << line << endl;
            auto words_begin = sregex_iterator(line.begin(), line.end(), find_regex);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); ++i) {
                string word = (*i).str();
                if (cnt < 7) {
                    index_1.push_back(stof(word));
                }
                else if (cnt < 14) {
                    index_2.push_back(stof(word));
                }
                else if (cnt > 13 && (regex_search(word, s, word_regex))) {
                    //cout << cnt << " " << word << " " << s.str() << endl;
                    int l = s.str().size();
                    if (s.str() == "cell") {
                        int last = word.find_last_of(")");
                        cell = word.substr(l + 1, last - l - 1);
                        //cout << s.str() << " " << cell << endl;
                        lib = new Lib(cell);
                        libs.insert({cell, lib});
                    }
                    else if (s.str() == "pin") {
                        int last = word.find_last_of(")");
                        pin = word.substr(l + 1, last - l - 1);
                        //cout << s.str() << " " << pin << endl;
                    }
                    else if (s.str() == "capacitance") {
                        tmp = stof(word.substr(l + 1));
                        /*
                         *cout << pin << " " << tmp << endl;
                         *cout << s.str() << " " << tmp << endl;
                         */
                        libs[cell]->AddCapacitance(pair<string, double>(pin, tmp));
                    }
                    else if (s.str() == "0") {
                        //cout << "AddTable(): " << cell << " " << tableName[tableCnt] << " " << word << endl;
                        libs[cell]->AddTable(tableName[tableCnt], stof(word));

                        if (vCnt++ % 49 == 48)
                            tableCnt = (tableCnt + 1) % 6;

                        //++vCnt;
                    }
                }
                ++cnt;
            }
        }
    }

    cout << "----check----" << endl;
    cout << "index_1: ";
    for (auto i : index_1)
        cout << i << " ";
    cout << endl;

    cout << "index_2: ";
    for (auto i : index_2)
        cout << i << " ";
    cout << endl;

    for (auto i : libs) {
        cout << i.second->GetName() << endl;
        for (auto j : i.second->GetAllCapacitance()) {
            cout << j.first << " " << j.second << endl;
        }
    }

    int tmpCnt = 0;
    //for (auto i :libs["NOR2X1"]->GetTable("rise_power"))
    //for (auto i :libs["NOR2X1"]->GetTable("fall_power"))
    for (auto i :libs["INVX1"]->GetTable("rise_transition"))
        if (tmpCnt++ % 7 !=6)
            cout  << i << " ";
        else
            cout << i << endl;
    cout << "-------------" << endl;
    for (auto i :libs["NOR2X1"]->GetTable("fall_power"))
    //for (auto i :libs["INVX1"]->GetTable("rise_transition"))
        if (tmpCnt++ % 7 !=6)
            cout  << i << " ";
        else
            cout << i << endl;
    cout << "-------------" << endl;

    fLib.close();
}

void TimingAnalyzer::GenOutputFile(const char* netlistFile) {
    string caseName; 

    if (netlistFile) {
        string filename(netlistFile);
        int start = filename.find_last_of("/");
        int end = filename.find_last_of(".");
        caseName = filename.substr(start + 1, end - start - 1);
    }

    cout << "-----------------------------" << endl;
    cout << "Start generating output files" << endl;
    cout << "case name: " << caseName << endl;
    cout << "-----------------------------" << endl;

    GenOutputLoad(caseName);
    GenOutputDelay(caseName);
    GenOutputPath(caseName);
}

bool cmpLoading(Cell* a, Cell* b) {
    return (a->GetOutputLoading() != b->GetOutputLoading()) ? 
        a->GetOutputLoading() > b->GetOutputLoading() : a->GetInstanceNum() < b->GetInstanceNum();
}

void TimingAnalyzer::GenOutputLoad(string caseName) {
    string filename = studentID + "_" + caseName + "_load.txt";
    ofstream fLoad(filename);
    if (fLoad.fail()) {
        cout << "Failed to open file: " << filename << endl;
        exit(-1);
    }
    CalOutputLoading();

    vector<Cell*> sorted;
    for (auto i : cells)
        sorted.push_back(i.second);

    sort(sorted.begin(), sorted.end(), cmpLoading);
    
    for (auto i : sorted)
        fLoad << i->GetName() << " " << i->GetOutputLoading() << endl;

    fLoad.close();
}

bool cmpDelay(Cell* a, Cell* b) {
    return a->GetPropagationDelay() > b->GetPropagationDelay();
}

void TimingAnalyzer::GenOutputDelay(string caseName) {
    string filename = studentID + "_" + caseName + "_delay.txt";
    ofstream fDelay(filename);
    if (fDelay.fail()) {
        cout << "Failed to open file: " << filename << endl;
        exit(-1);
    }
    cout << "PATTERN: " << patterns.size() << endl;
    for (int i = 0; i < patterns.size(); ++i) {
        vector<Cell*> sorted;
        CalDelay(patterns[i]);
        for (auto i : cells)
            sorted.push_back(i.second);
        sort(sorted.begin(), sorted.end(), cmpDelay);
    
        for (auto i : sorted) {
            fDelay << i->GetName() << " " << i->GetValue() << " ";
            fDelay << i->GetPropagationDelay() << " " << i->GetOutputTransitionTime() << endl;
        }
        if (i != patterns.size() - 1)
            fDelay << endl;
    }

    fDelay.close();
}

void TimingAnalyzer::GenOutputPath(string caseName) {
    string filename = studentID + "_" + caseName + "_path.txt";
    ofstream fPath(filename);
    if (fPath.fail()) {
        cout << "Failed to open file: " << filename << endl;
        exit(-1);
    }

    fPath.close();
}

void TimingAnalyzer::CalOutputLoading() {
    for (auto i : cells) {
        Net* tmp = i.second->GetOutput();
        double sum = i.second->GetOutputLoading();
        string gate;
        //cout << "[check]" << i.second->GetName() << " " << tmp->GetType() << " " << tmp->GetName() << endl;
        for (auto j : tmp->GetSucceding()) {
            switch (j.second->GetType()) {
                case NAND:
                    gate = "NANDX1";
                    break;
                case NOR:
                    gate = "NOR2X1";
                    break;
                case INV:
                    gate = "INVX1";
                    break;
            }
            //cout << j.first << " " << gate << " " << j.second->GetName() << endl;
            sum += libs[gate]->GetCapacitance(j.first);
        }
        cells[i.second->GetName()]->SetOutputLoading(sum);
    }
}

double TimingAnalyzer::LookUp(string cell, string tableName) {
    double inputTransitionTime = cells[cell]->GetInputTransitionTime();
    double outputLoading = cells[cell]->GetOutputLoading();
    double p0, p1, p2, p3;
    pair<double, double> c;
    pair<double, double> s;
    string gate;

    //cout << cell << " " << outputLoading << " " << inputTransitionTime << endl;

    switch (cells[cell]->GetType()) {
        case NAND:
            gate = "NANDX1";
            break;
        case NOR:
            gate = "NOR2X1";
            break;
        case INV:
            gate = "INVX1";
            break;
    }

    int i, j;
    for (i = 0; i < index_1.size(); ++i) {
        if (outputLoading < index_1[i]) {
            c.first = index_1[i - 1];
            c.second = index_1[i];
            break;
        }
    }
    for (j = 0; j < index_2.size(); ++j) {
        if (inputTransitionTime < index_2[j]) {
            s.first = index_2[j - 1];
            s.second = index_2[j];
            //cout << "FOUND" << endl;
            break;
        }
    }

    //cout << i << " " << j << endl;
    if (j == 0){
        ++j;
        s.first = index_2[j - 1];
        s.second = index_2[j];
    }

    //cout << "LookUp(): " << gate << " " << tableName << " ";
    //cout << libs[gate]->GetTable(tableName).size() << endl;
    /*
     *int cnt = 0;
     *for (auto i : libs[gate]->GetTable(tableName))
     *    if (cnt % 7 != 6)
     *        cout << i << " ";
     *    else
     *        cout << i << endl;
     */

    int idxI = i - 1;
    int idxJ = j - 1;
    vector<double> p = libs[gate]->GetP(tableName, idxI, idxJ);
    //0 3 2 1
    /*
     *tableName = "rise_transition";
     *s.first = index_2[0];
     *s.second = index_2[1];
     *vector<double> p = libs[gate]->GetP(tableName, 3, 0);
     *for (auto i : p)
     *    cout << i << endl;
     */

    /*
     *cout << c.first << " < " << outputLoading << " < " << c.second << endl;
     *cout << s.first << " < " << inputTransitionTime << " < " << s.second << endl;
     */

    return Interpolation(outputLoading, inputTransitionTime, s, c, p);
}

double TimingAnalyzer::Interpolation(double cReq, double sReq, pair<double, double> s, pair<double, double> c, vector<double> p) {
    double A = p[0] + ((p[2] - p[0]) / (s.second - s.first)) * (sReq - s.first);
    double B = p[3] + ((p[1] - p[3]) / (s.second - s.first)) * (sReq - s.first);
    return A + ((B - A) / (c.second - c.first)) * (cReq - c.first);
}

void TimingAnalyzer::CalTransition(string cell) {
    string table;
    bitset<1> output;
    Cell* tmp0;
    Cell* tmp1;
    double t0;
    double t1;
    double t;

    switch (cells[cell]->GetType()) {
        case NAND:
            tmp0 = cells[cell]->GetInput(0)->GetPrecceding().second;
            tmp1 = cells[cell]->GetInput(1)->GetPrecceding().second;
            t0 = tmp0->GetOutputTransitionTime();
            t1 = tmp1->GetOutputTransitionTime();
            if (t0 < t1 && tmp0->GetValue() == 0)
                t = t0;
            else if (t0 > t1 && tmp1->GetValue() == 0)
                t = t1;
            else
                t = max(t0, t1);
            break;
        case NOR:
            tmp0 = cells[cell]->GetInput(0)->GetPrecceding().second;
            tmp1 = cells[cell]->GetInput(1)->GetPrecceding().second;
            t0 = tmp0->GetOutputTransitionTime();
            t1 = tmp1->GetOutputTransitionTime();
            if (t0 < t1 && tmp0->GetValue() == 1)
                t = t0;
            else if (t0 > t1 && tmp1->GetValue() == 1)
                t = t1;
            else
                t = max(t0, t1);
            break;
        case INV:
            t = cells[cell]->GetInput(0)->GetPrecceding().second->GetOutputTransitionTime();
            break;
    }
    table = cells[cell]->GetValue() == 1 ? "rise_transition" : "fall_transition";
    cells[cell]->SetInputTransitionTime(t);
    cells[cell]->SetOutputTransitionTime(LookUp(cell, table));
    cout << cell << " v " << cells[cell]->GetValue() << " " << table << " " << t << endl;
    cout << "outputTransitionTime of " << cell << ": " << cells[cell]->GetOutputTransitionTime() << endl;
}

struct cmpInDegree{
    bool operator()(Cell*& a, Cell*& b) const{
        return a->GetInDegree() > b->GetInDegree();
    }
};

void TimingAnalyzer::CalDelay(vector<int> pattern) {
    vector<Cell*> t;
    map<string, int> backup;
    bitset<1> tmp;
    Cell* cur = NULL;
    //string table = cells[cell]->GetValue() == 1 ? "rise_transition" : "fall_transition";

    cout << "----START CAL DELAY----" << endl;

    for (int i = 0; i < pattern.size(); ++i) {
        Cell* pi = new Cell(inputSeq[i], PI, pattern[i]);
        pi->SetOutputTransitionTime(0);
        nets[inputSeq[i]]->AddPrecceding(pair<string, Cell*>(inputSeq[i], pi));
    }

    for (auto c : cells) {
        t.push_back(c.second);
        backup.insert({c.second->GetName(), c.second->GetInDegree()});
    }

    while (!t.empty()) {

        make_heap(t.begin(), t.end(), cmpInDegree());
        cur = t.front();
        pop_heap(t.begin(), t.end());
        t.pop_back();

        //cout << cur->GetName() << endl;
        switch (cur->GetType()) {
            case NAND:
                tmp = (cur->GetInput(0)->GetPrecceding().second->GetValue() & 
                    cur->GetInput(1)->GetPrecceding().second->GetValue()).flip();
                //CalTransition(cur->GetName());
                break;
            case NOR:
                tmp = (cur->GetInput(0)->GetPrecceding().second->GetValue() | 
                    cur->GetInput(1)->GetPrecceding().second->GetValue()).flip();
                //CalTransition(cur->GetName());
                break;
            case INV:
                tmp = (cur->GetInput(0)->GetPrecceding().second->GetValue()).flip();
                //CalTransition(cur->GetName());
                break;
        }
        /*
         *if (cur->GetName() == "g1")
         *    break;
         */
        cur->SetValue(tmp);
        CalTransition(cur->GetName());
        //cout << cur->GetName() << " " << cur->GetValue() << endl;
        string table = (cur->GetValue() == 1) ? "rise_transition" : "fall_transition";
        //cout << cur->GetName() << " " << table << endl;

        for (auto i : cur->GetOutput()->GetSucceding())
            i.second->DecrInDegree();
    }
    for (auto c : cells)
        c.second->SetInDegree(backup[c.second->GetName()]);
    cout << endl;
}
