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

    string line;
    //regex replace_regex("(\\/\\/.*)|(\\/\\*[^*\\/]*\\*\\/)|(^\\s+)");
    regex replace_regex("(\\/\\/.*)|(\\/\\*((?!\\*\\/).)*\\*\\/)|(^\\s+)");
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
        line = regex_replace(line, space_regex, " ");
        Cell* c;
        cellType type;

        if (line.size()) {
            if (regex_search(line, firstWord, pin_regex)) {

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
                    if (type == OUT)
                        POlist.push_back(name);
                }
            }
            else {

                if (comment && !regex_search(line, firstWord, closeComment_regex)) { 
                    continue; 
                }

                if (regex_search(line, firstWord, openComment_regex)) {
                    comment = true;
                }
                else if (regex_search(line, firstWord, closeComment_regex)) {
                    comment = false;
                    continue;
                }

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
                }
            }
        }
    }

    fNetlist.close();
}

void TimingAnalyzer::ReadPat(const char* patFile) {
    ifstream fPat(patFile);
    if (fPat.fail()) {
        cout << "Failed to open file: " << patFile << endl;
        exit(-1);
    }

    string line;
    regex word_regex("\\w+");
    int cnt = 0;

    while(getline(fPat, line)) {

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
            if (cnt == 0)
                inputSeq.push_back(tmp);
            else if (cnt > 0 && (*i).str() != "end")
                patterns[cnt - 1].push_back(stoi(tmp));
        }
        ++cnt;
    }
    patterns.pop_back();

    fPat.close();
}

void TimingAnalyzer::ReadLib(const char* libFile) {
    ifstream fLib(libFile);
    if (fLib.fail())  {
        cout << "Failed to open file: " << libFile << endl;
        exit(-1);
    }

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

            auto words_begin = sregex_iterator(line.begin(), line.end(), find_regex);
            for (sregex_iterator i = words_begin; i != sregex_iterator(); ++i) {

                string word = (*i).str();
                if (cnt < 7) {
                    index_1.push_back(stod(word));
                }
                else if (cnt < 14) {
                    index_2.push_back(stod(word));
                }
                else if (cnt > 13 && (regex_search(word, s, word_regex))) {

                    int l = s.str().size();
                    if (s.str() == "cell") {
                        int last = word.find_last_of(")");
                        cell = word.substr(l + 1, last - l - 1);
                        lib = new Lib(cell);
                        libs.insert({cell, lib});
                    }
                    else if (s.str() == "pin") {
                        int last = word.find_last_of(")");
                        pin = word.substr(l + 1, last - l - 1);
                    }
                    else if (s.str() == "capacitance") {
                        tmp = stod(word.substr(l + 1));
                        libs[cell]->AddCapacitance(pair<string, double>(pin, tmp));
                    }
                    else if (s.str() == "0") {
                        libs[cell]->AddTable(tableName[tableCnt], stod(word));
                        if (vCnt++ % 49 == 48)
                            tableCnt = (tableCnt + 1) % 6;
                    }
                }
                ++cnt;
            }
        }
    }

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

    GenOutputLoad(caseName);
    GenOutputDelayAndPath(caseName);
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
    return (a->GetPropagationDelay() != b->GetPropagationDelay()) ?
        a->GetPropagationDelay() > b->GetPropagationDelay() : a->GetInstanceNum() < b->GetInstanceNum();
}

void TimingAnalyzer::GenOutputDelayAndPath(string caseName) {
    string filenameDelay = studentID + "_" + caseName + "_delay.txt";
    string filenamePath = studentID + "_" + caseName + "_path.txt";

    ofstream fDelay(filenameDelay);
    ofstream fPath(filenamePath);

    if (fDelay.fail()) {
        cout << "Failed to open file: " << filenameDelay << endl;
        exit(-1);
    }
    if (fPath.fail()) {
        cout << "Failed to open file: " << filenamePath << endl;
        exit(-1);
    }

    for (size_t i = 0; i < patterns.size(); ++i) {
        CalDelay(patterns[i]);
        GenOutputDelay_t(fDelay);
        GenOutputPath_t(fPath);
    }

    fDelay.close();
    fPath.close();
}

void TimingAnalyzer::GenOutputDelay_t(ofstream& fDelay) {
    vector<Cell*> sorted;

    for (auto c : cells)
        sorted.push_back(c.second);

    sort(sorted.begin(), sorted.end(), cmpDelay);

    for (auto c : sorted) {
        fDelay << c->GetName() << " " << c->GetValue() << " ";
        fDelay << c->GetPropagationDelay() << " " << c->GetOutputTransitionTime() << endl;
    }
    fDelay << endl;
}

void TimingAnalyzer::GenOutputPath_t(ofstream& fPath) {
    double delay;
    pair<double, list<string>> path;
    int cnt = 0;

    path = FindLongestDelay();
    fPath << "Longest delay = " << path.first << ", the path is: ";
    cnt = 0;
    for (auto i : path.second)
        if (cnt++ == 0)
            fPath << i;
        else
            fPath << " -> " << i;
    fPath << endl;

    path = FindShortestDelay();
    fPath << "Shortest delay = " << path.first << ", the path is: ";
    cnt = 0;
    for (auto i : path.second)
        if (cnt++ == 0)
            fPath << i;
        else
            fPath << " -> " << i;
    fPath << endl;

    fPath << endl;
}

void TimingAnalyzer::CalOutputLoading() {
    for (auto i : cells) {
        Net* tmp = i.second->GetOutput();
        double sum = i.second->GetOutputLoading();
        string gate;

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
                default:
                    break;
            }
            sum += libs[gate]->GetCapacitance(j.first);
        }
        cells[i.second->GetName()]->SetOutputLoading(sum);
    }
}

double TimingAnalyzer::LookUp(string cell, string tableName) {
    double inputTransitionTime = cells[cell]->GetInputTransitionTime();
    double outputLoading = cells[cell]->GetOutputLoading();
    pair<double, double> c;
    pair<double, double> s;
    string gate;

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
        default:
            break;
    }

    long unsigned int i, j;
    for (i = 0; i < index_1.size(); ++i)
        if (outputLoading < index_1[i])
            break;

    for (j = 0; j < index_2.size(); ++j)
        if (inputTransitionTime < index_2[j])
            break;

    //if input transition time or output loading exceeded range of index_1 / index_2
    if (i == 0) ++i;
    if (j == 0) ++j;
    if (i == 7) --i;
    if (j == 7) --j;

    s.first = index_2[j - 1];
    s.second = index_2[j];
    c.first = index_1[i - 1];
    c.second = index_1[i];

    vector<double> p = libs[gate]->GetP(tableName, i - 1, j - 1);

    return Interpolation(outputLoading, inputTransitionTime, s, c, p);
}

double TimingAnalyzer::Interpolation(double cReq, double sReq, pair<double, double> s, pair<double, double> c, vector<double> p) {
    double A = p[0] + ((p[2] - p[0]) / (s.second - s.first)) * (sReq - s.first);
    double B = p[3] + ((p[1] - p[3]) / (s.second - s.first)) * (sReq - s.first);

    return (double) A + ((B - A) / (c.second - c.first)) * (cReq - c.first);
}

struct cmpInDegree{
    bool operator()(Cell*& a, Cell*& b) const{
        return a->GetInDegree() > b->GetInDegree();
    }
};

void TimingAnalyzer::CalDelay(vector<int> pattern) {
    vector<Cell*> heap;
    map<string, int> backup;
    bitset<1> outputValue;
    Cell* cur = NULL;
    Cell* pre0 = NULL;
    Cell* pre1 = NULL;
    double t, t0, t1;

    for (size_t i = 0; i < pattern.size(); ++i) {
        Cell* pi = new Cell(inputSeq[i], PI, pattern[i]);
        pi->SetOutputTransitionTime(0);
        nets[inputSeq[i]]->AddPrecceding(pair<string, Cell*>(inputSeq[i], pi));

        garbage.push_back(pi);
    }

    for (auto c : cells) {
        heap.push_back(c.second);
        backup.insert({c.second->GetName(), c.second->GetInDegree()});
        c.second->SetPathDelay(0);
    }

    while (!heap.empty()) {

        make_heap(heap.begin(), heap.end(), cmpInDegree());
        cur = heap.front();
        pop_heap(heap.begin(), heap.end());
        heap.pop_back();

        string table;
        double delay = 0;
        string cell = cur->GetName();

        switch (cur->GetType()) {
            case NAND:
                outputValue = (cur->GetInput(0)->GetPrecceding().second->GetValue() & 
                    cur->GetInput(1)->GetPrecceding().second->GetValue()).flip();
                cur->SetValue(outputValue);

                pre0 = cells[cell]->GetInput(0)->GetPrecceding().second;
                pre1 = cells[cell]->GetInput(1)->GetPrecceding().second;
                t0 = pre0->GetPathDelay() + pre0->GetPropagationDelay();
                t1 = pre1->GetPathDelay() + pre1->GetPropagationDelay();
                if (t0 < t1 && pre0->GetValue() == 0) {
                    t = pre0->GetOutputTransitionTime();
                    delay = pre0->GetPathDelay() + pre0->GetPropagationDelay();
                }
                else if (t0 > t1 && pre1->GetValue() == 0) {
                    t = pre1->GetOutputTransitionTime();
                    delay = pre1->GetPathDelay() + pre1->GetPropagationDelay();
                }
                else {
                    t = t0 > t1 ? pre0->GetOutputTransitionTime() : pre1->GetOutputTransitionTime();
                    delay = max(t0, t1);
                }
                break;
            case NOR:
                outputValue = (cur->GetInput(0)->GetPrecceding().second->GetValue() | 
                    cur->GetInput(1)->GetPrecceding().second->GetValue()).flip();
                cur->SetValue(outputValue);

                pre0 = cells[cell]->GetInput(0)->GetPrecceding().second;
                pre1 = cells[cell]->GetInput(1)->GetPrecceding().second;
                t0 = pre0->GetPathDelay() + pre0->GetPropagationDelay();
                t1 = pre1->GetPathDelay() + pre1->GetPropagationDelay();
                if (t0 < t1 && pre0->GetValue() == 1) {
                    t = pre0->GetOutputTransitionTime();
                    delay = t0;
                }
                else if (t0 > t1 && pre1->GetValue() == 1) { 
                    t = pre1->GetOutputTransitionTime(); 
                    delay = t1;
                }
                else {
                    t = t0 > t1 ? pre0->GetOutputTransitionTime() : pre1->GetOutputTransitionTime();
                    delay = max(t0, t1);
                }
                break;
            case INV:
                outputValue = (cur->GetInput(0)->GetPrecceding().second->GetValue()).flip();
                cur->SetValue(outputValue);

                pre0 = cells[cell]->GetInput(0)->GetPrecceding().second;
                t = pre0->GetOutputTransitionTime();
                delay = pre0->GetPathDelay() + pre0->GetPropagationDelay();
                break;
            default:
                break;
        }
        cells[cell]->SetInputTransitionTime(t);

        table = cells[cell]->GetValue() == 1 ? "rise_transition" : "fall_transition";
        cells[cell]->SetOutputTransitionTime(LookUp(cell, table));

        table = cells[cell]->GetValue() == 1 ? "cell_rise" : "cell_fall";
        double propagationDelay = LookUp(cell, table);
        cells[cell]->SetPropagationDelay(propagationDelay);

        cells[cell]->SetPathDelay(delay);
        cells[cell]->SetLongestDelay(delay + propagationDelay);

        for (auto i : cur->GetOutput()->GetSucceding())
            i.second->DecrInDegree();
    }

    for (auto c : cells)
        c.second->SetInDegree(backup[c.second->GetName()]);
}

pair<double, list<string>> TimingAnalyzer::FindLongestDelay() {
    list<string> seq;
    Net* cur = NULL;
    string net;
    string maxCell;
    double maxDelay = 0;

    //Find PO to backtrack
    for (auto net : POlist) {
        Cell* tmp = nets[net]->GetPrecceding().second;
        if (tmp->GetLongestDelay() > maxDelay) {
            maxDelay = tmp->GetLongestDelay();
            maxCell = tmp->GetName();
        }
    }
    net = cells[maxCell]->GetOutput()->GetName();
    seq.push_front(net);
    cur = nets[net];

    while (cur->GetType() != IN) {
        for (auto i : cur->GetPrecceding().second->GetAllInput()) {
            if (i->GetPrecceding().second->GetLongestDelay() == cur->GetPrecceding().second->GetPathDelay()) {
                seq.push_front(i->GetName());
                cur = i;
                break;
            }
        }
    }

    return {maxDelay, seq};
}

pair<double, list<string>> TimingAnalyzer::FindShortestDelay() {
    list<string> seq;
    Net* cur = NULL;
    string net;
    string minCell;
    double minDelay = INT_MAX;

    //Find PO to backtrack
    for (auto net : POlist) {
        Cell* tmp = nets[net]->GetPrecceding().second;
        if (tmp->GetLongestDelay() < minDelay) {
            minDelay = tmp->GetLongestDelay();
            minCell = tmp->GetName();
        }
    }
    net = cells[minCell]->GetOutput()->GetName();
    seq.push_front(net);
    cur = nets[net];

    while (cur->GetType() != IN) {
        for (auto i : cur->GetPrecceding().second->GetAllInput()) {
            if (i->GetPrecceding().second->GetLongestDelay() == cur->GetPrecceding().second->GetPathDelay()) {
                seq.push_front(i->GetName());
                cur = i;
                break;
            }
        }
    }

    return {minDelay, seq};
}
