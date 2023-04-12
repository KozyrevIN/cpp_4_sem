#include <set>
#include <gmsh.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iostream>
#include <mutex>

class design
{
private:
    unsigned dim_1, dim_2;
    float r_inner, r_outer;
    float h_inner, h_outer;
    std::vector<std::vector<float>> coordinates;
public:
    design(unsigned dim_1, unsigned dim_2){
        this -> dim_1 = dim_1;
        this -> dim_1 = dim_2;
        r_inner = 1;
        r_outer = 10;
        h_inner = 0.2;
        h_outer = 0.1;

        std::vector<std::vector<float>> vect(dim_1);

        for(unsigned i = 0; i < this -> dim_1; ++i){
            std::vector<float> vect_tmp(this -> dim_2);
            vect[i] = vect_tmp;
            for(unsigned j = 0; j < this -> dim_2; ++j){
                vect[i][j] = h_inner*(dim_1 - i)/dim_1 + h_outer*i/dim_2;
            }
        }
    }

    void build_mesh(){
        gmsh::initialize();
        gmsh::model::add("wheel");

        double lc = 1e-2;

        std::vector<std::vector<int>> vertex_indices(dim_1, std::vector<int>(dim_2, 0));
        for(unsigned i = 0; i < dim_1; ++i){
            for(unsigned j = 0; j < dim_2; ++j){
                vertex_indices[i][j] = gmsh::model::geo::addPoint((r_outer*i/dim_1 + r_inner*(dim_1-i)/dim_1)*cos(2*j*M_PI/dim_2),
                                           (r_outer*i/dim_1 + r_inner*(dim_1-i)/dim_1)*cos(2*j*M_PI/dim_2),
                                           coordinates[i][j]);
            }
        }

        std::vector<int> face_indices((dim_1 - 1) * dim_2, 0);
        for(unsigned i = 0; i < dim_1 - 1; ++i){
            for(unsigned j = 0; j < dim_2; ++j){
                int line_1 = gmsh::model::geo::addLine(vertex_indices[i][j], vertex_indices[(i + 1) % dim_1][j]);
                int line_2 = gmsh::model::geo::addLine(vertex_indices[(i + 1) % dim_1][j], vertex_indices[(i + 1) % dim_1][(j + 1) % dim_2]);
                int line_3 = gmsh::model::geo::addLine(vertex_indices[(i + 1) % dim_1][(j + 1) % dim_2], vertex_indices[i][(j + 1) % dim_2]);
                int line_4 = gmsh::model::geo::addLine(vertex_indices[i][(j + 1) % dim_2], vertex_indices[i][j]);
                face_indices[dim_1 * i + j] = gmsh::model::geo::addSurfaceFilling({line_1, line_2, line_3, line_4});
            }
        }
        int surf_loop = gmsh::model::geo::addSurfaceLoop(face_indices);

        std::vector<std::pair<int, int> > extrusion;
        gmsh::model::geo::extrude({{2, surf_loop}}, 0, 0, -2 * h_inner, extrusion);
        gmsh::model::geo::synchronize();

        gmsh::model::mesh::generate(3);

        gmsh::write("wheel.msh");

        gmsh::finalize();
    }
};

int main()
{
    design wheel1 = design(10, 10);
    wheel1.build_mesh();
    return 0;
}
