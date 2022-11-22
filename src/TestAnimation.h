#include "Animation.h"

class TestAnimationManager :public AnimationManager{
public:
	TestAnimationManager() {
		//rotation
		{
			Animation* rotateAni = new Animation(4);

			AnimationMotion* r = new AnimationMotion(AnimationType::ROTATION);
			r->frames.push_back(AnimationFrame(0, glm::vec3(0, 0, 0)));
			r->frames.push_back(AnimationFrame(1, glm::vec3(0, 90, 0)));
			r->frames.push_back(AnimationFrame(2, glm::vec3(0, 180, 0)));
			r->frames.push_back(AnimationFrame(3, glm::vec3(0, 270, 0)));
			rotateAni->addMotion("parent", r);

			animations["rotate"] = rotateAni;
		}

		//double rotation?!
		{
			Animation* rotateAni = new Animation(4);

			AnimationMotion* r = new AnimationMotion(AnimationType::ROTATION);
			r->frames.push_back(AnimationFrame(0, glm::vec3(0, 0, 0)));
			r->frames.push_back(AnimationFrame(1, glm::vec3(0, 90, 0)));
			r->frames.push_back(AnimationFrame(2, glm::vec3(0, 180, 0)));
			r->frames.push_back(AnimationFrame(3, glm::vec3(0, 270, 0)));
			rotateAni->addMotion("parent", r);

			AnimationMotion* rr = new AnimationMotion(AnimationType::ROTATION);
			rr->indeces.push_back(0);
			rr->frames.push_back(AnimationFrame(0, glm::vec3(-90, 0, 0)));
			rr->frames.push_back(AnimationFrame(1, glm::vec3(-90, -90, 0)));
			rr->frames.push_back(AnimationFrame(2, glm::vec3(-90, -180, 0)));
			rr->frames.push_back(AnimationFrame(3, glm::vec3(-90, -270, 0)));
			rotateAni->addMotion("child", rr);

			AnimationMotion* s = new AnimationMotion(AnimationType::SCALE);
			s->frames.push_back(AnimationFrame(0, glm::vec3(0.8, 0.8, 0.8)));
			s->frames.push_back(AnimationFrame(1, glm::vec3(1, 1, 1)));
			s->frames.push_back(AnimationFrame(2, glm::vec3(1.2, 1.2, 1.2)));
			s->frames.push_back(AnimationFrame(3, glm::vec3(1, 1, 1)));
			rotateAni->addMotion("scale", s);

			AnimationMotion* rt = new AnimationMotion(AnimationType::POSITION);
			rt->indeces.push_back(0);
			rt->frames.push_back(AnimationFrame(0, glm::vec3(10, 10, 0)));
			rt->frames.push_back(AnimationFrame(1, glm::vec3(10, 0, 0)));
			rt->frames.push_back(AnimationFrame(2, glm::vec3(10, -10, 0)));
			rt->frames.push_back(AnimationFrame(3, glm::vec3(10, 0, 0)));
			rotateAni->addMotion("child position", rt);

			animations["double rotate"] = rotateAni;
		}
	}
};