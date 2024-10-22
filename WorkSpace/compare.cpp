#include <bits/stdc++.h>
using namespace std;

int main()
{
    system("g++ -o gen gen.cpp");
    system("g++ -o prog1 main.cpp");
    system("g++ -o prog2 burst.cpp");

    for (int i = 0; i < 1000; ++i) 
    {
        system("gen > input.txt");               
        system("prog1 < input.txt > output1.txt"); 
        system("prog2 < input.txt > output2.txt"); 

        ifstream out1("output1.txt");
        ifstream out2("output2.txt");

        string line1, line2;
        bool same = true;
        while (getline(out1, line1) && getline(out2, line2))
        {
            if (line1 != line2)
            {
                same = false;
                break;
            }
        }
        getline(out1, line1);
        getline(out2, line2);
        if (line1 != line2)
        {
            same = false;
        }
        if (!same)
        {
            cout << "Difference found!" << endl;
            return 1;
        }
        else
        {
            cout << "Test " << i + 1 << " passed." << endl;
        }
    }
    cout << "All tests passed!" << endl;
    return 0;
}
