#include "jhParicleSystem.h"
#include "jhRenderer.h"
#include "jhResources.h"
namespace jh
{
	/*
		, mParticleCount()
		, mStartSize()
		, mEndSize()
		, mStartColor()
		, mEndColor()
		, mStartLifeTime()
	*/
	ParticleSystem::ParticleSystem()
		: RendererComponent(eComponentType::PARTICLE_SYSTEM)
		, mParticleCount(0)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mStartLifeTime(0.0f)
	{
		SetMesh(Resources::Find<Mesh>(renderer::RECT_MESH_KEY));

		// Paticle Material Setting
	}
	void ParticleSystem::Initialize()
	{

	}
	void ParticleSystem::Update()
	{

	}
	void ParticleSystem::FixedUpdate()
	{

	}
	void ParticleSystem::Render()
	{

	}
}