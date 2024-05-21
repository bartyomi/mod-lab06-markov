#include "textgen.h"
#include <fstream>
#include <vector>
#include <map>

using namespace std;

string Generator::GenerateText (string text, int countPrefix, int maxLength) {

    string result;
    map<prefix, suffix> table = GenerateTable(countPrefix, text);
    prefix pref = table.begin()->first;
    srand(time(nullptr));
    vector<string> words;
    words = Split(result, " ");


    while (words.size() + countPrefix <= maxLength) {

        if (table.find(pref) == table.end()) {
            break;
        }

        suffix suf = table[pref];
        int id = rand() % suf.size();
        result += suf[id] + " ";

        pref.pop_front();
        pref.push_back(suf[id]);

        words = Split(result, " ");
    }

    return result;
}

map<prefix, suffix> Generator::GenerateTable (int countPrefix, string text) {

    map<prefix, suffix> table = map<prefix, suffix>();
    prefix pref = prefix();
    vector<string> words = Split(text, " ");

    for (int i = 0; i < countPrefix; i++) {
        pref.push_back(words[i]);
    }

    for (int i = countPrefix; i < words.size(); i++) {

        if (table.find(pref) == table.end()) {
            suffix suf = suffix();
            suf.push_back(words[i]);
            table[pref] = suf;
        }
        else {
            table[pref].push_back(words[i]);
        }

        pref.pop_front();
        pref.push_back(words[i]);
    }

    return table;
}

vector<string> Split(string text, string separator) {
    int startPos = 0, endPos;
    string core;
    vector<string> result;

    while ((endPos = text.find(" ", startPos)) != text.length()) {

        core = text.substr(startPos, endPos - startPos);
        startPos = endPos + separator.length();

        if (core != " " && core != "") result.push_back(core);
    }

    if (text.substr(startPos) != "") result.push_back(text.substr(startPos));

    return result;
}

string ReadFile(string path) {

    string result = "";

    ifstream file(path);

    if (file.is_open()) {

        string line;

        while (getline(file, line)) result += line;

    }

    file.close();

    return result;
}