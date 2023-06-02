#include <iostream>
#include <vector>
#include "nodes.hpp"

int main()
{

    nodes::Node n1 = nodes::Node();

    vector<string> nodeAttr{
        "Blue", "Red", "Green"};

    nodes::Node n2 = nodes::Node(nodeAttr);

    n1.addConnection(&n2);

    n1.addAttribute("Purple");

    nodes::GraphDocument doc = nodes::GraphDocument();

    doc.appendNode(&n1);
    doc.appendNode(&n2);

    nodes::Node n3 = nodes::Node();

    n3.addAttribute("Yellow");
    doc.appendNode(&n3);

    doc.appendConnection(n1, &n3);

    doc.print();

    return 0;
}   
