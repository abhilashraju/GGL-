# GGL-
Generic Graph Library , A library of generic graph data structures and algorithms

![Traversals](https://github.com/abhilashraju/GGL-/blob/main/demo/Graph%202021-07-20%2022-41-01.gif) ![MST](https://github.com/abhilashraju/GGL-/blob/main/demo/MST%202021-07-20%2022-44-32.gif)
![dapp](https://github.com/abhilashraju/GGL-/blob/main/demo/Graph%202021-07-21%2011-17-34.gif) ![shrtp](https://github.com/abhilashraju/GGL-/blob/main/demo/shrt_path.gif)

Generic and reusable components to solve common graph problems. The implementation follows STL philosophy that separates data structure and alogorithms and connect them together through well defined concepts. So the library is 
1) A collection of reusable generic alogorthms that can work with any data type that are compatible with the concepts the algorithm expects
2) A collection of generic graph containers that reresents different graph models which can be parameterised based on user defined vertex type

This seperation of graph model from its algorithm enables us to achieve multiplicative reusability. Which means you can apply several graph algorithms to a single graph model and vice versa

Examples
```
using Graph=GraphImpl<int,undirected>;
using DGraph=GraphImpl<int,directed>;

DGraph g(10);
g.add_edge(0,2);
g.add_edge(0,5);
g.add_edge(2,5);
g.add_edge(1,5);
g.add_edge(5,1);
g.print(std::cout);
```
In the above example we have created a Directed graph that uses adjuscency list with integer vertex type. Library already provides reusable type aliases for most frequently used graphs. You can notice that how easy it is to change Directed Graph in to Undirected one just by changing the declaration of it. 
Some times you wanted to analyse relationships between entitities using graph algorithms. In those cases the vertex type may not be an integer . It will be an entity represented using your domain type such as Employee or Color. The following example shows how easy it is to create a graph with string vertex type.
```
using SGraph=GraphImpl<std::string,undirected>;
using SDGraph=GraphImpl<std::string,directed>;

SDGraph sg(10);
sg.add_edge("Abhilash","Abhila");
sg.add_edge("Abhilash","Pranav");
sg.add_edge("Abhila","Pranav");
sg.print(std::cout);
```
Notice the generic nature of the implementaion . With single implementation you achieved wide range of graphs with directed and undirected edges that supports any domain specific type. 

Now let's shift our focus to generic algorithm. Let's see how we can do a depth and breadth first seach using above graph structure
Lets us capture the relationship among people(captured using above graph) using a DFS
```
std::map<std::string,std::string> strparents;
travers(sg,"Abhilash",GDFS(),[&](auto p,auto c){
    strparents[c]=p;
},empty_visitor);
```
Travers is a generic function from library that accepts a graph , the start vertex , the search algorithm and two user specfic action that need to be taken whenever 
1) algorithm visit a vertex.
2) algorithm enques a child vertex for visit.

User can choose to provide any of the above two callbacks my leaving other empty depending on their requirements. In this purticular example I choose to give one that can capture the parent child relationship between vertices.

Now let's dig a bit deeper into the actual search algorithms

