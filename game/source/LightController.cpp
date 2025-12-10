#include "LightController.h"

#include <UniDx/Input.h>

using namespace UniDx;


void LightController::OnEnable()
{
    auto pos = transform->localPosition.get();
    // 水平面（XZ平面）上の距離
    float planar = std::sqrt(pos.x * pos.x + pos.z * pos.z);
    // 原点からの距離
    length = pos.Length();
    // yaw: Y軸周りの回転（Z軸正方向を基準とする、右手系）
    yaw = std::atan2(pos.x, pos.z);
    // pitch: X軸周りの回転（水平面からの上下角）
    pitch = std::atan2(pos.y, planar);
}


void LightController::Update()
{
    const float angleSpeed = 2.0f;
    Quaternion rot;
    if (Input::GetKey(Keyboard::O))
    {
        yaw += angleSpeed * Time::deltaTime;
    }
    if (Input::GetKey(Keyboard::P))
    {
        yaw -= angleSpeed * Time::deltaTime;
    }
    rot = Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
    transform->localRotation = rot;
    float planar = length * std::cos(pitch); // XZ平面上の距離
    float x = std::sin(yaw) * planar;
    float z = std::cos(yaw) * planar;
    transform->localPosition = Vector3(x, std::sin(pitch) * length, z);
}
