#ifndef MATRIX_H_
#define MATRIX_H_

void mat_identity(float *mat);
void mat_copy(float *dest, float *src);
void mat_mul(float *res, float *m);
void mat_translate(float *mat, float x, float y, float z);
void mat_rotate(float *mat, float angle, float x, float y, float z);
void mat_perspective(float *mat, float vfov_deg, float aspect, float znear, float zfar);

void mat_transform(float *mat, float *vec);


#endif	/* MATRIX_H_ */
