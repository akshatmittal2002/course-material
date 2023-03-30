#include <iostream>
#include <vector>

using namespace std;

//Function to traverse the graph.
void traversal(vector<int> graph[], vector<int> &visit, int s);

//Function to find distance of a particular vertex with every other vertex in graph.
void find_distances(vector<int> graph[], vector<int> &visit, vector<int> &dist, int s, int d);

int main()
{
    int vertices; //Variable to store number of vertices in graph.
    cin>>vertices; //Take input.
    vector<int> graph[vertices+1]; //An array of vectors to store all vertices connected to a vertex.
    int edges; //Variable to store number of edges in graph.
    cin>>edges; //Take input.
    //=============================================================================================
    int vertex1 , vertex2; //Variables to store two vertices that will define an edge
    //Take input of all edges.
    for(int i=0; i<edges; i++)
    {
        cin>>vertex1>>vertex2; //Take input
        //Add vertex 2 in vertex 1 and vertex 1 in vertex 2.
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }
    //=============================================================================================
    vector<int> visited(vertices+1,0); //An array to store whether an vertex is connected or not.
    traversal(graph,visited,1); //Traverse the graph.
    bool tree = true; //Variable to store whether given graph is tree or not.
    //Now during traversal, if every vertex has been visited, it 'can' be a tree.
    for(int i=1; i<vertices+1;i++)
    {
        if(visited[i]!=1) //If any vertex is not visited, graph is not a tree.
        {
            tree = false;
            break;
        }
    }
    /*If tree is true, check that graph does not contain any cycle. A direct result of this is:
                                      num of vertices = num of edges + 1      iff     graph do not have any cycle.*/
    if(tree==true)
    {
        if(vertices != (edges+1)) tree=false;
    }
    //=============================================================================================
    //Now make diameter to zero.
    int diameter = 0;
    //If graph is tree, find diameter.
    if(tree==true)
    {
        vector<int> distance(vertices+1,-1); //Array to store distances of each vertex.
        visited.assign(vertices+1,0); //Reset visited array.

        find_distances(graph,visited,distance,1,0); //Call the function for any random vertex.
        //Now find the that vertex which is at maximum distance from this vertex.
        int farthest = 0; //Variable to store the farthest vertex.
        for(int i=1; i<vertices+1; i++)
        {
            if(distance[i] > distance[farthest])
            {
                farthest = i;
            }
        }
        //=============================================================================================
        //Now reset visited and distance array.
        visited.assign(vertices+1,0);
        distance.assign(vertices+1,-1);
        //Call the function for that farthest vertex again.
        find_distances(graph,visited,distance,farthest,0);
        //Now find the vertex which is farthest from the given farthest vertex.
        //Distance between these two will be diameter of tree.
        farthest = 0;
        for(int i=1; i<vertices+1; i++)
        {
            if(distance[i] > distance[farthest])
            {
                farthest = i;
            }
        }
        //Assign this farthest distance to diameter.
        diameter = distance[farthest];
    }
    //Give output.
    if(tree) cout<<"Y\n";
    else cout<<"N\n";
    cout<<diameter<<"\n";
}

void traversal(vector<int> graph[], vector<int> &visit, int s)
{
    //If node has already been visited, just do nothing.
    //Else
    if(visit[s]==0)
    {
        visit[s]=1; //Make the visit = 1.
        //Now traverse all other vertices connected to current vertex.
        for(auto u : graph[s])
        {
            traversal(graph, visit, u);
        }
    }
    return;
}

void find_distances(vector<int> graph[], vector<int> &visit, vector<int> &dist, int s, int d)
{
    //Make visit = 1 for current vertex.
    visit[s] = 1;
    //Make the distance to current distance.
    dist[s] = d;
    //Now for every other vertex connected to current vertex, make distance as d+1, if that vertex has not been visited already.
    //If apply the condition of visit=0, because we have to find shortest distance between vertices.
    for(auto u : graph[s])
    {
        if(visit[u]==0)
        {
            find_distances(graph,visit,dist,u,d+1);
        }
    }
    return;
}
