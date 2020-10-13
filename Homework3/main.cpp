#include <iostream>
#include </Users/shaynabennett/Important_Files/math_tools.h>
#include </Users/shaynabennett/Important_Files/grid2d.h>
#include <omp.h>
#include <cmath>
#include <vector>
#include </Users/shaynabennett/Important_Files/setup.h>
#include </Users/shaynabennett/Important_Files/cf_2.h>
#include </Users/shaynabennett/Important_Files/sl_method.h>

using namespace std;

//___Test Interpolation Function___
class test_Function : public CF_2{
public:
    double operator()(double x, double y) const{
        return sin(x)+cos(y);
    }
};


//___Setup Velocity Stuff___
class velocity_X : public CF_2{
public:
    double operator()(double x, double y) const{
        return -y;
    }
};
class velocity_Y : public CF_2{
public:
    double operator()(double x, double y) const{
        return x;
    }
};


//___Main Code___
int main()
{
    //Setup grid size and boundaries
    int N = 101;
    double tf = 2*3.1415;
    double xmin = -1.;
    double xmax =  1.;
    double ymin = -1.;
    double ymax =  1.;


    //Set constructors
    Setup setup(N, N, xmin, xmax, ymin, ymax);
    Grid2D grid(N,N,xmin, xmax, ymin, ymax);
    test_Function test_function;
    math_tools MathT;
    SL_method SL;
    velocity_X vx;
    velocity_Y vy;

    //Setup initial vectors
    vector<double> test_function_n(N*N);

    //Setup mesh in X
    vector<double> MeshX = setup.meshgridX();

    //Setup mesh in Y
    vector<double> MeshY = setup.meshgridY();

    //Generate initial condition
    vector<double> t0 = setup.initial_cond2(MeshX, MeshY);


    //Calculate dt
    double dt = setup.calc_dt(1);

    //Setup Semi-Lagrangian Method
    SL.set_velX(vx);
    SL.set_velY(vy);
    SL.set_grid(grid);
    SL.set_solution(t0);
    SL.set_True(t0);
    SL.set_xd(MeshX);
    SL.set_yd(MeshY);

//___Check interpolation works___
//#pragma omp parallel for

//   for(int n=0; n<N*N; n++){
//       test_function_n[n] = test_function(grid.x_from_n(n), grid.y_from_n(n));
//   }

//    double x_intp = 1.5;
//    double y_intp = -1.;
//    double interp_value = MathT.bilinear_interpolation(grid, test_function_n, x_intp, y_intp);


//    cout<< abs(interp_value-test_function(x_intp, y_intp))<<endl;

//    cout << "Hello World!" << endl;


//___Check Runge-Kutta Works__
double k = 0.0;
    while(k<tf/2){
           // counter++;
           // auto STR = std::to_string(counter);
            SL.Runge_Kutta2(dt);
            SL.bilinear_interpolationENO();
            k=k+dt;
            cout << "Timestep at t= " <<k<< " complete" << endl;

    }
    cout << "Timesteps complete" << endl;

    SL.save_vtk("TrueRK2","EstRK7");
    // Test Interpolation
    return 0;
}
