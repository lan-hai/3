#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    string label;
    map<string, void*> properties;  // 任意属性
};

struct Edge {
    int id;
    int src;
    int dst;
    map<string, void*> properties;
};

class GraphDB {
  public:
    map<int, Node*> nodes;
    map<int, Edge*> edges;
    map<int, vector<Edge*>> outEdges;
    map<int, vector<Edge*>> inEdges;
    int nextEdgeID = 1;

    ~GraphDB() {
        // 释放所有节点和边
        for (auto& p : nodes) delete p.second;
        for (auto& p : edges) delete p.second;
    }

    void AddNode(int id, const map<string, void*>& properties) {
        if (nodes.count(id)) return;
        Node* n = new Node{id, "", properties};
        nodes[id] = n;
    }

    void AddEdge(int src, int dst, const map<string, void*>& properties) {
        if (!nodes.count(src) || !nodes.count(dst)) return;
        int eid = nextEdgeID++;
        Edge* e = new Edge{eid, src, dst, properties};
        edges[eid] = e;
        outEdges[src].push_back(e);
        inEdges[dst].push_back(e);
    }

    void UpdateNode(int id, const map<string, void*>& properties) {
        if (!nodes.count(id)) return;
        nodes[id]->properties = properties;
    }

    void DelNode(int id) {
        if (!nodes.count(id)) return;
        // 删除相关边
        vector<int> toDel;
        for (auto& p : edges) {
            if (p.second->src == id || p.second->dst == id) toDel.push_back(p.first);
        }
        for (int eid : toDel) DelEdge(eid);
        delete nodes[id];
        nodes.erase(id);
    }

    void DelEdge(int id) {
        if (!edges.count(id)) return;
        Edge* e = edges[id];
        // 从outEdges和inEdges移除
        auto& outV = outEdges[e->src];
        outV.erase(remove(outV.begin(), outV.end(), e), outV.end());
        auto& inV = inEdges[e->dst];
        inV.erase(remove(inV.begin(), inV.end(), e), inV.end());
        delete e;
        edges.erase(id);
    }

    Node* GetNode(int id) {
        if (!nodes.count(id)) return nullptr;
        return nodes[id];
    }

    Edge* GetEdge(int id) {
        if (!edges.count(id)) return nullptr;
        return edges[id];
    }

    void PrintNode(int nodeId) {
        Node* n = GetNode(nodeId);
        if (!n) { printf("Node %d not found\n", nodeId); return; }
        printf("Node %d, label: %s\n", n->id, n->label.c_str());
        printf("Properties: %zu\n", n->properties.size());
        printf("OutEdges: %zu\n", outEdges[nodeId].size());
        printf("InEdges: %zu\n", inEdges[nodeId].size());
    }
};

// 简单测试
#include <iostream>
int main() {
    GraphDB db;
    db.AddNode(1, {});
    db.AddNode(2, {});
    db.AddEdge(1, 2, {});
    db.PrintNode(1);
    db.PrintNode(2);
    db.DelNode(1);
    db.PrintNode(1);
    db.PrintNode(2);
    return 0;
}