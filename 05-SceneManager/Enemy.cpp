#include "Enemy.h"
#include "Game.h"

void CEnemy::UpdateActivation(float cam_x, float cam_y, float cam_w, float cam_h) {
    float cam_center_x = cam_x + cam_w / 2;
    float cam_center_y = cam_y + cam_h / 2;

    float active_left = start_x - 200;
    float active_right = start_x + 200;
    float active_top = start_y - 200;
    float active_bottom = start_y + 200;

    bool isCameraNearStart = cam_center_x >= active_left && cam_center_x <= active_right &&
        cam_center_y >= active_top && cam_center_y <= active_bottom;

    float cam_right = cam_x + cam_w;
    float cam_bottom = cam_y + cam_h;

    bool isInCamera = !(x + bbox_width / 2 < cam_x ||
        x - bbox_width / 2 > cam_right ||
        y + bbox_height / 2 < cam_y ||
        y - bbox_height / 2 > cam_bottom);

    SetVisible(isInCamera);

    if (!isCameraNearStart && !isInCamera) {
        isActivated = false;
        isOutOfRange = true;
        x = start_x;
        y = start_y;
        SetState(GetWaitingState());
        vx = vy = 0;
        return;
    }

    if (isOutOfRange && !isInCamera) {
        x = start_x;
        y = start_y;
        SetState(GetWaitingState());
        vx = vy = 0;
        isOutOfRange = false;
        return;
    }

    isActivated = true;

    if (state == GetWaitingState() && isActivated) {
        OnActivated();
    }
}