/*************************************************************************
	> File Name: utcopyalgorithm.cpp
	> Created Time: Sun 27 Aug 2017 20:36:10 PDT
 ************************************************************************/
#include <iostream>
using namespace std;

#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

int main()
{
    ifstream fin("/etc/exports");
    vector<string> content;
    
    istream_iterator<string>  begin(fin);
    istream_iterator<string>  end;

    copy(begin, end, back_inserter(content));
    cout << "============centent============" << endl;
    copy(content.begin(), content.end(), ostream_iterator<string>(cout,"\n"));

    return 0;
}
