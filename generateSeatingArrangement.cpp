#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent a diplomat
struct Diplomat {
    std::string name;
    std::vector<std::string> friends;
    std::vector<std::string> foes;
    bool indifferent;
};

// Function to check if two diplomats are foes
bool areFoes(const Diplomat& diplomat1, const Diplomat& diplomat2) {
    for (const std::string& foe : diplomat1.foes) {
        if (foe == diplomat2.name) {
            return true;
        }
    }
    return false;
}

// Function to check if a diplomat has at least one friend
bool hasFriend(const Diplomat& diplomat) {
    return !diplomat.friends.empty();
}

// Function to check if a diplomat can be seated next to another diplomat based on the conditions
bool isValidSeating(const Diplomat& diplomat, const Diplomat& neighbor) {
    if (areFoes(diplomat, neighbor) && !hasFriend(diplomat)) {
        return false;
    }
    return true;
}

// Function to generate a seating arrangement
std::vector<std::string> generateSeatingArrangement(const std::vector<Diplomat>& diplomats) {
    std::vector<std::string> seatingArrangement;
    std::vector<Diplomat> tempDiplomats = diplomats;  // Create a temporary copy to modify

    // Sort diplomats in alphabetical order
    std::sort(tempDiplomats.begin(), tempDiplomats.end(),
              [](const Diplomat& d1, const Diplomat& d2) { return d1.name < d2.name; });

    // Find a valid seating arrangement
    for (const Diplomat& diplomat : tempDiplomats) {
        if (seatingArrangement.empty()) {
            seatingArrangement.push_back(diplomat.name);
        } else {
            bool isValidNeighbor = false;
            for (const std::string& neighbor : seatingArrangement) {
                const Diplomat& neighborDiplomat = tempDiplomats[neighbor];
                if (isValidSeating(diplomat, neighborDiplomat)) {
                    isValidNeighbor = true;
                    break;
                }
            }
            if (isValidNeighbor) {
                seatingArrangement.push_back(diplomat.name);
            } else {
                return {};  // No valid seating arrangement possible
            }
        }
    }

    return seatingArrangement;
}

int main() {
    // Read input and create diplomats
    std::vector<Diplomat> diplomats;
    std::string line;

    while (std::getline(std::cin, line)) {
        Diplomat diplomat;
        std::string name;
        std::string temp;

        std::istringstream iss(line);
        while (iss >> temp) {
            if (isalpha(temp[0])) {
                name += temp[0];
                for (size_t i = 1; i < temp.size(); ++i) {
                    name += tolower(temp[i]);
                }
            } else {
                if (temp == "1") {
                    diplomat.friends.push_back(name);
                } else if (temp == "0") {
                    diplomat.foes.push_back(name);
                }
            }
        }

        if (!name.empty()) {
            diplomat.name = name;
            diplomat.indifferent = (diplomat.friends.empty() && diplomat.foes.empty());
            diplomats.push_back(diplomat);
        }
    }

    // Generate seating arrangement
    std::vector<std::string> seatingArrangement = generateSeatingArrangement(diplomats);

    // Display the names of all diplomats
    std::cout << "Diplomats: ";
    for (const Diplomat& diplomat : diplomats) {
        std::cout << diplomat.name << ", ";
    }
    std::cout << std::endl;

    // Display the seating arrangement, if possible
    if (!seatingArrangement.empty()) {
        std::cout << "Seating Arrangement: ";
        for (const std::string& diplomat : seatingArrangement) {
            std::cout << diplomat << ", ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No valid seating arrangement possible." << std::endl;
    }

    return 0;
}
