#ifndef EXPORT_H_
#define EXPORT_H_

#include <iostream>
#include "Tree.h"
#include "Camera.h"

#ifdef ENABLE_CGAL

void export_stl(const class CGAL_Nef_polyhedron *root_N, std::ostream &output);
void export_off(const CGAL_Nef_polyhedron *root_N, std::ostream &output);
void export_dxf(const CGAL_Nef_polyhedron *root_N, std::ostream &output);
void export_png_with_cgal(const CGAL_Nef_polyhedron *root_N, Camera &c, std::ostream &output);
void export_png_with_opencsg(Tree &tree, Camera &c, std::ostream &output);
void export_png_with_throwntogether(Tree &tree, Camera &c, std::ostream &output);

#endif

#ifdef DEBUG
void export_stl(const class PolySet &ps, std::ostream &output);
#endif

#endif
