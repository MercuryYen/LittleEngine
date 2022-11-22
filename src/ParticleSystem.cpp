#include"ParticleSystem.h"

/*
_maxAmount	: particle's max amount
_size		: particle's size
_interval	: particle's generation per second
_liveTime	: particle's live time
_pos		: particle system's center position
_dir		: particle's initial velocity
rnd_r		: particle system's generation radius
_loop		: regenerate particle?
*/
ParticleSystem::ParticleSystem(int _maxAmount, float _size, float _interval, float _liveTime, glm::vec3 _pos, glm::vec3 _dir, float rnd_r, bool _loop)
{
	maxAmount = _maxAmount;
	position = _pos;
	direction = _dir;
	positionRandomRadius = rnd_r;
	loop = _loop;
	color = glm::vec4(1, 1, 1, 1);
	size = _size;
	interval = _interval;
	liveTime = _liveTime;

	particles = new StandardParticle[maxAmount];

	if (!quadVAO) {

		//per particle
		GLfloat quadVertices[] = {
					0,0,
					1,0,
					0,1,
					1,1
		}; 
		GLuint quadElement[] = {
			0,1,2,
			1,3,2
		};
		GLuint VBO;
		GLuint VEO;

		glGenVertexArrays(1, &quadVAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VEO);

		glBindVertexArray(quadVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribDivisor(0, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadElement), quadElement, GL_STATIC_DRAW);

		//particle system
		glGenBuffers(1, &timeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, timeVBO);
		glBufferData(GL_ARRAY_BUFFER, maxAmount * sizeof(StandardParticle), NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE, sizeof(StandardParticle),(void*)0);
		glVertexAttribDivisor(1, 1);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(StandardParticle), (void*)sizeof(float));
		glVertexAttribDivisor(2, 1);
		glEnableVertexAttribArray(2);
		
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(StandardParticle), (void*)sizeof(glm::vec3));
		glVertexAttribDivisor(3, 1);
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);
	}

	reset();
}

void ParticleSystem::reset()
{
	particleAmount = 0;
}

void ParticleSystem::addParticle(int amount)
{
	for (int i = 0; i < amount; ++i) {
		if (particleAmount < maxAmount) {
			particles[particleAmount].time = 0;
			particles[particleAmount].position = positionRandomRadius * glm::normalize(glm::vec3(rand()%101-50, rand()%101-50, rand()%101-50));
			particles[particleAmount].velocity = direction;

			++particleAmount;
		}
	}
}
void ParticleSystem::updateParticle(int index, float deltaTime) {
	particles[index].time += deltaTime;
	particles[index].position += particles[index].velocity*deltaTime;
}

void ParticleSystem::deleteParticle(int index)
{
	particles[index] = particles[particleAmount - 1];
}

void ParticleSystem::sortParticle(glm::vec3 _camPos)
{
	StandardParticle::camPos = _camPos;
	sort(particles, particles + particleAmount, StandardParticle::comp);
}

void ParticleSystem::update(float deltaTime)
{
	sumOfDeltaTime += deltaTime;

	for (int i = 0; i < particleAmount; ++i) {
		updateParticle(i, deltaTime);

		if (particles[i].time > liveTime) {
			deleteParticle(i);
			--i;
			--particleAmount;
		}
	}

	if (loop && interval > 0) {
		addParticle((int)(sumOfDeltaTime * interval));
		sumOfDeltaTime -= (int)(sumOfDeltaTime * interval) / interval;
	}

	//sort(particles, particles + particleAmount);
}

void ParticleSystem::draw(ParticleShader& shader)
{
	glm::mat4 individualMatrix(1);
	individualMatrix = glm::scale(individualMatrix, glm::vec3(size));

	shader.setIndividualMatrix(individualMatrix);
	shader.setColor(color);

	glBindVertexArray(quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, timeVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleAmount * sizeof(StandardParticle), particles);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleAmount);
	glBindVertexArray(0);
}

bool StandardParticle::comp(const StandardParticle& a, const StandardParticle& b)
{
	return glm::length(a.position - camPos) > glm::length(b.position - camPos);
}

glm::vec3 StandardParticle::camPos;