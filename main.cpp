#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

void fn(std::string& s)
{
    int openBrackets = 0;
    std::vector<int> openBracketsPos;
    std::unordered_set<int> contaminatedSequences;
    std::unordered_set<int> toRemove;

    for (int i = 0; i < s.size(); i++)
    {
        auto& ch = s[i];
        if (ch == '(') // start of bracket sequence
        {
            openBrackets++;
            openBracketsPos.push_back(i);
        }
        else if (openBrackets > 0 && ch != ')')
        {// state -> sequence started, encountered non closing symbol
            contaminatedSequences.insert(openBracketsPos.back());
        }
        else if(openBrackets > 0) /// sequence closing, ch == ')'
        {
            auto it = contaminatedSequences.find(openBracketsPos.back());
            if (it == contaminatedSequences.end()) /// empty brackets
            {
                toRemove.insert(i);
                toRemove.insert(openBracketsPos.back());
            }
            openBrackets--;
            openBracketsPos.pop_back(); /// close bracket sequence
        }
    }

    int slow = 0; // builds resulting str
    for (int i = 0; i < s.size(); i++)
    {
        if (toRemove.find(i) == toRemove.end())
        {
            s[slow] = s[i];
            slow++;
        }
    }
    s.erase(slow, s.size() - slow);
}

int main() {
    std::unordered_map<std::string, std::string> testcases = {{"ab()c", "abc"},
                                                              {"ab(()a)", "ab(a)"},
                                                              {"(((())))", {""}},
                                                              {"( )", "( )"},
                                                              {"()()", ""},
                                                              {"ab)()(()", "ab)("},
                                                              {"(a()b)", "(ab)"},
                                                              {"()ab ((", "ab (("},
                                                              {")))(((", ")))((("},
                                                              {"(a(b(c(d(e)))))", "(a(b(c(d(e)))))"}};

    for (auto& [input, expectedOutput] : testcases)
    {
        std::string nonConst = input;
        if (fn(nonConst); nonConst != expectedOutput)
        {
            std::cout << "FAILED: " << "Expected: " << expectedOutput << "; Actual: " << nonConst << std::endl;
        } else
        {
            std::cout << "PASSED: " << input << " -> " << expectedOutput << std::endl;
        }
    }
    return 0;
}
