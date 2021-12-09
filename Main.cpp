// Code developed by JDK Co. (John Ridgeway, Dennis Kim, Kevin Allen)

#include <iostream>
#include <random>
#include <ctime>
#include "Graph.h"

int main () {
    // Construct graph object and perform Kosaraju algorithm before actual program starts
   Graph twitterData;

   // Welcome message with citations
   cout << endl << "Welcome to the Twitter Connector!" << endl;
   cout << "Created by JDK Co. (John Ridgeway, Dennis Kim, Kevin Allen)" << endl;
   cout << "Twitter Data Source (Link): http://datasets.syr.edu/datasets/Twitter.html" << endl;
   cout << "Twitter Data Source (APA): R. Zafarani and H. Liu, (2009). Social Computing Data Repository at ASU [http://socialcomputing.asu.edu]." << endl;; 
   cout << "                           Tempe, AZ: Arizona State University, School of Computing, Informatics and Decision Systems Engineering." << endl;
   cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

    while (true) { 
        // Main menu
        cout << endl << "Twitter Connector Menu" << endl;
        cout << "----------------------" << endl;
        cout << "1. Find connection levels between users" << endl;
        cout << "2. Find users connected network" << endl;
        cout << "3. Find users strongly connected to a user" << endl;
        cout << "4. Exit" << endl << endl;

        cout << "Enter menu option: "; // Get menu option input
        int option;
        cin >> option;

        if (option == 1) { // Find connection levels between users
            cout << "Enter first user ID (enter integer between 1-11316811): "; // Getting user id inputs
            int id1;
            cin >> id1;
            cout << "Enter second user ID (enter integer between 1-11316811): ";
            int id2;
            cin >> id2;
            
            int levels = 0;
            cout << endl << "Performing BFS from user " << id1 << " to user " << id2 << "..."; // Perform BFS id1 to id2 and output result
            if (!twitterData.BFS(id1, id2, levels)) { // Different print statements shown based on levels of connections found
                cout << " done!" << endl;
                cout << "There is no connection from user " << id1 << " to user " << id2 << endl;
            }
            else {
                cout << " done!" << endl;
                if (levels > 1) {
                    cout << "There are " << levels << " levels of connection from user " << id1 << " to user " << id2 << endl;
                }
                 else if (levels > 0) {
                    cout << "There is " << levels << " level of connection from user " << id1 << " to user " << id2 << endl;
                }
            }

            levels = 0; // Reset levels before second BFS call
            cout << "Performing BFS from user " << id2 << " to user " << id1 << "..."; // Peform BFS id2 to id1 and output result
            if (!twitterData.BFS(id2, id1, levels)) { // Different print statements shown based on levels of connections found
                cout << " done!" << endl;
                cout << "There is no connection from user " << id2 << " to user " << id1 << endl;
            }
            else {
                cout << " done!" << endl;
                if (levels > 1) {
                    cout << "There are " << levels << " levels of connection from user " << id2 << " to user " << id1 << endl;
                }
                 else if (levels > 0) {
                    cout << "There is " << levels << " level of connection from user " << id2 << " to user " << id1 << endl;
                }
            }
        }

        else if (option == 2) { // Find user’s connected network
            cout << "Enter user ID (enter integer between 1-11316811): "; // Get user id input
            int id;
            cin >> id;
            cout << endl << "Attempting to create 2 level spanning tree from user " << id << " entire network...";
            vector<vector<int>> connections = twitterData.GetConnections(id); // Perform 2 level spanning tree
            cout << " done!" << endl;

            if (connections[0].size() > 1) { // Different print statements shown based on levels of connections found
                cout << "User " << id << "'s Following Level 1 Connections: " << connections[0][1] << endl;

                if (connections[0].size() > 2) {
                    cout << "User " << id << "'s Following Level 2 Connections: " << connections[0][2] << endl;
                }
            }
            else {
                cout << "User " << id << " has no following connections" << endl;
            }
            
            if (connections[1].size() > 1) { // Different print statements shown based on levels of connections found
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
            cout << "Enter user ID (enter integer between 1-11316811): "; // Get user id input
            int id;
            cin >> id;

            vector<int> strongConnections = twitterData.GetIDSCC(id);

            // Make random number generator between 0 and size - 1 of vector returned to generate 10 random user ids to show for option 3
            mt19937 rng(time(nullptr));
            uniform_int_distribution<std::mt19937::result_type> distSize(0, strongConnections.size() - 1);

            cout << "Number of users strongly connected with user " << id << ": " << strongConnections.size() - 1 << endl; // Print out total users strongly connection

            if (strongConnections.size() < 11 && strongConnections.size() > 1) { // If between 1-10 strong connections print them all
                cout << "User IDs strongly connected with user " << id << ":";
            }
            else if (strongConnections.size() > 1) { // If more than 10 strong connections print only first 10 in vector
                cout << "10 User IDs strongly connected with user " << id << ":";
            }
            int limit = 10;
            for (int i = 0; i < limit; i++) {
                int randomID = distSize(rng);
                if (i == (strongConnections.size())) { // Stops printing once size of vector reached, preventing index out of bounds errors
                    break;
                }
                if (strongConnections[i] == id) { // If original id found (always present in a SCC) then ignore and increase limit so up to 10 ids still printed
                    limit++;
                    continue;
                }
                cout << " " << strongConnections[randomID];
            }
            cout << endl;
        }

        else if (option == 4) { // Exit
            cout << "Thank you for using the Twitter Connector!" << endl;
            break;
        }

        else { // Invalid option response (does not cover non-integer input since course project did not require extensive input validation)
            cout << "Invalid option input! Please enter an integer between 1-4" << endl;
        }
    }

    return 0;
}
