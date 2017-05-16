#include<iostream>
#include<string.h>
#include<list>
#include<stack>
#include<queue>

using namespace std;

template <class T>
class Graph{
	int V;
	list<T> *adj;
	void DFSUtil(bool visited[], T u){
		visited[u] = 1;
		cout<<u<<" ";
		typename list<T>::iterator it;
		
		for(it = adj[u].begin(); it != adj[u].end(); it++){
			if(!visited[*it])
				DFSUtil(visited, *it);
		}
	}
	
	bool isCyclicUtil(bool visited[], bool recStack[], T u){
		visited[u] = 1;
		recStack[u] = 1;
		typename list<T>::iterator it;
		
		for(it = adj[u].begin(); it != adj[u].end(); it++){
			if(!visited[*it] && isCyclicUtil(visited, recStack, *it))
				return 1;
			if(recStack[*it])
				return 1;
					
		}
		recStack[u] = 0;
		return 0;
		
	}
	
	void TopologicalSortUtil(bool visited[], T u, stack<T>& Stack){
		visited[u] = 1;
		typename list<T>::iterator it;
			
		for(it = adj[u].begin(); it != adj[u].end(); it++){
			if(!visited[*it])
				TopologicalSortUtil(visited,*it,Stack);
		}
		//cout<<"pushing "<<u<<endl;
		Stack.push(u);
	}
	
	//This BFS does not work for disconnected graph or it will not display those vertices who doesn't have path from the source. like in this example 4.
	//For displaying disconnected graph we have to put it into loop as we did in DFS
	void BFS(bool visited[], T s){
		queue<T> myQueue;
		myQueue.push(s);
		visited[s] = 1;
		
		while(!myQueue.empty()){
			T u = myQueue.front();
			myQueue.pop();
			cout<<u<<" ";
			typename list<T>::iterator it;
			for(it = adj[u].begin(); it != adj[u].end(); it++){
				if(!visited[*it]){
					visited[*it] = 1;
					myQueue.push(*it);
				}
			}
		}
	}
	
	public:
		Graph(int vertices){
			V = vertices;
			adj = new list<T>[V];
		}
		~Graph(){
			delete []adj;
			//cout<<"Destructor executed "<<endl;
		}
		
		//Adding edge between vertices
		void addEdge(T u, T v){
			adj[u].push_back(v);
			//adj[v].push_back(u); //for creation of undirected graph uncomments this.
		}
		
		//DFS Traversal
		void DFSTraversal(){
			bool *visited = new bool[V];
			memset(visited,0,sizeof(visited));
			for(int i = 0; i<V; i++){
				if(!visited[i])
					DFSUtil(visited, i);
			}
		}	
		
		//Topological Sort by modifying DFS
		void TopologicalSort(){
			stack<T> myStack;
			bool *visited = new bool[V];
			memset(visited,0,sizeof(visited));
			
			for(int i=V-1; i >= 0; i--){
				if(!visited[i])
					TopologicalSortUtil(visited,i,myStack);
			}
			while(!myStack.empty()){
				cout<<myStack.top()<<" ";
				myStack.pop();
			}
		}
		
		//BFS Traversal
		void BFSTraversal(){
			bool *visited = new bool[V];
			memset(visited,0,sizeof(visited));
			
			for(int i = V-1; i >= 0; i--){
				if(!visited[i])
					BFS(visited,i);
			}
		}
		
		//TO check the presence of cycle
		bool isCyclic(){
			bool *visited = new bool[V];
			bool *recStack = new bool[V];
			memset(visited, 0, sizeof(visited));
			memset(recStack, 0, sizeof(recStack));
			
			for(int i = V-1; i >= 0; i--){
				if(!visited[i])
					if(isCyclicUtil(visited, recStack, i)){
						return 1;
					}
			}
			return 0;
		}
		
};

int main(){
	Graph<int> G(6);
	
	G.addEdge(5,2);
	G.addEdge(5,0);
	G.addEdge(4,0);
	G.addEdge(4,1);
	G.addEdge(2,3);
	G.addEdge(3,1);
	G.addEdge(1,5);
	
/*	cout<<"The DFS Traversal : "<<endl;
	G.DFSTraversal();
	cout<<endl;
	
	cout<<"BFS Traversal : "<<endl;
	G.BFSTraversal();
	cout<<endl;
	
	cout<<"Topological sort : "<<endl;
	G.TopologicalSort();
	cout<<endl;*/
	
	bool isCycle = G.isCyclic();
	if(isCycle){
		cout<<"Cyclic Graph"<<endl;
	}
	else{
		cout<<"Non-Cyclic graph"<<endl;	
	}
		
	}