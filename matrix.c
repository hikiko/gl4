#include <string.h>
#include <math.h>
#include "matrix.h"

void mat_identity(float *mat)
{
	memset(mat, 0, 16 * sizeof *mat);
	mat[0] = mat[5] = mat[10] = mat[15] = 1.0f;
}

void mat_copy(float *dest, float *src)
{
	memcpy(dest, src, 16 * sizeof *dest);
}

#define M(i,j)	(((i) << 2) + (j))
void mat_mul(float *res, float *m2)
{
	int i, j;
	float m1[16];

	memcpy(m1, res, sizeof m1);

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			*res++ = m1[M(0,j)] * m2[M(i,0)] +
				m1[M(1,j)] * m2[M(i,1)] +
				m1[M(2,j)] * m2[M(i,2)] +
				m1[M(3,j)] * m2[M(i,3)];
		}
	}
}

void mat_translate(float *mat, float x, float y, float z)
{
	float m[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	m[12] = x;
	m[13] = y;
	m[14] = z;
	mat_mul(mat, m);
}

void mat_rotate(float *mat, float deg, float x, float y, float z)
{
	float m[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	float angle = M_PI * deg / 180.0f;
	float sina = sin(angle);
	float cosa = cos(angle);
	float one_minus_cosa = 1.0f - cosa;
	float nxsq = x * x;
	float nysq = y * y;
	float nzsq = z * z;

	m[0] = nxsq + (1.0f - nxsq) * cosa;
	m[4] = x * y * one_minus_cosa - z * sina;
	m[8] = x * z * one_minus_cosa + y * sina;
	m[1] = x * y * one_minus_cosa + z * sina;
	m[5] = nysq + (1.0 - nysq) * cosa;
	m[9] = y * z * one_minus_cosa - x * sina;
	m[2] = x * z * one_minus_cosa - y * sina;
	m[6] = y * z * one_minus_cosa + x * sina;
	m[10] = nzsq + (1.0 - nzsq) * cosa;
	m[15] = 1.0f;

	mat_mul(mat, m);
}

void mat_perspective(float *mat, float vfov_deg, float aspect, float znear, float zfar)
{
	float m[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	float vfov = M_PI * vfov_deg / 180.0f;
	float s = 1.0f / tan(vfov * 0.5f);
	float range = znear - zfar;

	m[0] = s / aspect;
	m[5] = s;
	m[10] = (znear + zfar) / range;
	m[11] = -1.0f;
	m[14] = 2.0f * znear * zfar / range;

	mat_mul(mat, m);
}

void mat_transform(float *mat, float *vec)
{
	float x = mat[0] * vec[0] + mat[4] * vec[1] + mat[8] * vec[2] + mat[12];
	float y = mat[1] * vec[0] + mat[5] * vec[1] + mat[9] * vec[2] + mat[13];
	float z = mat[2] * vec[0] + mat[6] * vec[1] + mat[10] * vec[2] + mat[14];

	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}
