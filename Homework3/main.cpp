#include <iostream>
#include </Users/shaynabennett/MATH233_HOMEWORK/Important_Files/math_tools.h>
#include </Users/shaynabennett/MATH233_HOMEWORK/Important_Files/grid2d.h>
#include <omp.h>
#include <cmath>
#include <vector>
#include </Users/shaynabennett/MATH233_HOMEWORK/Important_Files/setup.h>
#include </Users/shaynabennett/MATH233_HOMEWORK/Important_Files/cf_2.h>
#include </Users/shaynabennett/MATH233_HOMEWORK/Important_Files/sl_method.h>

using namespace std;

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
    int N = 201;
    double rtf = 0.25;
    double tf = 2*3.1415;
    double xmin = -1.;
    double xmax =  1.;
    double ymin = -1.;
    double ymax =  1.;


    //Set constructors
    Setup setup(N, N, xmin, xmax, ymin, ymax);
    Grid2D grid(N,N,xmin, xmax, ymin, ymax);
    SL_method SL;
    velocity_X vx;
    velocity_Y vy;

    //Setup mesh in X
    vector<double> MeshX = setup.meshgridX();

    //Setup mesh in Y
    vector<double> MeshY = setup.meshgridY();

    //Generate initial condition
    vector<double> t0 = setup.initial_condREN(MeshX, MeshY);
    //Generate signed distance function
    vector<double> t1 = setup.initial_cond2(MeshX, MeshY);
    //Generate dt for reinitialization
    double rdt = grid.get_dx()/10;


    //Calculate dt
    double dt = setup.calc_dt(1);

    //Setup Semi-Lagrangian Method
    SL.set_velX(vx);
    SL.set_velY(vy);
    SL.set_grid(grid);
    SL.set_solution(t0);
    SL.set_True(t1);
    SL.set_xd(MeshX);
    SL.set_yd(MeshY);


//___Check Semi-Lagrangian Method Works__
//    int counter = 0;
//    double k = 0.0;
//    while(k<dt)
//    {
//        // counter++;
//        auto STR = std::to_string(counter);
//        SL.Runge_Kutta2(dt);
//        SL.bilinear_interpolationENO();
//        SL.save_vtk("TrueRKT_a"+STR+".vtk","EstRK_a"+STR+".vtk");
//        k=k+dt;
//        counter++;
//        cout << "Timestep at t= " <<k<< " complete" << endl;

//    }
//    cout << "Timesteps complete" << endl;
//    return 0;


//___Check reinitialization works___

//    double q = 0.0;
//  //  SL.save_vtk("Correct_Problem1_b.vtk","Function_Problem2_b.vtk");
//    while (q<rtf)
//    {
//        SL.reinitialize(dt/2);
//        q = q+(dt/2);
//        cout << "Timestep at t= " <<q<< " complete" << endl;
//    }
//    SL.save_vtk("TrueRKT_Reint_f.vtk","Reinitialized_f.vtk");
//    cout << "Timesteps complete" << endl;

//__________________________________________________________________
//___Put them together___
int counter = 0;
//int counter2;
double k = 0.0;
int q;
    while(k<tf){
           // counter++;
            auto STR = std::to_string(counter);
            q = 0;
           // counter2 = 0;
            while (q<20)
            {
                //auto STR2 = std::to_string(counter2);
                SL.reinitialize(rdt); //do not use dt - it will blow up
                    q++;
                    //SL.save_vtk("TrueRKT_Reint_c"+STR2+".vtk","EstRK_Reint_c"+STR2+".vtk");
                   // counter2++;
            }
            SL.Runge_Kutta2(dt);
            SL.bilinear_interpolationENO();
            SL.save_vtk("TrueLVS_b"+STR+".vtk","EstLVS_b"+STR+".vtk");
            k=k+dt;
            counter++;
            cout << "Timestep at t= " <<k<< " complete" << endl;

    }
    cout << "Timesteps complete" << endl;


//___The End___

    return 0;
}



