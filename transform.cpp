#include "transform.h"

void jtgTransform::apply()
{
	this->mat = glm::mat4(1);

	this->mat *= glm::translate(this->pos);
	this->mat *= glm::scale(glm::vec3(this->scale));
	this->mat *= glm::toMat4(this->rot);
	this->mat *= glm::translate(-this->pivot);
}

jtgTransform::jtgTransform(glm::vec3 pos)
{
	this->pos = pos;
	apply();
}

jtgTransform::jtgTransform(glm::vec3 pos, glm::quat rot, float scale)
{
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
	apply();
}


