#include <ctime>
#include <cstring>
#include <iostream>
#include <vector>
#include <random>
#include "nodes.hpp"

using namespace std;

nodes::NodeIdentified::NodeIdentified()
{
    id = random_id();
};

// Credits to this answer: (CaptainCodeman)
// https://stackoverflow.com/a/58467162/17779964
string nodes::NodeIdentified::random_id()
{
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 35);

    const char *v = "0123456789abcdefghijklmnopqrstuvwxyz";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    string res;
    for (int i = 0; i < 16; i++)
    {
        if (dash[i])
            res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
};

string nodes::NodeIdentified::getId()
{
    return id;
};

nodes::Node::Node(){

};

nodes::Node::Node(vector<string> initAttributes)
{
    attributes = initAttributes;
}

nodes::Node::Node(vector<string> initAttributes, vector<string> initConnections)
{
    attributes = initAttributes;
    connections = initConnections;
};

vector<string> nodes::Node::getConnections()
{
    return connections;
};

vector<string> nodes::Node::getAttributes()
{
    return attributes;
}

string nodes::Node::attributtesToString()
{
    string ret_string = "[";
    for (const string &s : attributes)
        ret_string.append(s + ";");
    ret_string.resize(ret_string.size() - 1);
    ret_string.append("]");
    return ret_string;
};

string nodes::Node::connectionsToString()
{
    string connectionStrings = "[";
    for (const string nId : connections)
        connectionStrings.append(nId + ";");
    connectionStrings.resize(connectionStrings.size() - 1);
    connectionStrings.append("]\n");
    return connectionStrings;
}

void nodes::Node::addAttribute(string attr)
{
    if (attributes.size() < 100)
    {
        attributes.push_back(attr);
        return;
    }

    cout << "Node " << getId() << " has max attributes (100)";
}

bool nodes::Node::isConnectedWith(string nId)
{

    for (const string idStored : connections)
        if (strcmp(idStored.data(), nId.data()) == 0)
            return true;

    return false;
}

bool nodes::Node::isConnectedWith(Node n)
{

    for (const string idStored : connections)
        if (strcmp(idStored.data(), n.getId().data()) == 0)
            return true;

    return false;
}

void nodes::Node::addConnection(Node *n)
{
    if (!isConnectedWith(*n) && connections.size() < 100 && n->connections.size() < 100)
    {
        connections.push_back(n->getId());
        n->connections.push_back(getId());
        return;
    }

    cout << "Node " << getId() << " has max connections (100)" << endl;
}

void nodes::Node::removeConnection(Node *n)
{
    string nId = n->getId();

    for (size_t i = 0; i < connections.size(); i++)
        if (strcmp(connections[i].data(), nId.data()) == 0)
            connections.erase(connections.begin() + i);

    for (size_t i = 0; i < n->connections.size(); i++)
        if (strcmp(n->connections[i].data(), getId().data()) == 0)
            n->connections.erase(n->connections.begin() + i);
}

nodes::GraphDocument::GraphDocument()
{
    instance = map<string, nodes::Node *>();
};

nodes::GraphDocument::GraphDocument(map<string, nodes::Node *> initInstance)
{
    instance = initInstance;
};

void nodes::GraphDocument::appendNode(Node *n)
{
    instance.insert(pair<string, Node *>(n->getId(), n));
}

void nodes::GraphDocument::removeNode(Node n)
{
    instance.erase(n.getId());
}

void nodes::GraphDocument::removeNode(string nId)
{
    instance.erase(nId);
}

void nodes::GraphDocument::appendConnection(Node n, Node *n2)
{
    instance[n.getId()]->addConnection(n2);
}

void nodes::GraphDocument::removeConnection(Node n, Node *n2)
{
    instance[n.getId()]->removeConnection(n2);
}

void nodes::GraphDocument::print()
{
    for (const pair<string, Node *> &n : instance)
        cout << Node::to_string(*n.second) << "\n";
}

string nodes::Node::to_string(Node node)
{
    return "Node: " + node.getId() + ";\n\tAttributtes: " + node.attributtesToString() + "\n\tConnections: " + node.connectionsToString();
};
