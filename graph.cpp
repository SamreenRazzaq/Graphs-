//Graphs

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include "linklist.h"
#include "object.h"

using namespace std;

class Neighbour : public object {
public:
    string name;
    float distance;

    Neighbour() {}
    Neighbour(string d, float w) {
        name = d;
        distance = w;
    }

    void input() {
        cout << "Enter neighbour name: ";
        cin >> name;
        cout << "Enter distance: ";
        cin >> distance;
    }

    void print() {
        cout << " " << name << " " << distance << " ";
    }
};

class Vertix : public object {
public:
    string name;
    LL neighbourList;
    bool visited;

    Vertix() { 
        visited = false; 
    }

    Vertix(string n) {
        name = n;
        visited = false;
    }

    void addNeighbour(string d, float weight) {
        Neighbour* n = new Neighbour(d, weight);
        neighbourList.insert(n);
    }

    void input() {
        cout << "Enter vertex name: ";
        cin >> name;

        int numNeighbours;
        cout << "Enter number of neighbours: ";
        cin >> numNeighbours;

        for (int i = 0; i < numNeighbours; i++) {
            cout << "Enter neighbour #" << i + 1 << " details:" << endl;
            string neighbourName;
            float distance;

            cout << "Enter neighbour name: ";
            cin >> neighbourName;

            cout << "Enter distance: ";
            cin >> distance;

            addNeighbour(neighbourName, distance);
        }
    }

    void print() {
        cout << " " << name << " ";
        neighbourList.print();
    }

    string getName() {
        return name;
    }
};

class Edge : public object {
public:
    string source;
    string destination;
    float weight;

    Edge() {}

    Edge(string s, string d, float w) {
        source = s;
        destination = d;
        weight = w;
    }

    void input() {}

    void print() {
        cout << " " << source << " " << destination << " " << weight << " ";
    }
};

class Graph {
    LL AdjList;
    LL EdgeList;

public:
    void buildGraph(string filename) {
        ifstream in;
        in.open(filename.c_str());

        // Read vertices and create vertex objects
        string vertices;
        getline(in, vertices);
        cout << vertices;

        while (vertices.length() > 0) {
            Vertix* v;
            int sep = vertices.find(' ');

            if (sep != -1) {
                v = new Vertix(vertices.substr(0, sep));
                vertices = vertices.substr(sep + 1, vertices.length());
            } else {
                v = new Vertix(vertices);
                vertices = vertices.substr(0, 0);
            }

            AdjList.insert(v);
        }

        // Read edges and add neighbours to vertex objects
        while (!in.eof()) {
            string s, d;
            float weight;

            in >> s >> d >> weight;
            cout << s << " " << d << " " << weight << endl;

            int loc = searchInAdjList(s);
            ((Vertix*)AdjList.get(loc))->addNeighbour(d, weight);

            loc = searchInAdjList(d);
            ((Vertix*)AdjList.get(loc))->addNeighbour(s, weight);

            AdjList.print();
        }
    }
    
    int searchInAdjList(string node) {
        for (int i = 0; i < AdjList.getLength(); i++) {
            Vertix* v = static_cast<Vertix*>(AdjList.get(i));
            if (v->getName() == node) {
                return i;
            }
        }
        return -1; // Return -1 if the node is not found
    }

    void print() {
        for (int i = 0; i < AdjList.getLength(); i++) {
            Vertix* v = static_cast<Vertix*>(AdjList.get(i));
            v->print();
        }
    }

    void shortestPathBFS(string source, string dest) {
        // Find the source and destination vertices in the adjacency list
        int sourceIdx = searchInAdjList(source);
        if (sourceIdx == -1) {
            cout << "Source vertex not found in the graph." << endl;
            return;
        }
        int destIdx = searchInAdjList(dest);
        if (destIdx == -1) {
            cout << "Destination vertex not found in the graph." << endl;
            return;
        }

        // Create a queue to store the vertices to be visited
        queue<Vertix*> q;

        // Enqueue the source vertex
        Vertix* sourceVertix = static_cast<Vertix*>(AdjList.get(sourceIdx));
        sourceVertix->visited = true;
        q.push(sourceVertix);

        // Create a map to store the parent of each vertex in the shortest path
        map<string, string> parentMap;
        parentMap[source] = "";

        // Perform BFS traversal
        while (!q.empty()) {
            // Dequeue a vertex from the queue
            Vertix* currVertix = q.front();
            q.pop();

            // Visit all the neighbours of the current vertex
            for (int i = 0; i < currVertix->neighbourList.getLength(); i++) {
                Neighbour* neighbour = static_cast<Neighbour*>(currVertix->neighbourList.get(i));
                Vertix* neighbourVertix = static_cast<Vertix*>(AdjList.get(searchInAdjList(neighbour->name)));

                // If the neighbour has not been visited, enqueue it and mark it as visited
                if (!neighbourVertix->visited) {
                    neighbourVertix->visited = true;
                    q.push(neighbourVertix);

                    // Add the neighbour to the parent map
                    parentMap[neighbour->name] = currVertix->name;
                }
            }
        }

        // Print the shortest path from the source to the destination
        if (parentMap.find(dest) == parentMap.end()) {
            cout << "Error: there is no path from the source to the destination." << endl;
        } else {
            string currNode = dest;
            cout << currNode;
            while (currNode != source) {
                currNode = parentMap[currNode];
                cout << " <- " << currNode;
            }
            cout << endl;
        }   
		for (int i = 0; i < AdjList.getLength(); i++) {
        Vertix* v = (Vertix*)AdjList.get(i);
        v->visited = false;
    }
}
};


int main() {
    Graph g;

    // Build the graph from the file "GraphMaze.txt"
    g.buildGraph("GraphMaze.txt");

    // Print the graph to verify it was read correctly
    cout << "The graph is: " << endl;
    g.print();

    // Find the shortest path between two vertices using BFS
    string source, dest;
    cout << endl << "Enter the source vertex: ";
    cin >> source;
    cout << "Enter the destination vertex: ";
    cin >> dest;

    g.shortestPathBFS(source, dest);

    return 0;
}

