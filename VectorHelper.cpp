#include "VectorHelper.hpp"
#include <sstream>


using namespace std;
using namespace DirectX;

namespace Library
{
	const XMFLOAT2 Vector2Helper::Zero = XMFLOAT2(0.0f, 0.0f);
	const XMFLOAT2 Vector2Helper::One = XMFLOAT2(1.0f, 1.0f);

	string Vector2Helper::ToString(const XMFLOAT2& vector)
	{
		stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << "}";

		return stream.str();
	}

	const XMFLOAT3 Vector3Helper::Zero = XMFLOAT3(0.0f, 0.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::One = XMFLOAT3(1.0f, 1.0f, 1.0f);
	const XMFLOAT3 Vector3Helper::Forward = XMFLOAT3(0.0f, 0.0f, -1.0f);
	const XMFLOAT3 Vector3Helper::Backward = XMFLOAT3(0.0f, 0.0f, 1.0f);
	const XMFLOAT3 Vector3Helper::Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Down = XMFLOAT3(0.0f, -1.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 Vector3Helper::Left = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	string Vector3Helper::ToString(const XMFLOAT3& vector)
	{
		stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";

		return stream.str();
	}

	XMFLOAT3 Vector3Helper::ToFloat3(const XMFLOAT4& vector)
	{
		return XMFLOAT3(vector.x, vector.y, vector.z);
	}

	const XMFLOAT4 Vector4Helper::Zero = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	const XMFLOAT4 Vector4Helper::One = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	string Vector4Helper::ToString(const XMFLOAT4& vector)
	{
		stringstream stream;

		stream << "{" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "}";

		return stream.str();
	}
}