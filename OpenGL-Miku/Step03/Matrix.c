#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*==============================*
** 行列の割り当て
**==============================*/
float *alloc_matrix(void)
{
    float *mat = malloc(sizeof(float) * 16);
    if (!mat) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    return mat;
}

/*==============================*
** 行列の解放
**==============================*/
void free_matrix(float *mat)
{
    free(mat);
}

/*==============================*
** 行列のクリア
**==============================*/
void clear_matrix(float *mat)
{
    int i;

    for (i = 0; i < 16; i++) {
        mat[i] = 0.0f;
    }
}

/*==============================*
** 単位行列の生成
**==============================*/
void set_identity_matrix(float *mat)
{
    int i;

    clear_matrix(mat);

    for (i = 0; i < 4; i++) {
        mat[i * 4 + i] = 1.0f;
    }
}

/*==============================*
** 透視変換行列の生成
**==============================*/
void set_perspective_matrix(float *mat,
    float fov, float aspect, float near, float far)
{
    float f;
    
    clear_matrix(mat);

    f = 1.0f / tan(fov / 2.0f);
    
    mat[0 * 4 + 0] = f / aspect;
    mat[1 * 4 + 1] = f;
    mat[2 * 4 + 2] = (far + near) / (near - far);
    mat[2 * 4 + 3] = -1.0f;
    mat[3 * 4 + 2] = (2.0f * far * near) / (near - far);
}

/*==============================*
** 視野変換行列の生成
**==============================*/
void set_lookat_matrix(float *mat,
    float eye_x, float eye_y, float eye_z,
    float center_x, float center_y, float center_z,
    float up_x, float up_y, float up_z)
{
    float tmp_x, tmp_y, tmp_z;
    float d;
    float f_x, f_y, f_z;
    float s_x, s_y, s_z;
    float u_x, u_y, u_z;

    clear_matrix(mat);

    tmp_x = center_x - eye_x;
    tmp_y = center_y - eye_y;
    tmp_z = center_z - eye_z;

    d = sqrtf(tmp_x * tmp_x + tmp_y * tmp_y + tmp_z * tmp_z);
    f_x = tmp_x / d;
    f_y = tmp_y / d;
    f_z = tmp_z / d;

    tmp_x = f_y * up_z - f_z * up_y;
    tmp_y = f_z * up_x - f_x * up_z;
    tmp_z = f_x * up_y - f_y * up_x;

    d = sqrtf(tmp_x * tmp_x + tmp_y * tmp_y + tmp_z * tmp_z);
    s_x = tmp_x / d;
    s_y = tmp_y / d;
    s_z = tmp_z / d;

    u_x = s_y * f_z - s_z * f_y;
    u_y = s_z * f_x - s_x * f_z;
    u_z = s_x * f_y - s_y * f_x;

    mat[0 * 4 + 0] = s_x;
    mat[1 * 4 + 0] = s_y;
    mat[2 * 4 + 0] = s_z;

    mat[0 * 4 + 1] = u_x;
    mat[1 * 4 + 1] = u_y;
    mat[2 * 4 + 1] = u_z;

    mat[0 * 4 + 2] = -f_x;
    mat[1 * 4 + 2] = -f_y;
    mat[2 * 4 + 2] = -f_z;

    mat[3 * 4 + 0] = -(s_x * eye_x + s_y * eye_y + s_z * eye_z);
    mat[3 * 4 + 1] = -(u_x * eye_x + u_y * eye_y + u_z * eye_z);
    mat[3 * 4 + 2] = f_x * eye_x + f_y * eye_y + f_z * eye_z;

    mat[3 * 4 + 3] = 1.0f;
}

/*==============================*
** 行列の積
**==============================*/
void multiply_matrix(float *result, float *mat1, float *mat2)
{
    int i, j, k;

    clear_matrix(result);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                result[j * 4 + i] += mat1[k * 4 + i] * mat2[j * 4 + k];
            }
        }
    }
}
