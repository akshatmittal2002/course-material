#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int x=0;
    /// Start Redirection of cin and cout.

    std::ifstream input("input.txt"); ///Take input from the file "input.txt".
    std::streambuf *cinbuf = std::cin.rdbuf(); ///Save old buffer.
    std::cin.rdbuf(input.rdbuf()); ///Redirect cin to input.txt.

    std::ofstream output("output.txt"); ///Prints output to the file "output.txt".
    std::streambuf *coutbuf = std::cout.rdbuf(); ///Save old buffer.
    std::cout.rdbuf(output.rdbuf()); ///Redirect cout to output.txt.

    ///Inside this block, all cin and cout operations will be redirected to the files.
    cout<<"INSIDE THE FILE!"<<endl;
    cin>>x;
    cout<<"READ "<<x<<" FROM THE FILE"<<endl;

    std::cin.rdbuf(cinbuf); ///Reset to standard input again.
    std::cout.rdbuf(coutbuf); ///Reset to standard output again.

    ///Now everything is set back to normal and input and output will be on screen.

    cout<<"OUTSIDE THE FILE NOW!"<<endl;
    cout<<"ENTER A NUMBER: ";
    cin>>x;
    cout<<"YOU ENTERED: "<<x<<endl;

    return 0;
}
