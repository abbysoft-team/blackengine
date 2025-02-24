//
// Created by popof on 15.11.2018.
//

#include "Camera.h"

#include <util/Screen.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace black {
Camera::Camera(
    ProjectionType projection,
    const glm::vec3 &position,
    const glm::vec3 &lookAt,
    const glm::vec3 &upVector)
    : position(position),
    lookAt(lookAt),
    up(upVector),
    projectionType(ProjectionType::PERSPECTIVE) {
  this->setProjection(projection);
  this->updateMatrices();
}

const glm::mat4 &Camera::getViewMatrix() const {
  return this->viewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() const {
  return this->projectionMatrix;
}

const glm::vec3 &Camera::getPosition() const {
  return this->position;
}

const glm::vec3 &Camera::getLookAt() const {
  return this->lookAt;
}

const glm::vec3 &Camera::getUpVector() const {
  return this->up;
}

void Camera::updateMatrices() {
  this->viewMatrix = glm::lookAt(this->position, this->lookAt, this->up);
}

void Camera::setPosition(const glm::vec3 &newPosition) {
  this->position = newPosition;
  this->updateMatrices();
}

void Camera::setLookAt(const glm::vec3 &newLookAt) {
  this->lookAt = glm::normalize(newLookAt);
  this->updateMatrices();
}

void Camera::setUpVector(const glm::vec3 &newUp) {
  this->up = glm::normalize(newUp);
  this->updateMatrices();
}

void Camera::setProjection(ProjectionType projection) {
  this->projectionType = projection;

  switch (this->projectionType) {
  case ProjectionType::PERSPECTIVE:
    this->projectionMatrix = glm::perspective(45.0f, Screen::GetAspectRatio(), 0.1f, 100.0f);
    break;
  case ProjectionType::ORTHOGRAPHIC:this->projectionMatrix = glm::ortho(0, Screen::GetWidth(), 0, Screen::GetHeight());
    break;
  }
}

void Camera::strafeRight(float value) {
  this->position += glm::vec3(value, 0.0f, 0.0f);
  updateMatrices();
}

void Camera::strafeLeft(float value) {
  this->position -= glm::vec3(value, 0.0f, 0.0f);
  updateMatrices();
}

void Camera::moveForward(float value) {
  this->position += lookAt * value;
  updateMatrices();
}

void Camera::moveBackward(float value) {
  this->position -= lookAt * value;
  updateMatrices();
}
}