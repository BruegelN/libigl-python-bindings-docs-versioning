#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/cgal/mesh_boolean.h>


const char* ds_mesh_boolean = R"igl_Qu8mg5v7(
MESH_BOOLEAN Compute boolean csg operations on "solid", consistently oriented
meshes.
      

Parameters
----------
VA  : #VA by 3 list of vertex positions of first mesh
FA  : #FA by 3 list of triangle indices into VA
VB  : #VB by 3 list of vertex positions of second mesh
FB  : #FB by 3 list of triangle indices into VB

Returns
-------
VC : #VC by 3 list of vertex positions of boolean result mesh
FC : #FC by 3 list of triangle indices into VC
J  : #FC list of indices into [FA;FA.rows()+FB] revealing "birth" facet
      
See also
--------
mesh_boolean_cork, intersect_other, remesh_self_intersections
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_int, dense_long, dense_longlong)
npe_arg(vb, npe_matches(va))
npe_arg(fb, npe_matches(fa))
npe_arg(type, std::string)


npe_begin_code()
  Eigen::MatrixXd va_copy = va.template cast<double>();
  Eigen::MatrixXd vb_copy = vb.template cast<double>();
  Eigen::MatrixXi fa_copy = fa.template cast<int>();
  Eigen::MatrixXi fb_copy = fb.template cast<int>();

  Eigen::MatrixXd vc_copy;
  Eigen::MatrixXi fc_copy;
  Eigen::VectorXi  j_copy;
  igl::copyleft::cgal::mesh_boolean(
    va_copy, 
    fa_copy,
    vb_copy,
    fb_copy,
    type,
    vc_copy,
    fc_copy,
     j_copy);

  EigenDenseLike<npe_Matrix_va> vc = vc_copy.cast<typename decltype(vc)::Scalar>();
  EigenDenseLike<npe_Matrix_fa> fc = fc_copy.cast<typename decltype(fc)::Scalar>();
  EigenDenseLike<npe_Matrix_fa>  j =  j_copy.cast<typename decltype( j)::Scalar>();
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));
npe_end_code()

