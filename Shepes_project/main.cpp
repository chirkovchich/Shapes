#include <iostream>
#include "shapes.h"
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
    static mt19937 engine;
    engine.seed(time(0));
    uniform_int_distribution<int> rand_int(0, 2);
    uniform_real_distribution<double> rand_real(-2, 10);

    //======
    //2.Populate a container (e.g. vector or list) of objects of these types created in random manner with  random parameters

    vector<shared_ptr<Shape>> shapes;
    shapes.reserve(20);

    for (int i = 0; i < 20 ; ++i){
        int type = rand_int(engine);
        try {
            std::cout << rand_real(engine) << std::endl;
            switch (type) {
                case 0:
                    shapes.emplace_back(make_shared<Circle>(rand_real(engine)));
                break;
                case 1:
                    shapes.emplace_back(make_shared<Ellipse>(rand_real(engine), rand_real(engine)));
                break;
                case 2:
                    shapes.emplace_back(make_shared<Helix>(rand_real(engine), rand_real(engine)));
                break;
            }
        }
        catch (const ParameterException& exc) {
            std::cout << "Error: " << exc.what() << std::endl; //Curves must be physically correct (e.g. radii must be positive).
        }
    }
    std::cout << shapes.size() << std::endl;

    //======
    //3.Print coordinates of points and derivatives of all curves in the container at t=PI/4.

    for (int i = 0; i < shapes.size(); ++i) {
        std::cout << shapes[i]->GetPoint(M_PI / 4);
        std::cout << shapes[i]->GetDerivative(M_PI / 4);
    }
    cout << endl;

    //======
    //4.Populate a second container that would contain only circles from the first container. Make sure the
    //second container shares (i.e. not clones) circles of the first one, e.g. via pointers.

    vector<shared_ptr<Shape>> circles;
    double sum = 0;
    for (shared_ptr<Shape> ptr_sh : shapes){
        cout << ptr_sh->GetType() << endl;
        if (dynamic_cast<Circle*>(ptr_sh.get())){
            circles.push_back(ptr_sh);
            sum+= ptr_sh->GetRadius(); // 6.Compute the total sum of radii of all curves in the second container.
        }
    }
    std::cout << "Size only circles container: " << circles.size() << std::endl;
    std::cout << "Summ all radius: " <<sum << std::endl;

    //======
    //5.Sort the second container in the ascending order of circles’ radii. That is, the first element has the
    //smallest radius, the last - the greatest.

    sort(circles.begin(), circles.end(), [](const auto& lhs, const auto rhs)
                                         {return lhs->GetRadius() < rhs->GetRadius() ;});

    for (int i = 0; i < circles.size(); ++i){
        cout << "Radius " << i << ": " << circles[i]->GetRadius() << endl;
    }



    return 0;
}
