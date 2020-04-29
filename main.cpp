#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class Node{
	public:
		int index;
		int color; //0 = white, 1 = grey, 2 = black
		int distance;
		Node * parent;

		Node(){
			index = -1;
			color = 0;
			distance = -1;
			parent = NULL;
		}
};

vector<pair<int,int> > BFS_list(vector<vector<int> >, vector<Node* >, int startNode);

int main(int argc, char* argv[]){
	int directed = 0; //directed = 1, undirected = 0
    int numOfNodes = 0, numOfEdges = 0;

	int firstNode = 0, secondNode = 0;
	string line;

	ifstream infile(argv[1]);

	getline(infile, line);
	directed = stoi(line);

	getline(infile, line);
	stringstream s(line);
	s >> numOfNodes >> numOfEdges;

	vector<vector<int> > adjList;
	vector<Node *> nodes; nodes.resize(numOfNodes);

	while(getline(infile, line)){
		stringstream s2(line);

		s2 >> firstNode >> secondNode;

		if(directed==1){

		}else{
			vector<int>::iterator indexFound = find(adjList[firstNode].begin(), adjList[firstNode].end(), secondNode);
			
			if(indexFound!=adjList[firstNode].end()){
				adjList[firstNode].push_back(secondNode);
			}
			
			indexFound = find(adjList[secondNode].begin(), adjList[secondNode].end(), firstNode);
			
			if(indexFound!=adjList[secondNode].end()){
				adjList[secondNode].push_back(firstNode);
			}
		}
	}
	
	cout << directed << "\n" << numOfNodes << " " << numOfEdges << endl;
	//BFS_list(adjList, nodes, 0);
}

vector<pair<int,int> > BFS_list(vector<vector<int> > adjList, vector<Node* > vertex, int startNode){
  vector<pair<int,int> > edgesIncluded;
  Node * s = vertex[startNode];
  s->color = 1;//grey
  s->distance = 0;//origin
  s->parent = NULL;
  s->index = startNode;
  queue<Node *> Q;
  Q.push(s);
  while(!Q.empty()){
    Node * x = Q.front();
    Q.pop();
    for(int edge: adjList[x->index]){
      Node * v = vertex[edge];
      if(v->color==0){//white
        v->color=1;//grey
        v->distance = x->distance + 1;
        v->parent = x;
        v->index = edge;
        pair<int,int> BFSedge(x->index,v->index);
        edgesIncluded.push_back(BFSedge);
        Q.push(v);
      }
    }
    x->color = 2;//black
  }
  return edgesIncluded;
}

//it = find (myvector.begin(), myvector.end(), 30);
