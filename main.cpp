#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

void fn(std::string& s)
{
    std::vector<int> openBracketsPos;
    std::unordered_set<int> contaminatedSequences;

    for (int i = 0; i < s.size(); i++)
    {
        auto& ch = s[i];
        if (ch == '(') // start of bracket sequence
        {
            openBracketsPos.push_back(i);
        }
        else if (!openBracketsPos.empty() > 0 && ch != ')')
        {// state -> sequence started, encountered non closing symbol
            contaminatedSequences.insert(openBracketsPos.back());
        }
        else if(!openBracketsPos.empty()) /// sequence closing, ch == ')'
        {
            auto it = contaminatedSequences.find(openBracketsPos.back());
            if (it == contaminatedSequences.end()) /// empty brackets
            {
                s[i] = (char)0;
                s[openBracketsPos.back()] = char(0);
            }
            openBracketsPos.pop_back();
        }
    }
    auto it = std::remove(s.begin(), s.end(), (char)0);
    s.erase(it, s.end());
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
