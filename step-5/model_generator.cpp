#include <set>
#include <gmsh.h>
#include <vector>
#include <cmath>
#include <iostream>

class Mesh
{
public:
    Mesh(float inner_r, float outer_r, int n, float dist, float r): inner_r{inner_r}, outer_r{outer_r}, n{n}, dist{dist}, r{r} {};

    void GenerateOutput()
    {
        gmsh::initialize();
        gmsh::model::add("wheel");
        double lc = 5e-1;
        
        //center hole points
        int center = gmsh::model::geo::addPoint(0, 0, 0);
        std::vector<int> central_points = std::vector{n + 2, 0};
        for (int i = 2; i < n + 2; ++i){
            central_points[i] = gmsh::model::geo::addPoint(dist * cos(2 * i * M_PI / n), dist * sin(2 * i * M_PI / n), 0, lc);
        }
        central_points[0] = gmsh::model::geo::addPoint(0, 0, 0); central_points[1] = gmsh::model::geo::addPoint(0, 0, 0, lc);

        //points forming each hole
        std::vector<std::vector<int>> edge_points = std::vector{n + 2, std::vector{3, 0}};
        for (int i = 2; i < n + 2; ++i){
            for (int j = 0; j < 3; ++j){
                edge_points[i][j] = gmsh::model::geo::addPoint(dist * cos(2*i*M_PI / n) + r * sin(2*j*M_PI / 3),
                                                               dist * sin(2*i*M_PI / n) + r * cos(2*j*M_PI / 3) , 0, lc);
            }
        }

        //points forming wheel
        for (int j = 0; j < 3; ++j){
            edge_points[0][j] = gmsh::model::geo::addPoint(outer_r * sin(2*j*M_PI / 3),
                                                               outer_r * cos(2*j*M_PI / 3) , 0, lc);
        }
        for (int j = 0; j < 3; ++j){
            edge_points[1][j] = gmsh::model::geo::addPoint(inner_r * sin(2*j*M_PI / 3),
                                                               inner_r * cos(2*j*M_PI / 3) , 0, lc);
        }
       
        //creating arcs
        std::vector<int> circles = std::vector(n + 2, 0);
        for (int i = 0; i < n + 2; ++i){
            std::cout << "point " << i << " done" << '\n';
            int tmp_1 = gmsh::model::geo::addCircleArc(edge_points[i][0], central_points[i], edge_points[i][1]);
            int tmp_2 = gmsh::model::geo::addCircleArc(edge_points[i][1], central_points[i], edge_points[i][2]);
            int tmp_3 = gmsh::model::geo::addCircleArc(edge_points[i][2], central_points[i], edge_points[i][0]);
            circles[i] = gmsh::model::geo::addCurveLoop({tmp_1, tmp_2, tmp_3});
        }

        int surf = gmsh::model::geo::addPlaneSurface(circles);
        gmsh::model::geo::synchronize();
        gmsh::model::mesh::setRecombine(2, surf);
        gmsh::model::mesh::generate(2);
        gmsh::write("wheel.msh");
        gmsh::finalize();
    }

private:
    float inner_r;
    float outer_r;
    int n; 
    float dist; 
    float r;
};