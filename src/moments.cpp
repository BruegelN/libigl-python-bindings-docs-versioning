#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/moments.h>

const char *ds_moments = R"igl_Qu8mg5v7(
Computes the moments of mass for a solid object bound by a triangle mesh.
 
Parameters
----------
   V  #V by dim list of rest domain positions
   F  #F by 3 list of triangle indices into V
Returns
-------
   m0  zeroth moment of mass, total signed volume of solid.
   m1  first moment of mass, center of mass times total mass
   m2  second moment of mass, moment of inertia with center of mass as reference point

)igl_Qu8mg5v7";

npe_function(moments)
npe_doc(ds_moments)

npe_arg(V, dense_float, dense_double)
npe_arg(F, dense_int, dense_long, dense_longlong)

npe_begin_code()
  assert_valid_3d_tri_mesh(V, F);
  EigenDenseLike<npe_Matrix_V> m1;
  EigenDenseLike<npe_Matrix_V> m2;
  double m0;
  igl::moments(V, F, m0, m1, m2);
  return std::make_tuple(m0,npe::move(m1),npe::move(m2));
npe_end_code()

