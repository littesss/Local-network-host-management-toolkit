#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{

    ifstream fin("/etc/exports");
    vector<string> content;

    istream_iterator<string> begin(fin);
    istream_iterator<string> end;

    copy(begin, end, back_inserter(content));

    cout << "content" << endl;

    copy(content.begin(), content.end(),

            ostream_iterator<string>(cout, "\n"));

    return 0;
}
