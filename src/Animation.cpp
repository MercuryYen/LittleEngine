#include "Animation.h"

glm::vec3 AnimationMotion::getValue(float time, bool loop)
{
	static float CardinalFloatV[] = {
		-0.5,1,-0.5,0,
		1.5,-2.5,0,1,
		-1.5,2,0.5,0,
		0.5,-0.5,0,0
	};
	static glm::mat4 CardinalMat = glm::make_mat4(CardinalFloatV);
	//out of range
	if (!loop && time < 0) {
		return frames[0].value;
	}
	else if (!loop && time > frames.back().time) {
		return frames.back().value;
	}
	//Cardinal spline	
	else {
		//find 4 points
		glm::vec3 points[4];
		int lowerBound = 0;
		int upperBound = frames.size() - 1;
		int index = 0;
		while (time > animation->time)time -= animation->time;

		//find true range
		if (time < frames.front().time || time > frames.back().time) {
			index = 0;
		}
		else {
			int preIndex = -1;
			while (preIndex!=index) {
				preIndex = index;
				index = (lowerBound + upperBound) / 2;
				if (time > frames[index].time) {
					lowerBound = index;
				}
				else {
					upperBound = index;
				}
			}
			++index;
		}

		

		//to calculate curve
		float t;

		if (index > 0) {
			t = (time - frames[index - 1].time) / (frames[index].time - frames[index - 1].time);
		}
		else {
			if (time > frames.back().time) {
				t = (time - frames.back().time) / (frames[0].time + animation->time - frames.back().time);
			}
			else {
				t = (time + animation->time - frames.back().time) / (frames[0].time + animation->time - frames.back().time);
			}
		}

		int p0 = (index + frames.size() - 2) % frames.size();
		int p1 = (index + frames.size() - 1) % frames.size();
		int p2 = index;
		int p3 = (index + 1) % frames.size();

		//calculate interpolation
		if (type != AnimationType::ROTATION) {
			float GP[] = {
			frames[p0].value.x,frames[p0].value.y,frames[p0].value.z,
			frames[p1].value.x,frames[p1].value.y,frames[p1].value.z,
			frames[p2].value.x,frames[p2].value.y,frames[p2].value.z,
			frames[p3].value.x,frames[p3].value.y,frames[p3].value.z,
			};
			glm::mat4x3 G = glm::make_mat4x3(GP);

			glm::vec4 P(t * t * t, t * t, t, 1);
			return G * glm::transpose(CardinalMat) * P;
		}
		else {
			//error
			/*glm::quat pre(glm::radians(frames[p1].value));
			glm::quat next(glm::radians(frames[p2].value));
			glm::quat mix = glm::slerp(pre, next, t);
			glm::vec3 euler = glm::eulerAngles(mix);
			glm::vec3 degreeeuler = glm::degrees(euler);
			return degreeeuler;*/
			glm::vec3 out;
			for (int i = 0; i < 3; ++i) {
				float pre = frames[p1].value[i];
				float next = frames[p2].value[i];
				
				float diff = next - pre;
				while (diff > 180)diff -= 360;
				while (diff < -180)diff += 360;

				out[i] = pre + t * diff;
			}
			return out;
		}
	}
}

void Animation::addMotion(string name, AnimationMotion* AM)
{
	motions[name] = AM;
	motions[name]->animation = this;
}
