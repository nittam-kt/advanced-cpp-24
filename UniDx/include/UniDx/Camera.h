#pragma once
#include <SimpleMath.h>

#include "Behaviour.h"


namespace UniDx {

// --------------------
// Cameraクラス
// --------------------
class Camera : public Behaviour
{
public:
    static Camera* main;

    float fov = 60.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;

    Matrix GetViewMatrix() const;

    Matrix GetProjectionMatrix(float aspect) const {
        using namespace DirectX;
        return XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspect, nearClip, farClip);
    }

    // 定数バッファ更新
    void UpdateConstantBuffer();

protected:
    virtual void OnEnable() override;
    virtual void OnDisable() override;

    ComPtr<ID3D11Buffer> constantBufferPerCamera; // カメラごとにGPUで共通利用する定数バッファ
};

} // namespace UniDx
