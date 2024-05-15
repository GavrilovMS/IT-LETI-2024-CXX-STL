#include <iostream>
#include <map>
#include <string>
#include <algorithm>

int main() {
    std::map<std::string, int> map;

    map.insert(std::make_pair("key1", 1)); // существует => ничего не происходит
    map["key2"] = 2; // существует => перезаписывается

    auto it = std::find_if(map.begin(), map.end(),  [](auto it){return it.second = 1;});
    if (it != map.end()) {
        std::cout << "key for 1: " << it->first << std::endl;
    }

    it = std::find_if(map.begin(), map.end(), [](auto it){return it.first == "key2";});
    if (it != map.end()) {
        std::cout << "value for key2: " << it->second << std::endl;
    }

    // лучше
    it = map.find("key1");
    if (it != map.end()) {
        std::cout << "value for key1: " << it->second << std::endl;
    }

    return 0; 
}