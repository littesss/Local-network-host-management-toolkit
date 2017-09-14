#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

class myline : public string {};

istream& operator>>(istream& is, myline& line)
{
    getline(is, line);
    return is;
}

int main()
{
    ifstream fin("/etc/exports");

    istream_iterator<myline> begin(fin);
    istream_iterator<myline> end;

    vector<string> content;

    copy(begin, end, back_inserter(content));

    cout << "content" <<endl;

    copy(content.begin(), content.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}
