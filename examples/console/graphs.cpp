#include "graph.hpp"
#include "graphalgorithms.hpp"
#include <iostream>
int main (){
    auto empty_visitor=[](auto v){};
    auto empty_childhandler=[](auto p,auto c){};
    auto printparents=[](auto& map,auto node,auto root,auto tostring){
        auto p=node;
        std::cout << tostring(p);
        while(p!=root){
            p=map[p];
            std::cout <<" << " << tostring(p);
        }
    };
    DGraph g(10);
    g.add_edge(0,2);
    g.add_edge(0,5);
    g.add_edge(2,5);
    g.add_edge(1,5);
    g.add_edge(5,1);
    g.print(std::cout);
    std::vector<int> parents;
    parents.reserve(10);
    travers(g,0,GDFS(),[&](auto p,auto c){
       parents[c]=p;
    },empty_visitor);
    printparents(parents,1,0,[](auto v){return std::to_string(v);});
    SDGraph sg(10);
    sg.add_edge("Abhilash","Abhila");
    sg.add_edge("Abhilash","Pranav");
    sg.add_edge("Abhila","Pranav");

    sg.print(std::cout);

    std::map<std::string,std::string> strparents;
    travers(sg,"Abhilash",GDFS(),[&](auto p,auto c){
        strparents[c]=p;
    },empty_visitor);
    printparents(strparents,std::string("Pranav"),std::string("Abhilash"),[](auto& v){return v;});



    RowMatrix<int> mg({
                       1,0,0,1,
                       1,1,0,1,
                       0,0,1,1,
                       1,0,1,1,
                     },4);
    mg.setPredicate([](int c){return c==1;}).print(std::cout);
    travers(mg,1,GBFS(),[&](auto p,auto c){

    },[](auto v){
        std::cout<<v<<" ";
    });




    using CGVertex=typename CrossMatrix<char>::VertexType;
    CrossMatrix<char> cg({
                       'a','b','a','a',
                       'b','b','b','a',
                       'a','b','a','a',
                       'b','b','a','a',
                     });
    cg.setPredicate([](char c){return c=='a';}).printContent(std::cout);

    std::map<CGVertex,CGVertex> vertexParents;
    travers(cg,CGVertex{3,3},GDFS(),[&](auto p,auto c){
        vertexParents[c]=p;
        std::cout<< cg.to_string(p)<<cg.to_string(c)<<"\n";
    },[&](auto v){
        cg.setValue(v,'b');
    });
    printparents(vertexParents,CGVertex{0,2},CGVertex{0,0},[&](auto& v){return cg.to_string(v);});
    cg.printContent(std::cout);

    EdgeWeightedGraph eg(10);
    eg.addEdge(Edge{0,1,7}).addEdge(Edge{0,2,5});
    eg.print(std::cout);



}
