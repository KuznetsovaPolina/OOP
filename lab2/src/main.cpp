#include <iostream>
#include "Five.h"

int main(){
    Five a("13");
    Five b("4");
    Five c=a.add(b);
    std::cout<<a.to_string()<<" + "<<b.to_string()<<" = "<<c.to_string()<<std::endl;
    return 0;
}
