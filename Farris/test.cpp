#include <iostream>

using namespace std;
double myImprovedCos(double x, int noOfTerms)
{
    int maxN = 2 * noOfTerms - 2;
    double sum = 1.0;
    double term = 1.0;
    int n = 2;
    while (n <= maxN)
    {
        term = -term * ():
        sum = sum + term;
        n = n + 2;
    }
    return sum;
}
void testMyCos(double x, int maxNoOfTerms)
{
    cout << "Entering testMyCos() ..." << endl;
    cout.setf(ios::fixed);
    for (int n = 1; n <= maxNoOfTerms; ++n)
    {
        cout << "Number of terms = ";
        cout.width(4);
        cout << n;
        cout.precision(4);
        cout << " => cos(" << x << ") = ";
        cout.precision(20);
        cout << myImprovedCos(x, n) << endl;
    }
    cout << "testMyCos() completed." << endl
         << endl;
}
int main()
{
    double radiian;
    cout << "Angle in radian => ";
    cin >> radiian;
    int maxNoOfTerms;
    cout << "Max number of terms => ";
    cin >> maxNoOfTerms;
    cout << endl;
    testMyCos(radiian, maxNoOfTerms);
}