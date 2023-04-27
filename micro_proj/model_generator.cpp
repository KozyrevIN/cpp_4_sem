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

int CreateSurface(int argc, char **argv, int n, int m, float* heighs)
{
  gmsh::initialize();
  gmsh::model::add("wheel");

  float r_0 = 0.058, r_1 = 0.7366;, h0 = 0.1, h1 = 0.05;

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

class Mesh
{
public:
    Mesh(int size_c, int size_r, float inner_r, float outer_r)
    {
        This->size_c = size_c;
        This->size_r = size_r;
        This->inner_r = inner_r;
        This->outer_r = outer_r;

        height_map = std::vector(std::vector(0, size_r), size_c);
        float inner_h = inner_r;
        float outer_h = inner_r / 2;

        for (int i = 0; i < size_c){
            for (int j = 0; j < size_r){
                height_map[i][j] = i / (size_c - 1) * outer_h  + (size_c - 1 - i) / (size_c - 1) * inner_h;
            }
        }
    };

    Mesh(int size_c; //amount of circular circles in a mesh
    int size_r; //amount of radial lines in a mesh
    std::vector<std::vector<float>> height_map; 
    float inner_r;
    float outer_r;)
    {
        This->size_c = size_c;
        This->size_r = size_r;
        This->height_map = height_map; 
        This->inner_r = inner_r;
        This->outer_r = outer_r;
    };

    void GenerateOutput()
    {
        gmsh::initialize();
        gmsh::model::add("wheel");

        std::vector<std::vector<int>> points = std::vector(std::vector(0, size_r), size_c)

        //points
        for (int i = 0; i < size_c; ++i){
            for (int j = 0; j < size_r; ++j){
                points[i][j] = gmsh::model::geo::addPoint(cos(2*j*M_PI/size_r), sin(2*j*M_PI/size_r), height_map[i][j]);
                points[i][j] = gmsh::model::geo::addPoint(cos(2*j*M_PI/size_r), sin(2*j*M_PI/size_r), -(h0*(n-i) + h1*i)/n);
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
        }

    }

  gmsh::model::geo::addVolume({t1, -t2});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("ex_0.3.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();
    }

private:
    int size_c; //amount of circular circles in a mesh
    int size_r; //amount of radial lines in a mesh
    std::vector<std::vector<float>> height_map; 
    float inner_r;
    float outer_r;
}