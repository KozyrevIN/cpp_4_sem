// This code conforms with the UFC specification version 2018.2.0.dev0
// and was automatically generated by FFCx version 0.7.0.dev0.
//
// This code was generated with the following options:
//
//  {'assume_aligned': -1,
//   'epsilon': 1e-14,
//   'output_directory': '.',
//   'padlen': 1,
//   'profile': False,
//   'scalar_type': 'double',
//   'table_atol': 1e-09,
//   'table_rtol': 1e-06,
//   'tabulate_tensor_void': False,
//   'ufl_file': ['/home/tea_shroom/Programming/cpp_4_sem/hyperelasticity/hyperelasticity.py'],
//   'verbosity': 30,
//   'visualise': False}


#pragma once

#include <ufcx.h>

#ifdef __cplusplus
extern "C" {
#endif

extern ufcx_finite_element element_ef833ef3ebbfa4eaf47d934f0b21758cc32f7406;

extern ufcx_finite_element element_816e6054a3233e7d3d34e081edcdfca61285a187;

extern ufcx_dofmap dofmap_ef833ef3ebbfa4eaf47d934f0b21758cc32f7406;

extern ufcx_dofmap dofmap_816e6054a3233e7d3d34e081edcdfca61285a187;

extern ufcx_integral integral_69f2b982ef48a6c30f0ac1f934e9c8ccdd9a7312;

extern ufcx_integral integral_3e85a1ecf56295d91d8d2aeec076af8eeeec80fd;

extern ufcx_form form_c6044fe317d161e9b543a0ce2ae061f53eba0da9;

// Helper used to create form using name which was given to the
// form in the UFL file.
// This helper is called in user c++ code.
//
extern ufcx_form* form_hyperelasticity_F_form;

// Helper used to create function space using function name
// i.e. name of the Python variable.
//
ufcx_function_space* functionspace_form_hyperelasticity_F_form(const char* function_name);

extern ufcx_form form_2c2c036a9167d0a9f4a04c5402427cf3b9270712;

// Helper used to create form using name which was given to the
// form in the UFL file.
// This helper is called in user c++ code.
//
extern ufcx_form* form_hyperelasticity_J_form;

// Helper used to create function space using function name
// i.e. name of the Python variable.
//
ufcx_function_space* functionspace_form_hyperelasticity_J_form(const char* function_name);

extern ufcx_expression expression_f3d70d0fedadbb765c97c41874f1d07c9960766c;

// Helper used to create expression using name which was given to the
// expression in the UFL file.
// This helper is called in user c++ code.
//
extern ufcx_expression* expression_hyperelasticity_sigma;

#ifdef __cplusplus
}
#endif
