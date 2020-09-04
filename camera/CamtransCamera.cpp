/**
 * @file   CamtransCamera.cpp
 *
 * This is the perspective camera class you will need to fill in for the Camtrans lab.  See the
 * lab handout for more details.
 */

#include "CamtransCamera.h"
#include <Settings.h>

CamtransCamera::CamtransCamera()
{
    // @TODO: [CAMTRANS] Fill this in...
}

void CamtransCamera::setAspectRatio(float a)
{
    // @TODO: [CAMTRANS] Fill this in...

}

glm::mat4x4 CamtransCamera::getProjectionMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getViewMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getScaleMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::mat4x4();
}

glm::mat4x4 CamtransCamera::getPerspectiveMatrix() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::mat4x4();
}

glm::vec4 CamtransCamera::getPosition() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::vec4();
}

glm::vec4 CamtransCamera::getLook() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::vec4();
}

glm::vec4 CamtransCamera::getUp() const {
    // @TODO: [CAMTRANS] Fill this in...
    return glm::vec4();
}

float CamtransCamera::getAspectRatio() const {
    // @TODO: [CAMTRANS] Fill this in...
    return 0;
}

float CamtransCamera::getHeightAngle() const {
    // @TODO: [CAMTRANS] Fill this in...
    return 0;
}

void CamtransCamera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::setHeightAngle(float h) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::translate(const glm::vec4 &v) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::rotateU(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::rotateV(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::rotateW(float degrees) {
    // @TODO: [CAMTRANS] Fill this in...

}

void CamtransCamera::setClip(float nearPlane, float farPlane) {
    // @TODO: [CAMTRANS] Fill this in...

}

