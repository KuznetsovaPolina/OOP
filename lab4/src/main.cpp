#include <iostream>
#include <memory>
#include "Square.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Array.h"
#include "TotalArea.h"
int main(){
    using Coord=double;
    using FP=std::shared_ptr<Figure<Coord>>;
    Array<FP> figs;
    int n; std::cin>>n;
    for(int i=0;i<n;i++){
        int t; std::cin>>t;
        if(t==1){auto s=std::make_shared<Square<Coord>>();std::cin>>*s;figs.push_back(s);}
        if(t==2){auto r=std::make_shared<Rectangle<Coord>>();std::cin>>*r;figs.push_back(r);}
        if(t==3){auto tr=std::make_shared<Trapezoid<Coord>>();std::cin>>*tr;figs.push_back(tr);}
    }
    for(size_t i=0;i<figs.size();i++){
        std::cout<<*figs[i]<<"\n";
        auto c=figs[i]->center();
        std::cout<<"Center: "<<c.x<<","<<c.y<<" Area: "<<figs[i]->area()<<"\n";
    }
    std::cout<<"Total area: "<<total_area(figs)<<"\n";
}
