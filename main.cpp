#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n=graph.size();
        //CONSTRUCCION GRAFO DIRECTO
        vector<vector<int>> adj(graph.size());
        for(int i=0; i<graph.size(); i++){
            for(int j=0; j<graph[0].size(); j++){
                if(i!=j && graph[i][j]) adj[i].push_back(j);
            }
        }

        sort(initial.begin(), initial.end());
        int min_infected=INT_MAX;
        int ans=0;
        vector<int> base(n,0);
        
        for(auto &i: initial){
            base[i]=1; //marca los nodos infectados
        }

        for(auto& i: initial){
            vector<int> dp=base; //copia del vector base
            dp[i]=0; //se desinfecta temporalmente el nodo i del vector initial
            vector<int> isvisited(n,false);
            queue<int> Q;
            for(auto& node: initial){
                if(node!=i && isvisited[node]==false){
                    Q.push(node); //se agregan los no visitados pero si infectados
                    isvisited[node]=true; //se marca como visitado
                }
            }
            //PROPAGAR LA INFECCIÓN
            while(!Q.empty()){
                int node=Q.front();
                Q.pop();
                for(auto& edge: adj[node]){
                    if(!isvisited[edge] && i!=edge){
                        isvisited[edge]=true;
                        Q.push(edge);
                        dp[edge]=1; //nodo infectado
                    }
                }
            }
            //calcula la suma total de nodos infectados en el vector dp
            int s=accumulate(dp.begin(),dp.end(),0); 
            if(s<min_infected){
                min_infected=s;
                ans=i;
            }
        }
        return ans;
    }
};