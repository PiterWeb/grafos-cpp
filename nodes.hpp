#pragma once
#include <map>

using namespace std;

namespace nodes
{

    class NodeIdentified
    {

    public:
        NodeIdentified();
        string getId();

    private:
        string id;
        static string random_id();
    };

    class Node : public NodeIdentified
    {
    public:
        Node();

        Node(vector<string> initAttributes);

        Node(vector<string> initAttributes, vector<string> initConnections);

        long nConnections();

        vector<string> getConnections();

        vector<string> getAttributes();

        string attributtesToString();

        string connectionsToString();

        void addAttribute(string attr);

        bool isConnectedWith(string nId);

        bool isConnectedWith(Node n);

        void addConnection(Node *n);

        void removeConnection(Node *n);

        string static to_string(Node n);

    private:
        vector<string> attributes;
        vector<string> connections;
    };

    class GraphDocument
    {

    public:
        GraphDocument();

        GraphDocument(map<string, nodes::Node *> initInstance);

        void appendNode(Node *n);

        void removeNode(Node n);

        void removeNode(string nId);

        void appendConnection(Node n1, Node *n2);

        void removeConnection(Node n1, Node *n2);

        void print();

    private:
        map<string, nodes::Node *> instance;
    };

};
