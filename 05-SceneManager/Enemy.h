#pragma once
#include "GameObject.h"

class CEnemy : public CGameObject {
protected:
    float start_x, start_y;
    float bbox_width, bbox_height;

    bool isActivated = false;
    bool isOutOfRange = false;
    bool visible = true;

    virtual void OnActivated() = 0;
    virtual int GetWaitingState() = 0;

public:
    void SetStartPosition(float x, float y) { start_x = x; start_y = y; }
    void SetBoundingBoxSize(float w, float h) { bbox_width = w; bbox_height = h; }

    void SetVisible(bool v) { visible = v; }
    bool IsVisible() const { return visible; }

    void UpdateActivation(float cam_x, float cam_y, float cam_w, float cam_h);
};