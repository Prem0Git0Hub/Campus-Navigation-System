#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int to;
    int weight;
};
struct Location{
    string name;
    int x;
    int y;
};
struct Result{
    vector<int> path;
    int cost;
    int explored;
};
vector<Location> locations={
    {"Main Gate",80,300},
    {"Admin Block",220,180},
    {"USAR Block",400,120},
    {"USDI Block",400,300},
    {"Library",600,180},
    {"Auditorium",760,100},
    {"Sports Complex",760,300},
    {"Boys Hostel",520,430},
    {"Girls Hostel",720,470},
    {"Cafeteria",580,320}
};
vector<vector<Edge> > graph(locations.size());
void addEdge(int u,int v,int weight){
    graph[u].push_back(Edge{v,weight});
    graph[v].push_back(Edge{u,weight});
}
void buildGraph(){
    addEdge(0,1,140);
    addEdge(0,3,210);
    addEdge(1,2,190);
    addEdge(1,3,190);
    addEdge(2,4,210);
    addEdge(2,5,370);
    addEdge(3,4,220);
    addEdge(3,9,190);
    addEdge(4,5,180);
    addEdge(4,9,120);
    addEdge(4,6,220);
    addEdge(3,7,190);
    addEdge(7,8,220);
    addEdge(7,9,100);
    addEdge(8,6,180);
    addEdge(9,6,210);
}
Result dijkstra(int start,int destination){
    const int INF=1000000000;
    vector<int> distance(locations.size(),INF);
    vector<int> parent(locations.size(),-1);
    vector<bool> visited(locations.size(),false);
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
    distance[start]=0;
    pq.push(make_pair(0,start));
    int explored=0;
    while(!pq.empty()){
        pair<int,int> current=pq.top();
        pq.pop();
        int u=current.second;
        if(visited[u])
            continue;
        visited[u]=true;
        explored++;
        if(u==destination)
            break;
        for(int i=0;i<(int)graph[u].size();i++){
            int v=graph[u][i].to;
            int weight=graph[u][i].weight;
            int newDistance=distance[u]+weight;
            if(newDistance<distance[v]){
                distance[v]=newDistance;
                parent[v]=u;
                pq.push(make_pair(newDistance,v));
            }
        }
    }
    if(distance[destination]==INF)
        return Result{vector<int>(),-1,explored};
    vector<int> path;
    int current=destination;
    while(current!=-1){
        path.push_back(current);
        current=parent[current];
    }
    reverse(path.begin(),path.end());
    return Result{path,distance[destination],explored};
}
double getScale(){
    double scale=1e9;
    for(int u=0;u<(int)graph.size();u++){
        for(int i=0;i<(int)graph[u].size();i++){
            int v=graph[u][i].to;
            if(u>=v)
                continue;
            double dx=locations[u].x-locations[v].x;
            double dy=locations[u].y-locations[v].y;
            double visualDistance=sqrt(dx*dx+dy*dy);
            if(visualDistance>0)
                scale=min(scale,graph[u][i].weight/visualDistance);
        }
    }
    return scale;
}
double heuristic(int u,int destination,double scale){
    double dx=locations[u].x-locations[destination].x;
    double dy=locations[u].y-locations[destination].y;
    return sqrt(dx*dx+dy*dy)*scale;
}
Result aStar(int start,int destination){
    const int INF=1000000000;
    vector<int> distance(locations.size(),INF);
    vector<int> parent(locations.size(),-1);
    vector<bool> visited(locations.size(),false);
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
    double scale=getScale();
    distance[start]=0;
    pq.push(make_pair((int)heuristic(start,destination,scale),start));
    int explored=0;
    while(!pq.empty()){
        pair<int,int> current=pq.top();
        pq.pop();
        int u=current.second;
        if(visited[u])
            continue;
        visited[u]=true;
        explored++;
        if(u==destination)
            break;
        for(int i=0;i<(int)graph[u].size();i++){
            int v=graph[u][i].to;
            int weight=graph[u][i].weight;
            int newDistance=distance[u]+weight;
            if(newDistance<distance[v]){
                distance[v]=newDistance;
                parent[v]=u;
                int priority=newDistance+(int)heuristic(v,destination,scale);
                pq.push(make_pair(priority,v));
            }
        }
    }
    if(distance[destination]==INF)
        return Result{vector<int>(),-1,explored};
    vector<int> path;
    int current=destination;
    while(current!=-1){
        path.push_back(current);
        current=parent[current];
    }
    reverse(path.begin(),path.end());
    return Result{path,distance[destination],explored};
}
bool isRouteEdge(int u,int v,const vector<int>& path){
    for(int i=1;i<(int)path.size();i++){
        if((path[i-1]==u&&path[i]==v)||(path[i-1]==v&&path[i]==u))
            return true;
    }
    return false;
}
void createMap(const vector<int>& path,int total,string algorithm){
    ofstream file("route.svg");
    file<<"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"900\" height=\"600\">";
    file<<"<rect width=\"900\" height=\"600\" fill=\"#f5f7fa\"/>";
    file<<"<text x=\"40\" y=\"40\" font-family=\"Arial\" font-size=\"26\" font-weight=\"bold\">USAR Campus Navigation</text>";
    file<<"<text x=\"40\" y=\"68\" font-family=\"Arial\" font-size=\"15\">Algorithm: "<<algorithm<<" | Shortest route: "<<total<<" m approximately</text>";
    for(int u=0;u<(int)graph.size();u++){
        for(int i=0;i<(int)graph[u].size();i++){
            int v=graph[u][i].to;
            int weight=graph[u][i].weight;
            if(u>v)
                continue;
            bool active=isRouteEdge(u,v,path);
            string lineColor=active?"#e53935":"#9aa0a6";
            int lineWidth=active?7:3;
            file<<"<line x1=\""<<locations[u].x<<"\" y1=\""<<locations[u].y<<"\" x2=\""<<locations[v].x<<"\" y2=\""<<locations[v].y<<"\" stroke=\""<<lineColor<<"\" stroke-width=\""<<lineWidth<<"\"/>";
            int x=(locations[u].x+locations[v].x)/2;
            int y=(locations[u].y+locations[v].y)/2;
            file<<"<text x=\""<<x<<"\" y=\""<<y<<"\" font-family=\"Arial\" font-size=\"11\" fill=\"#555\">"<<weight<<"m</text>";
        }
    }
    for(int i=0;i<(int)locations.size();i++){
        bool selected=find(path.begin(),path.end(),i)!=path.end();
        string fill=selected?"#ffcc80":"white";
        file<<"<circle cx=\""<<locations[i].x<<"\" cy=\""<<locations[i].y<<"\" r=\"18\" fill=\""<<fill<<"\" stroke=\"#222\" stroke-width=\"2\"/>";
        file<<"<text x=\""<<locations[i].x+25<<"\" y=\""<<locations[i].y+5<<"\" font-family=\"Arial\" font-size=\"13\">"<<locations[i].name<<"</text>";
    }
    file<<"</svg>";
    file.close();
}
void printResult(string name,const Result& result){
    cout<<"\n"<<name<<":\n";
    if(result.cost==-1){
        cout<<"No route exists.\n";
        return;
    }
    cout<<"Route: ";
    for(int i=0;i<(int)result.path.size();i++){
        if(i>0)
            cout<<" -> ";
        cout<<locations[result.path[i]].name;
    }
    cout<<"\nCost: "<<result.cost<<" metres approximately";
    cout<<"\nNodes explored: "<<result.explored<<"\n";
}
int main(){
    buildGraph();
    cout<<"========================================\n";
    cout<<"       USAR CAMPUS NAVIGATION\n";
    cout<<"========================================\n\n";
    cout<<"Campus Locations:\n\n";
    for(int i=0;i<(int)locations.size();i++)
        cout<<i+1<<". "<<locations[i].name<<"\n";
    int start,destination;
    cout<<"\nEnter start location number: ";
    cin>>start;
    cout<<"Enter destination location number: ";
    cin>>destination;
    if(start<1||start>(int)locations.size()||destination<1||destination>(int)locations.size()){
        cout<<"\nInvalid location number.\n";
        return 0;
    }
    start--;
    destination--;
    Result d=dijkstra(start,destination);
    Result a=aStar(start,destination);
    printResult("Dijkstra",d);
    printResult("A*",a);
    cout<<"\n========================================\n";
    cout<<"             COMPARISON\n";
    cout<<"========================================\n";
    if(d.cost!=-1&&a.cost!=-1){
        cout<<"Same shortest cost: "<<(d.cost==a.cost?"YES":"NO")<<"\n";
        cout<<"Dijkstra nodes explored: "<<d.explored<<"\n";
        cout<<"A* nodes explored: "<<a.explored<<"\n";
        if(a.explored<d.explored)
            cout<<"A* explored fewer nodes.\n";
        else if(a.explored>d.explored)
            cout<<"Dijkstra explored fewer nodes for this route.\n";
        else
            cout<<"Both explored the same number of nodes.\n";
        createMap(a.path,a.cost,"A*");
        cout<<"Visual map created: route.svg\n";
    }else{
        cout<<"No valid route found.\n";
    }
    return 0;
}