#include "header.h"
#include <string>
#include <fstream>
#include <streambuf>

int main(int argc, char* argv[]) {

    ifstream t(argv[1]);
    string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    regex r("(?:\\/\\/(?:\\\\\\n|[^\\n])*\\n)|(?:\\/\\*[\\s\\S]*?\\*\\/)|((?:R\"([^(\\\\\\s]{0,16})\\([^)]*\\)\\2\")|(?:@\"[^\"]*?\")|(?:\"(?:\\?\\?'|\\\\\\\\|\\\\\"|\\\\\\n|[^\"])*?\")|(?:'(?:\\\\\\\\|\\\\'|\\\\\\n|[^'])*?'))");

    str = regex_replace(str, r, "");

    cout << str << endl;

}
