#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "depot.hpp"
#include "customer.hpp"
#include "geneticAlgorithm.hpp"

int main(int argc, char *argv[])
{
    srand(1999);
    if (argc <= 1)
    {
        return -1;
    }
    
    std::string filename = argv[1];
    std::ifstream file(filename);
    
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string line;
    
    std::getline(fileStream, line);
    std::istringstream is(line);
    
    int m, n, t;
    is >> m >> n >>t;
    
    is.clear();
    is.seekg(0);
    
    std::vector<Depot> depots;
    std::vector<Customer> customers;
    
    for(int i = 1; i <= t; ++i)
    {
        std::getline(fileStream, line);
        std::istringstream is2(line);
        int D, Q;
        is2 >> D >> Q;
        depots.push_back(Depot(i, D, Q));
    }
    int scale[4] = {INT_MAX, INT_MAX, INT_MIN, INT_MIN};
    
    
    
    for(int _ = 0; _<n; _++)
    {
        int i, x, y, d, q;
        
        std::getline(fileStream, line);
        std::istringstream is2(line);
        is2 >> i >> x >> y >> d >> q;

        
        customers.push_back(Customer(i, x, y, d, q));
        
        if (x< scale[0])
        {
            scale[0] = x;
        }
        if (y< scale[1])
        {
            scale[1] = y;
        }
        if (x> scale[2])
        {
            scale[2] = x;
        }
        if (y> scale[3])
        {
            scale[3] = y;
        }
    }
    
    for(int i = 0; i<t; i++)
    {
        int x, y, dc;
        std::getline(fileStream, line);
        std::istringstream is2(line);
        is2 >> dc >> x >> y ;

        depots[i].addCoordinates(x, y);
        
        if (x< scale[0])
        {
            scale[0] = x;
        }
        if (y< scale[1])
        {
            scale[1] = y;
        }
        if (x> scale[2])
        {
            scale[2] = x;
        }
        if (y> scale[3])
        {
            scale[3] = y;
        }
    }
    
    GeneticAlgorithm ga(depots, customers, scale, m);
    ga.run(5000, 5000, 400);
    //ga.run(30000, 200);
    //ga.run(10000, 200);
    
    return 0;
}

