#include <iostream>
#include <vector>
#include <map>
using namespace std;
//------------------------------------------------
 
// This program allows you to build a DFA machine and test any words on it
 
// Created and developed by :
// Andrew Ezzat Daoud - Section 2
// Sarah Raouf Shaker - Section 3
// Rana Osama Mohammed - Section 3
 
// Faculty of Computers and Information - Assiut University
 
//------------------------------------------------

class DFA_Machine{
private:
    int stateNum; // The number of states in the DFA
    int alphaNum; // The number of the alphabet characters in the DFA
    int finalNum; // The number of final states in the DFA
    string startState; // The name of the start state
    vector<string> States; // A vector to store the states in the DFA
    vector<char> Alphabet; // A vector to store the available alphabet character in the DFA
    map<string, bool> finalState;  // A map to store and check for the final states
    
    // A map to make the Transition Table :
    // The Key : Is a pair of string and char which represent the current state and the alphabet character used
    // The Value : Is a string which represent the name of the next state if the this alphabet character is used with the current state
    map<pair<string, char>, string> transitionTable;
    
public:
    bool notNumberTest(string input){
        bool found = false;
        for(int i = 0 ; i < input.size() ; i++){
            if(input[i] < '0' || input[i] > '9'){
                found = true;
                break;
            }
        }
        if(found || input == "0"){
            cout << "Invalid Input! Try again.\n";
            cout << "Please enter a number\n";
            return true;
        }
        return false;
    }
    bool invalidInputTest(string stateName){
        bool notFound = true;
        for(int i = 0 ; i < stateNum ; i++){
            if(States[i] == stateName){
                notFound = false;
                break;
            }
        }
        if(notFound){
            cout << "Invalid Input! Try again.\n";
            cout << "Please enter a state name in your DFA Machine\n";
            return true;
        }
        return false;
    }
    void setStates(){
        cout << "\nEnter the number of states :\n";
        string input;
        do{
            cin >> input;
        } while(notNumberTest(input));
        stateNum = stoi(input);
        cout << "\nEnter the names of states :\n";
        cout << "NOTE : Use one word per state name\n";
        for(int i = 1 ; i <= stateNum ; i++){
            cout << i << " => ";
            string stateName;
            cin >> stateName;
            States.push_back(stateName);
        }
    }
    void setAlphabet(){
        cout << "\nEnter the number of characters in the alphabet :\n";
        string input;
        do{
            cin >> input;
        } while(notNumberTest(input));
        alphaNum = stoi(input);
        cout << "\nEnter the characters of the alphabet :\n";
        for(int i = 1 ; i <= alphaNum ; i++){
            cout << i << " => ";
            char character;
            cin >> character;
            Alphabet.push_back(character);
        }
    }
    void setTransitionTable(){
        cout << "\nEnter the transition Table :\n";
        cout << "For every state and alphabet character please enter the name of the state that it should transition to :\n";
        
        for(int i = 0 ; i < stateNum ; i++){
            cout << "\n-=-=- For state : ( " << States[i] << " ) -=-=- \n";
            for(int j = 0 ; j < alphaNum ; j++){
                string stateName;
                do{
                    cout << "Character ( " << Alphabet[j] << " )  =>  ";
                    cin >> stateName;
                } while(invalidInputTest(stateName));
                transitionTable[{States[i], Alphabet[j]}] = stateName;
            }
        }
    }
    void setStartState(){
        cout << "\nEnter the name of the start state :\n";
        string stateName;
        do{
            cin >> stateName;
        } while(invalidInputTest(stateName));
        startState = stateName;
    }
    void setFinalStates(){
        cout << "\nEnter the number of the final states :\n";
        string input;
        do{
            cin >> input;
        } while(notNumberTest(input));
        finalNum = stoi(input);
        cout << "\nEnter the names of the final states :\n";
        for(int i = 1 ; i <= finalNum ; i++){
            cout << i << " => ";
            string stateName;
            do{
                cin >> stateName;
            } while(invalidInputTest(stateName));
            finalState[stateName] = true;
        }
    }
    void displayDFA(){
        cout << "\nYour DFA machine is now completed!\nYour DFA Components are :\n\n";
        cout << "1 - The States :\n";
        for(int i = 0 ; i < stateNum ; i++){
            cout << i+1 << " => ";
            cout << States[i] << "\n";
        }
        cout << "\n\n2 - The Alphabet :\n";
        for(int i = 0 ; i < alphaNum ; i++){
            cout << i+1 << " => ";
            cout << Alphabet[i] << "\n";
        }
        cout << "\n\n3 - The Start State :\n";
        cout << startState;
        cout << "\n\n\n4 - The Final States :\n";
        for(int i = 0, cnt = 1; i < stateNum ; i++){
            if(finalState[States[i]]){
                cout << cnt++ << " => ";
                cout << States[i] << "\n";
            }
        }
        cout << "\n\n5 - The Transition Table :\n";
        for(int i = 0 ; i < stateNum ; i++){
            cout << "\n-=-=- For state : ( " << States[i] << " ) -=-=- \n";
            for(int j = 0 ; j < alphaNum ; j++){
                cout << "Character ( " << Alphabet[j] << " )  =>  ";
                cout << transitionTable[{States[i], Alphabet[j]}] << "\n";
            }
        }
    }
    bool testWord(string word) {
        string currState = startState;
        for (int i = 0; i < word.size(); i++) {
            //testing for invalid character in the word
            if(transitionTable.find({currState, word[i]}) == transitionTable.end()){
                return false;
            }
            currState = transitionTable[{currState, word[i]}];
        }
        if (finalState[currState]) {
            return true;
        }
        return false;
    }
};

DFA_Machine initDFA(){
    
    DFA_Machine DFA;
    cout << "-=-=-=-=-=-=-=- DFA Machine Build -=-=-=-=-=-=-=-\n";
    DFA.setStates();
    DFA.setAlphabet();
    DFA.setTransitionTable();
    DFA.setStartState();
    DFA.setFinalStates();
    cout << "-=-=-=-=-=-=-=- DFA Machine Build Finished -=-=-=-=-=-=-=-\n";
    return DFA;
    
}

int validateDFA(DFA_Machine DFA){
    DFA.displayDFA();
    int choice;
    while(true){
        cout << "\n\nChoose one of the following\n\n";
        cout << "1 - Continue Testing Words On This DFA\n";
        cout << "2 - Rebuild The DFA\n";
        cout << "3 - Exit The Program\n";
        cin >> choice;
        if(choice == 1 || choice == 2 || choice == 3){
            return choice;
        }
    }
}

int main() {
    DFA_Machine DFA;
    while(true){
        DFA = initDFA();
        int choice = validateDFA(DFA);
        if(choice == 1){
            break;
        }
        else if(choice == 3){
            return 0;
        }
    }
    
    while(true){
        cout << "\nEnter the word you want to test or type Exit\n-=-=-=-=-=-=-=\n\n";
        string word;
        cin >> word;
        if (word == "Exit") {
            return 0;
        }

        if (DFA.testWord(word)) {
            cout << "Accepted Word!\n\n";
        }
        else {
            cout << "Rejected Word!\n\n";
        }
    }
}
