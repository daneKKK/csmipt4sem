#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("task1");

  double lc = 7e-3;

  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  gmsh::model::geo::addPoint(0.1, 0, 0, lc, 2);
  gmsh::model::geo::addPoint(0, 0.1, 0, lc, 3);
  gmsh::model::geo::addPoint(-0.1, 0, 0, lc, 4);
  gmsh::model::geo::addPoint(0, -0.1, 0, lc, 5);

  gmsh::model::geo::addPoint(0, 0, 0, lc, 11);
  gmsh::model::geo::addPoint(0.12, 0, 0, lc, 12);
  gmsh::model::geo::addPoint(0, 0.12, 0, lc, 13);
  gmsh::model::geo::addPoint(-0.12, 0.0, 0, lc, 14);
  gmsh::model::geo::addPoint(0, -0.12, 0, lc, 15);
  

  for (int i = 0; i < 3; i++) {
    gmsh::model::geo::addCircleArc(2 + i, 1, 3 + i, 1 + i);
  }
  gmsh::model::geo::addCircleArc(5, 1, 2, 4);


  for (int i = 0; i < 3; i++) {
    gmsh::model::geo::addCircleArc(12 + i, 11, 13 + i, 5 + i);
  }
  gmsh::model::geo::addCircleArc(15, 11, 12, 8);

  gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
  gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 2);
  gmsh::model::geo::addPlaneSurface({1, -2}, 1);

  std::vector<std::pair<int, int> > ov1;
  gmsh::model::geo::revolve({{2, 1}}, -0.5, 0, 0, 0, 1, 0, M_PI * 2 / 3, ov1);
  gmsh::model::geo::revolve({{2, 50}}, -0.5, 0, 0, 0, 1, 0, M_PI * 2 / 3, ov1);
  gmsh::model::geo::revolve({{2, 1}}, -0.5, 0, 0, 0, -1, 0, M_PI * 2 / 3, ov1);
  gmsh::model::geo::addPhysicalGroup(3, {1, 2, 3}, 1, "Thor");

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("task1.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}