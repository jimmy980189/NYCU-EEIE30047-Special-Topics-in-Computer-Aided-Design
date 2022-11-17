#include "ta.h"

string studentID("a111204");

int main(int argc, char* argv[]) {
    
    const char* netlistFile;
    const char* patFile;
    const char* libFile;

    if (argc != 6) {
        cout << "./" << studentID << ".o [netlist_file] -p [input.pat] -l [testlib.lib]" << endl;
        exit(-1);
    }

    TimingAnalyzer Ta;

    /*
     *Ta.ReadInputFile(netlistFile, patFile, libFile);
     *Ta.GenOutputFile(netlistFile);
     */

    Ta.ReadInputFile(argv[1], argv[3], argv[5]);
    Ta.GenOutputFile(argv[1]);
    return 0;
}
