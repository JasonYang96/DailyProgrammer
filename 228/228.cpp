//  https://www.reddit.com/r/dailyprogrammer/comments/3h9pde/20150817_challenge_228_easy_letters_in/
//  228.cpp
//
//  Created by Jason Yang on 8/17/15.
//  Copyright (c) 2015 Jason Yang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BOTH_ORDER = " IN ORDER AND REVERSE ORDER\n";
string REVERSE_ORDER = " REVERSE ORDER\n";
string IN_ORDER = " IN ORDER\n";
string NOT_IN_ORDER = " NOT IN ORDER\n";

void order(string word) {
    bool inOrder = true;
    bool reverseOrder = true;
    for (int i = 0; (i < word.length() - 1) && (inOrder || reverseOrder); i++) {
        if (word[i] < word[i+1] && reverseOrder)
            reverseOrder = false;
        if (word[i] > word[i+1] && inOrder)
            inOrder = false;
    }
    
    if (reverseOrder && inOrder)
        cout << word + BOTH_ORDER;
    else if (reverseOrder)
        cout << word + REVERSE_ORDER;
    else if (inOrder)
        cout << word + IN_ORDER;
    else
        cout << word + NOT_IN_ORDER;
}

int main(int argc, const char * argv[]) {
    vector<string> input;
    string line;
    
    while (getline(cin, line)) {
        input.push_back(line);
    }
    
    for_each(input.begin(), input.end(), order);
    
    
    return 0;
}
