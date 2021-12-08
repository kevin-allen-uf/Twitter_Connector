// Other includes go here
#include "Graph.h"
#include <iostream>
using namespace std;

int main () {

   // Step 1
   Graph twitterData;

   cout << endl << "Welcome to the Twitter Connector!" << endl;
   cout << "Created by JDK Co. (John Ridgeway, Dennis Kim, Kevin Allen)" << endl;
   cout << "-----------------------------------------------------------" << endl;

   // Step 2 - 5
    while (true) { // Main menu
    
        
        cout << endl << "Twitter Connector Menu" << endl;
        cout << "----------------------" << endl << endl;
        cout << "1. Find connection levels between users" << endl;
        cout << "2. Find users connected network" << endl;
        cout << "3. Find strongly connected component of user" << endl;
        cout << "4. Exit" << endl << endl;

        cout << "Enter menu option: ";
        int option;
        cin >> option;

        if (option == 1) { // Find connection levels between users
            cout << "Enter first user ID (enter integer between 1-11316811): ";
            int id1;
            cin >> id1;
            cout << "Enter second user ID (enter integer between 1-11316811): ";
            int id2;
            cin >> id2;
            
            int levels = 0;

            if (!twitterData.BFS(id1, id2, levels)) {
                cout << "There is no connection from user " << id1 << " to user " << id2 << endl;
            }
            else {

                if (levels > 1) {
                    cout << "There are " << levels << " levels of connection from user " << id1 << " to user " << id2 << endl;
                }
                 else if (levels > 0) {
                    cout << "There is " << levels << " level of connection from user " << id1 << " to user " << id2 << endl;
                }
            }

            levels = 0;

            if (!twitterData.BFS(id2, id1, levels)) {
                cout << "There is no connection from user " << id2 << " to user " << id1 << endl;
            }
            else {

                if (levels > 1) {
                    cout << "There are " << levels << " levels of connection from user " << id2 << " to user " << id1 << endl;
                }
                 else if (levels > 0) {
                    cout << "There is " << levels << " level of connection from user " << id2 << " to user " << id1 << endl;
                }
            }
        }
        else if (option == 2) { // Find user’s connected network
            cout << "Enter user ID (enter integer between 1-11316811): ";
            int id;
            cin >> id;
            vector<vector<int>> connections = twitterData.GetConnections(id);

            if (connections[0].size() > 1) {
                cout << "User " << id << "'s Following Level 1 Connections: " << connections[0][1] << endl;

                if (connections[0].size() > 2) {
                    cout << "User " << id << "'s Following Level 2 Connections: " << connections[0][2] << endl;
                }
            }
            else {
                cout << "User " << id << " has no following connections" << endl;
            }
            
            if (connections[1].size() > 1) {
                cout << "User " << id << "'s Follower Level 1 Connections: " << connections[1][1] << endl;

                if (connections[1].size() > 2) {
                    cout << "User " << id << "'s Follower Level 2 Connections: " << connections[1][2] << endl;
                }
            }
            else {
                cout << "User " << id << " has no follower connections" << endl;
            }

        }
        else if (option == 3) { // Find strongly connected component of user
            cout << "Enter user ID (enter integer between 1-11316811): ";
            int id;
            cin >> id;

            vector<int> strongConnections = twitterData.GetIDSCC(id);
            cout << "Size of Strongly Connected Component containing user " << id << ": " << strongConnections.size() << endl;
        }
        else if (option == 4) { // Exit
            cout << "Thank you for using the Twitter Connector!" << endl;
            break;
        }
        else {
            cout << "Invalid option input! Please enter an integer between 1-4" << endl;
        }
    }

    return 0;
}
