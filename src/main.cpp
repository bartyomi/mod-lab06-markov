#include <iostream>
#include <vector>
#include "textgen.h"

using namespace std;

int main() {

    string text = ReadFile("data.txt");
    const int maxLength = 500;
    const int countPrefix = 2;

    string result = Generator().GenerateText(text, countPrefix, maxLength);

    cout << result;

    return 0;
}