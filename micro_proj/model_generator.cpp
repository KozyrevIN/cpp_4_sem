#include <set>
#include <gmsh.h>
#include <vector>
#include <cmath>
#include <iostream>

int CreateTorus(float r1, float r2, float lc)
{
    //points
    int point[9]; int center_point[3];
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
             point[3*i + j] = gmsh::model::geo::addPoint(cos(2*i*M_PI / 3)*(r1 + r2*cos(2*j*M_PI / 3)),
                                                        sin(2*i*M_PI / 3)*(r1 + r2*cos(2*j*M_PI / 3)),
                                                        r2*sin(2*j*M_PI / 3), lc);
        }
        center_point[i] = gmsh::model::geo::addPoint(cos(2*i*M_PI/ 3)*r1, sin(2*i*M_PI / 3)*r1, 0, lc);
    }

    //arcs
    int arc[9];
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
            arc[3*i + j] = gmsh::model::geo::addCircleArc(point[3*i + j], center_point[i],  point[3*i + ((j + 1) % 3)]);
    }

    //surfaces
    std::vector<int> surf;
    surf.assign(9, 0);
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::vector<std::pair<int, int>> ov;
            gmsh::model::geo::revolve({{1, arc[3*i + j]}}, 0, 0, 0, 0, 0, 1, 2*M_PI / 3, ov, {20});
            surf[3*i + j] = ov[1].second;
            std::cout << surf[3*i + j] << '\n';
        }
    }

    return gmsh::model::geo::addSurfaceLoop(surf);
}

int CreateSurface(int argc, char **argv)
{
  gmsh::initialize();
  gmsh::model::add("wheel");

  float r0 = 0.1, r1 = 1, h0 = 0.1, h1 = 0.05;

  int n = 10, //number of radial circles
      m = 10; //number of verticies in each circle

  int* points = new int [2*n*m];
  int* central_points = new int [2*n];

  //points
  for (int i = 0; i < n; ++i){
      central_points[i] = gmsh::model::geo::addPoint(0, 0, (h0*(n-i) + h1*i)/n);
      central_points[n + i] = gmsh::model::geo::addPoint(0, 0, (h0*(n-i) + h1*i)/n);
      for (int j = 0; j < m; ++j){
          points[n * i + j] = gmsh::model::geo::addPoint(cos(2*j*M_PI/m), sin(2*j*M_PI/m), (h0*(n-i) + h1*i)/n);
          points[n*m + n * i + j] = gmsh::model::geo::addPoint(cos(2*j*M_PI/m), sin(2*j*M_PI/m), -(h0*(n-i) + h1*i)/n);
      }
  }

  //arcs
  int* arcs = new int [4*n*m];
  for (int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j){
            arcs[n*i + j] = gmsh::model::geo::addCircleArc(points[n*i + j], central_points[i],  points[n*i + ((j + 1) % m)]);
            arcs[m*n + n*i + j] = gmsh::model::geo::addCircleArc(points[n*m + n*i + j], central_points[i],  points[n*i + ((j + 1) % m)]);

            arcs[n*i + j] = gmsh::model::geo::addCircleArc(points[n*i + j], central_points[i],  points[n*i + ((j + 1) % m)]);

            ]
        }

    }

  gmsh::model::geo::addVolume({t1, -t2});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("ex_0.3.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}
