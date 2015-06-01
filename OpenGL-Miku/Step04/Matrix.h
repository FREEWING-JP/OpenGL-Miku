#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

/* 行列の割り当て */
float *alloc_matrix(void);

/* 行列の解放 */
void free_matrix(float *mat);

/* 行列のクリア */
void clear_matrix(float *mat);

/* 単位行列の生成 */
void set_identity_matrix(float *mat);

/* 透視変換行列の生成 */
void set_perspective_matrix(float *mat,
    float fov, float aspect, float near, float far);

/* 視野変換行列の生成 */
void set_lookat_matrix(float *mat,
    float eye_x, float eye_y, float eye_z,
    float center_x, float center_y, float center_z,
    float up_x, float up_y, float up_z);

/* 行列の積 */
void multiply_matrix(float *result, float *mat1, float *mat2);

#endif
