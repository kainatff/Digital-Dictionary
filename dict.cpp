#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

#define tablesize 100

class WordNode {
    string name;
    string meaning;
    string sentence;
public:
    WordNode() {
        name = ""; meaning = ""; sentence = "";
    }
    void setdetails(string a, string b, string c) {
        name = a; meaning = b; sentence = c;
    }
    void printdetails() {
        cout << "******************************************************************************************************************************************" << endl;
        cout << "WORD: " << name << "\nMEANING: " << meaning << "\nSENTENCE: " << sentence << endl;
    }
    void wordoftheday() {
        cout << "********************************************************************************************************************************************" << endl;
        cout << "WORD OF THE DAY" << endl;
        cout << "********************************************************************************************************************************************" << endl;
        cout << "WORD: " << name << "\nMEANING: " << meaning << "\nSENTENCE: " << sentence << endl;
    }
    bool isempty() {
        if (name == "\0") {
            return true;
        }
        return false;
    }
    string getname() {
        return name;
    }
    string getmean() {
        return meaning;
    }
    string getsent() {
        return sentence;
    }
    char firstletter() {
        return name[0];
    }
};
unsigned int hashFunction(const string& word) {
    //hash function for strings using word name
    unsigned int hashValue = 0;
    for (char c : word) {
        hashValue = (hashValue * 31 + static_cast<unsigned int>(c)) % tablesize;
    }
    return hashValue;
}
class HashTable {
    WordNode** table;
public:
    HashTable() {
        table = new WordNode * [tablesize]();
        //initilizing table to null values
    }
    // Destructor
    ~HashTable() {
        for (int i = 0; i < tablesize; ++i) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
    }

    void InsertNewWord(string a, string b, string c) {
        unsigned int index = hashFunction(a);
        // If the index is empty (nullptr), allocate a new WordNode
        if (table[index] == nullptr || table[index]->isempty()) {
            table[index] = new WordNode();
        }
        else {
            // Handle collision using linear probing
            unsigned int nextIndex = (index + 1) % tablesize;
            // Keep probing until an empty slot is found
            while (table[nextIndex] != nullptr && !table[nextIndex]->isempty()) {
                nextIndex = (nextIndex + 1) % tablesize;
            }
            // Allocate a new WordNode at the next available slot
            table[nextIndex] = new WordNode();
            index = nextIndex;  // Update index to the next available slot
        }
        table[index]->setdetails(a, b, c);
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Word Successfully Added To The Dictionary." << endl;
    }
    void InsertWord(string a, string b, string c) {
        unsigned int index = hashFunction(a);
        // If the index is empty (nullptr), allocate a new WordNode
        if (table[index] == nullptr || table[index]->isempty()) {
            table[index] = new WordNode();
        }
        else {
            // Handle collision using linear probing
            unsigned int nextIndex = (index + 1) % tablesize;
            // Keep probing until an empty slot is found
            while (table[nextIndex] != nullptr && !table[nextIndex]->isempty()) {
                nextIndex = (nextIndex + 1) % tablesize;
            }
            // Allocate a new WordNode at the next available slot
            table[nextIndex] = new WordNode();
            index = nextIndex;  // Update index to the next available slot
        }
        table[index]->setdetails(a, b, c);
    }
    void UpdateWord(string a, string b, string c) {
        unsigned int index = hashFunction(a);
        while (table[index] != nullptr && !table[index]->isempty()) {
            if (table[index]->getname() == a) {
                table[index]->setdetails(a, b, c);
                cout << "********************************************************************************************************************************************" << endl;
                cout << "Word Successfully Updated in the Dictionary." << endl;
                return;
            }
            index = (index + 1) % tablesize;
        }
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Error: Required Word Does Not Exist in the Dictionary." << endl;
    }

    int SearchWord(string a) {
        unsigned int index = hashFunction(a);
        while (table[index] != nullptr && !table[index]->isempty()) {
            if (table[index]->getname() == a) {
                cout << "********************************************************************************************************************************************" << endl;
                cout << "The word you searched for is: " << endl;
                table[index]->printdetails();
                return 1;
            }
            index = (index + 1) % tablesize;
        }
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Error: Required Word Does Not Exist in the Dictionary." << endl;
        return 0;
    }
    void DisplayWords() {
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Displaying All Words From The Dictionary" << endl;
        for (int i = 0; i < tablesize; i++) {
            if (table[i] != nullptr) {
                table[i]->printdetails();
            }
        }
    }
    void DeleteWord(string a) {
        unsigned int index = hashFunction(a);
        while (table[index] != nullptr && !table[index]->isempty()) {
            if (table[index]->getname() == a) {
                table[index]->setdetails("", "", "");
                table[index] = nullptr;
                cout << "********************************************************************************************************************************************" << endl;
                cout << "Word Successfully Deleted From Dictionary." << endl;
                return;
            }
            index = (index + 1) % tablesize;
        }
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Error: Required Word Does Not Exist In The Dictionary." << endl;
    }
    void DisplayWordOfDay() {
        int maxAttempts = tablesize;
        int attemptCount = 0;
        while (attemptCount < maxAttempts) {
            unsigned int index = rand() % tablesize;
            if (table[index] != nullptr && !table[index]->isempty()) {
                table[index]->wordoftheday();
                return;
            }
            attemptCount++;
        }
        cout << "********************************************************************************************************************************************" << endl;
        cout << "Error: Insufficient Words Exist To Find A Valid Word Of The Day." << endl;
    }
    void DisplaySingleAlphabet(char a) {
        cout << 
"********************************************************************************************************************************************" << endl;
        cout << "Displaying Words Starting With Alphabet '" << a << "'" << endl;
        int count = 0;
        for (int i = 0; i < tablesize; i++) {
            if (table[i] != nullptr && table[i]->firstletter() == a) {
                table[i]->printdetails();
                count++;
            }
        }
        if (count == 0) {
            cout << "Error: No Words Of Entered Alphabet Exist In Dictionary." << endl;
        }
    }
    WordNode** GetTable() const {
        return table;
    }
    
void inputWords(unordered_set<string>& wordList, HashTable* D1) {
    WordNode** table = D1->GetTable(); // Get the table from the HashTable

    for (int i = 0; i < tablesize; i++) {
        if (table[i] != nullptr && !table[i]->isempty()) {
            wordList.insert(table[i]->getname());

        }
    }
}

};

void SortAlphabetically(WordNode** table) {
    WordNode* Sorted = new WordNode[tablesize];
    int count = 0;
    cout << "********************************************************************************************************************************************" << endl;
    cout << "After Arranging in Alphabetical Order:" << endl;
    // Copy data to the Sorted array
    for (int index = 0; index < tablesize; index++) {
        if (table[index] != nullptr && !table[index]->isempty()) {
            Sorted[count].setdetails(table[index]->getname(), table[index]->getmean(), table[index]->getsent());
            count++;
        }
    }
    // Bubble sort based on entire word
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (Sorted[j].getname() > Sorted[j + 1].getname()) {
                swap(Sorted[j], Sorted[j + 1]);
            }
        }
    }
    // Print the sorted array
    for (int i = 0; i < count; i++) {
        Sorted[i].printdetails();
    }
    // Release the memory
    delete[] Sorted;
}
vector<string> getSimilarWords(const string& word, const unordered_set<string>& wordList) {
    vector<string> similarWords;
    int minEditDistance = max(5, static_cast<int>(word.size()));

    for (const string& w : wordList) {
        int editDistance = 0;

        for (int i = 0; i < word.size() && i < w.size(); ++i) {
            if (word[i] != w[i]) {
                editDistance++;
            }
        }

        if (editDistance < minEditDistance) {
            minEditDistance = editDistance;
            similarWords.clear();
            similarWords.push_back(w);
        } else if (editDistance == minEditDistance) {
            similarWords.push_back(w);
        }
    }

    return similarWords;
}

bool spellCheck(const string& word, const unordered_set<string>& wordList) {
    return wordList.find(word) != wordList.end();
}
void exitFunction(void) {
    cout << "**********************************************************************************************************************************************" << endl;
    cout << "Thank you For Using Our Services! Happy Learning!" << endl;
}

// Function to print a separator line
void printSeparator() {
    std::cout << "**********************************************************************************************************************************************" << std::endl;
}

void printMenu() {
    printSeparator();
    std::cout << std::setw(40) << "LITERARY BINGO" << std::endl;
    printSeparator();
    std::cout << "Our digital dictionary works to improve your vocabulary and enrich it with fresh words." << std::endl;
    std::cout << "These words are accompanied with their meaning and a sample sentence. " << std::endl;
    printSeparator();
    std::cout << std::setw(40) << "MENU:" << std::endl;
    printSeparator();
    std::cout << "1. Insert New Words\n2. Delete Specific Word\n3. Update Existing Word\n4. Search Word Meaning\n";
    std::cout << "5. View Word Of the Day\n6. View Words For A Specific Letter\n7. View All Words\n8. Exit\n9. Spell Check With Suggestions" << std::endl;
    printSeparator();
}

void displayContinuePrompt() {
    std::cout << "Do You Want To Continue Using The Dictionary? Press 1 for Yes Or Any Other Integer for No:" << std::endl;
}

void printExitMessage() {
    printSeparator();
    std::cout << "Thank you For Using Our Services! Happy Learning!" << std::endl;
    printSeparator();
}

void printSuccessMessage(const std::string& message) {
    printSeparator();
    std::cout << message << std::endl;
    printSeparator();
}


void mainLoop(HashTable* D1) {
    int choice=0;
    do {
        printMenu();
        std::cout << "Your Choice: ";
        std::cin >> choice;
        getchar();
        system("cls"); // Use "clear" instead of "cls" for Linux/macOS

        switch (choice) {
        case 1: {
            std::string word = { '\0' }; string mean = { '\0' }; string sent = { '\0' };
            std::cout << "Enter the new word you want to insert: " << std::flush;
            std::cin >> word;
            std::cout << "Enter its meaning: " << std::flush;
            std::cin >> mean;
            std::cout << "Enter a sample sentence: " << std::flush;
            std::cin >> sent;
            D1->InsertNewWord(word, mean, sent);
            break;
        }
        case 2: {
            std::string word;
            std::cout << "Enter the word you want to delete: ";
            std::cin >> word;
            D1->DeleteWord(word);
            break;
        }case 3: {
            std::string word = { '\0' }; string mean = { '\0' }; string sent = { '\0' };
            cout << "**********************************************************************************************************************************************" << endl;
            cout << "Enter the word you want to update:" << endl<<std::flush;
           
            cin >> word;
            cout << "Enter its new meaning:" << endl << std::flush;
           
            cin >> mean;
            cout << "Enter its new sentence:" << endl << std::flush;
            
            cin >> sent;
            D1->UpdateWord(word, mean, sent);
            break;
        }
        case 4: {
                std::cout << "**********************************************************************************************************************************************" << std::endl;
                std::cout << "Enter the word you want to search meaning for:" << std::endl << std::flush;
                std::string word;
                std::cin >> word;
                unordered_set<string> wordList;
                D1->inputWords(wordList,D1);
                if (spellCheck(word, wordList)) {
                    D1->SearchWord(word);
                    break;
                }
                else {
                    vector<string> similarWords = getSimilarWords(word, wordList);
                    cout << "Did you mean: ";
                    int i=1;
                    //max words for recommendation are 10.
                    string *arr=new string[10];
                    for (const string& w : similarWords) {
                        cout <<i<< " . "<< w << " ";
                        arr[i]=w;
                        i++;
                    }
                    cout<<"\nEnter The Index Of Your Required Word Or -1 If Its Not In The List:"<<endl;
                    int c=0;
                    cin>>c;
                    if(c==-1){
                        cout<<"\nOops! Looks Like Your Searched Word Does Not Exist In Our Library Yet."<<endl;
                    }
                    else {
                        D1->SearchWord(arr[c]);
                    }
                    cout << endl;
                   break;
                }

                }
        case 5: {
            cout << "**********************************************************************************************************************************************" << endl;
            D1->DisplayWordOfDay();
            break;
        }
        case 6: {
            cout << "**********************************************************************************************************************************************" << endl;
            cout << "Enter the alphabet you want to view words of: (In UpperCase) " << endl << std::flush;
            char a;
            cin >> a;
            D1->DisplaySingleAlphabet(a);
            break;
        }
        case 7: {
            cout << "**********************************************************************************************************************************************" << endl;
            SortAlphabetically(D1->GetTable());
            break;
        }
        case 8:
            printExitMessage();
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl << std::flush;
        }

        displayContinuePrompt();
        cin >> choice;
        getchar();
        system("cls");
    } 
    while (choice == 1);
    printExitMessage();
}
void AddWordsInTable(HashTable* D1) {
    D1->InsertWord("Adjure", "Formal exertion on someone to do something.", "The doctor adjured his patient to concur for heart surgery.");
    D1->InsertWord("Badinage", "Witty conversation.", "We had badinage last night.");
    D1->InsertWord("Dogmatic ", "Thrusting one’s opinion or beliefs while reluctant to accept those of others.", "The leader seems quite dogmatic.");
    D1->InsertWord("Jink", "Sudden quick change of direction.", "The pilot jinked the plane for an emergency landing.");
    D1->InsertWord("Uncanny", "Strange or mysterious.", "The portrait’s appearance was uncanny.");
    D1->InsertWord("Dof", "A stupid person.", "The university is filled with dofs.");
    D1->InsertWord("Aggrandize", "To enhance power, wealth, or status.", "A generous grant, enabled the library to significantly aggrandize its collection of books on tape.");
    D1->InsertWord("Abnegation", "Renunciation of a belief or doctrine.", "Monks practice abnegation of the material aspects of human life.");
    D1->InsertWord("Recalcitrant", "Resistant to authority.", "For anyone who has ever struggled to extract a recalcitrant cork from a bottle … the value of a good corkscrew is a given.");
    D1->InsertWord("Travesty", "Distorting facts or imitation.", "The trial was a travesty of justice.");
    D1->InsertWord("Ubiquitous", "Omnipresent or existing everywhere.", "Apple is working to make Siri a little more ubiquitous, and to that end, is finally opening Siri up to third-party devices.");
    D1->InsertWord("Athleisure", "A fashion trend distinguished by athletic clothing that is both comfortable and alluring.", "Athleisure looks great whether you’re working out or going about your daily business.");
    D1->InsertWord("Scrutinise", "To carefully or critically study in great detail.", "When planning your next tactics, it is advisable to carefully scrutinize your opponent’s moves.");
    D1->InsertWord("Effervescent", "Bubbling with high spirits or excitement.", "Her effervescent personality brightened up the entire room.");
    D1->InsertWord("Quintessential", "Representing the most perfect or typical example of a quality or class.", "The old bookstore was the quintessential haven for bibliophiles.");
    D1->InsertWord("Ineffable", "Too great or extreme to be expressed or described in words.", "The beauty of the sunrise was ineffable.");
    D1->InsertWord("Ephemeral", "Lasting for a very short time.", "The beauty of cherry blossoms is ephemeral, blooming for just a few weeks.");
    D1->InsertWord("Serendipity", "The occurrence and development of events by chance in a happy or beneficial way.", "Their meeting was pure serendipity, leading to a lifelong friendship.");
    D1->InsertWord("Mellifluous", "Sweet or musical in sound.", "The singer's mellifluous voice captivated the audience.");
    D1->InsertWord("Peregrinate", "To travel or wander around from place to place.", "In the summer, they love to peregrinate through picturesque landscapes.");
    D1->InsertWord("Halcyon", "Denoting a period of time in the past that was idyllically happy and peaceful.", "The memories of their halcyon days lingered in their hearts.");
    D1->InsertWord("Effulgent", "Shining brightly; radiant.", "The garden was effulgent with the colors of blooming flowers.");
    D1->InsertWord("Supine", "Lying face upward.", "He lay supine on the grass, gazing at the clouds above.");
    D1->InsertWord("Pernicious", "Having a harmful effect, especially in a gradual or subtle way.", "The pernicious influence of gossip can damage relationships.");
    D1->InsertWord("Obfuscate", "To deliberately make something unclear or difficult to understand.", "Some politicians obfuscate the truth to manipulate public opinion.");
    D1->InsertWord("Sycophant", "A person who acts obsequiously towards someone important in order to gain advantage.", "The sycophant constantly praised the boss to secure promotions.");
    D1->InsertWord("Quixotic", "Extremely idealistic; unrealistic and impractical.", "His quixotic dreams of changing the world inspired those around him.");
    D1->InsertWord("Surreptitious", "Kept secret, especially because it would not be approved of.", "She made a surreptitious glance to check if anyone was watching.");
    D1->InsertWord("Cacophony", "A harsh, discordant mixture of sounds.", "The street was filled with the cacophony of honking horns and shouting vendors.");
    D1->InsertWord("Ephemeral", "Lasting for a very short time.", "The beauty of cherry blossoms is ephemeral, blooming for just a few weeks.");
    D1->InsertWord("Esoteric", "Intended for or likely to be understood by only a small number of people with special knowledge.", "The professor's lecture on quantum physics was esoteric for most students.");
    D1->InsertWord("Idiosyncrasy", "A mode of behavior or way of thought peculiar to an individual.", "Her idiosyncrasy was to always wear mismatched socks.");
    D1->InsertWord("Pulchritude", "Beauty, especially a woman's beauty.", "The actress was admired not only for her talent but also for her pulchritude.");
    D1->InsertWord("Sycophant", "A person who acts obsequiously towards someone important in order to gain advantage.", "The sycophant constantly praised the boss to secure promotions.");
    D1->InsertWord("Vorfreude", "The joyful, intense anticipation that comes from imagining future pleasures.", "The vorfreude before a vacation can be as delightful as the trip itself.");
    D1->InsertWord("Quagmire", "A difficult or precarious situation; a predicament.", "The political debate turned into a quagmire of conflicting opinions.");
}

int main() {
    HashTable* D1 = new HashTable();
    AddWordsInTable(D1);
    mainLoop(D1);
    return 0;
}


