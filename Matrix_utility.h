#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Utility.h"

namespace Math
{
	template<typename T>
	Math::Matrix<4, 4, T> frustum(const T& left, const T& right, const T& bottom, const T& top, const T& nearVal, const T& farVal);

	template<typename T>
	Math::Matrix<4, 4, T> infinitePerspective(T fovy, T aspect, T zNear);

	template<typename T>
	Math::Matrix<4, 4, T> lookAtRH(const Math::Vector<3, T>& eye, const Math::Vector<3, T>& center, const Math::Vector<3, T>& up)
	{
		const Math::Vector<3, T> f((center - eye).normalized());
		const Math::Vector<3, T> s(normalize(cross(f, up)));
		const Math::Vector<3, T> u(cross(s, f));

		Math::Matrix<4, 4, T>  Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] = dot(f, eye);
		return Result;
	}

	template<typename T>
	Math::Matrix<4, 4, T> lookAtLH(const Math::Vector<3, T>& eye, const Math::Vector<3, T>& center, const Math::Vector<3, T>& up)
	{
		const Math::Vector<3, T> f(normalize(center - eye));
		const Math::Vector<3, T> s(normalize(cross(up, f)));
		const Math::Vector<3, T> u(cross(f, s));

		Math::Matrix<4, 4, T> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = f.x;
		Result[1][2] = f.y;
		Result[2][2] = f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] = -dot(f, eye);
		return Result;
	}

	template<typename T>
	Math::Matrix<4, 4, T> lookAt(const Math::Vector<3, T>& eye, const Math::Vector<3, T>& center, const Math::Vector<3, T>& up)
	{
#       if (CURRENT_COORDINATE_SYSTEM & LEFT_HAND)
		return lookAtLH(eye, center, up);
#       else
		return lookAtRH(eye, center, up);
#       endif
	}

	template<typename T>
	Math::Matrix<4, 4, T> ortho(const T& left, const T& right, const T& bottom, const T& top)
	{
		Math::Matrix<4, 4, T> Result(static_cast<T>(1));
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = -static_cast<T>(1);
		Result[3][0] = -(right + left) / (right - left);
		Result[3][1] = -(top + bottom) / (top - bottom);
		return Result;
	}

	template<typename T>
	Math::Matrix<4, 4, T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& zNear, const T& zFar);

	template<typename T>
	Math::Matrix<4, 4, T> perspective(const T& fovy, const T& aspect, const T& zNear, const T& zFar)
	{
		//( CURRENT_CLIP_RANGE & CLIP_RANGE_NEGATIVE_ONE_TO_ONE ) (CURRENT_COORDINATE_SYSTEM & LEFT_HAND)

#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
		return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
		return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
		return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
		return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename T>
	Math::Matrix<4, 4, T> perspective(const T& fov, const T& width, const T& height, const T& zNear, const T& zFar);

	/*
	template<typename T, typename U>
	Math::Matrix<4, 4, T> pickMatrix(const Math::Vector<2, T>& center, const Math::Vector<2, T>& delta, const Math::Vector<4, U>& viewport);
	*/



	template<typename T, typename U>
	Math::Vector<3, T> projectZeroToOne(const Math::Vector<3, T>& obj, const Math::Matrix<4, 4, T>& model, const Math::Matrix<4, 4, T>& proj, const Math::Vector<4, U>& viewport)
	{
		Math::Vector<4, T> tmp = Math::Vector<4, T>(obj, static_cast<T>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp.x = tmp.x * static_cast<T>(0.5) + static_cast<T>(0.5);
		tmp.y = tmp.y * static_cast<T>(0.5) + static_cast<T>(0.5);

		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return Math::Vector<3, T>(tmp);
	}

	template<typename T, typename U>
	Math::Vector<3, T> projectNOneToOne(const Math::Vector<3, T>& obj, const Math::Matrix<4, 4, T>& model, const Math::Matrix<4, 4, T>& proj, const Math::Vector<4, U>& viewport)
	{
		Math::Vector<4, T> tmp = Math::Vector<4, T>(obj, static_cast<T>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * static_cast<T>(0.5) + static_cast<T>(0.5);
		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return Math::Vector<3, T>(tmp);
	}

	template<typename T, typename U>
	Math::Vector<3, T> project(const Math::Vector<3, T>& obj, const Math::Matrix<4, 4, T>& model, const Math::Matrix<4, 4, T>& proj, const Math::Vector<4, U>& viewport)
	{
#		if CURRENT_CLIP_RANGE & CLIP_RANGE_NEGATIVE_ONE_TO_ONE
		return projectZeroToOne(obj, model, proj, viewport);
#		else
		return projectNOneToOne(obj, model, proj, viewport);
#		endif
	}

	template<typename T>
	Math::Matrix<4, 4, T> rotate(const Math::Matrix<4, 4, T>& m, const T& angle, const Math::Vector<3, T>& v)
	{
		const T a = angle;
		const T c = Math::CosInRadian(a);
		const T s = Math::SinInRadian(a);

		Math::Vector<3, T> axis(v.normalized());
		Math::Vector<3, T> temp((T(1) - c) * axis);

		Math::Matrix<4, 4, T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		Math::Matrix<4, 4, T> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	Math::Matrix<4, 4, T> scale(const Math::Matrix<4, 4, T>& m, const Math::Vector<3, T>& v)
	{
		Math::Matrix<4, 4, T> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	Math::Matrix<4, 4, T> translate(const Math::Matrix<4, 4, T>& m, const Math::Vector<3, T>& v)
	{
		Math::Matrix<4, 4, T> Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}

	/*
	template<typename T>
	Math::Matrix<4, 4, T> tweakedInfinitePerspective(T fovy, T aspect, T zNear);

	template<typename T, typename U>
	Math::Vector<3, T> unProject(const Math::Vector<3, T>& win, const Math::Matrix<4, 4, T>& model, const Math::Matrix<4, 4, T>& proj, const Math::Vector<4, U>& viewport);
	*/
}