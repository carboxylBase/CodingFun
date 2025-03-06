#include <bits/stdc++.h>
using namespace std;

int main()
{
    system("g++ -o build\\gen gen.cpp");
    system("g++ -o build\\prog1 main.cpp");
    system("g++ -o build\\prog2 burst.cpp");

    for (int i = 0; i < 100000000; ++i) 
    {
        system("build\\gen > input.txt");               
        system("build\\prog1 < input.txt > output\\output1.txt"); 
        system("build\\prog2 < input.txt > output\\output2.txt"); 

        ifstream out1("output\\output1.txt");
        ifstream out2("output\\output2.txt");

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
