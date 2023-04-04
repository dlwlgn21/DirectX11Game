#include "jhParicleSystem.h"
#include "jhRenderer.h"
#include "jhResources.h"
#include "jhStructuredBuffer.h"
#include "jhGameObject.h"
#include "jhTransform.h"

static constexpr UINT STRUCTURED_BUFFER_SLOT_NUMBER = 15;

namespace jh
{
	ParticleSystem::ParticleSystem()
		: RendererComponent(eComponentType::PARTICLE_SYSTEM)
		, mParticleCount(0)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mStartLifeTime(0.0f)
	{
		SetMesh(Resources::Find<Mesh>(renderer::POINT_MESH_KEY));
		// Paticle Material Setting
		SetMaterial(Resources::Find<Material>(renderer::PARTICLE_MATERIAL_KEY));

		const UINT particlesSize = 1000;
		graphics::Particle praticles[particlesSize] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 16; ++x)
			{
				praticles[16 * y + x].Position = startPos + Vector4(x * 100.0f, y * 100.0f, 0.0f, 0.0f);
				praticles[16 * y + x].Active = 1;
			}
		}
		mParticleCount = 9 * 16;
		mpStructuredBuffer = new graphics::StructuredBuffer();
		mpStructuredBuffer->Create(sizeof(Particle), mParticleCount, graphics::eShaderResourceViewType::NONE, praticles);

	}

	ParticleSystem::~ParticleSystem()
	{
		if (mpStructuredBuffer != nullptr)
		{
			delete mpStructuredBuffer;
		}
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
		assert(GetOwner() != nullptr);
		GetOwner()->GetTransform()->WriteContantBufferAtGPUAndSetConstantBufferAtShader();
		mpStructuredBuffer->SetShaderResourceView(graphics::eShaderStage::VERTEX_SHADER, STRUCTURED_BUFFER_SLOT_NUMBER);
		mpStructuredBuffer->SetShaderResourceView(graphics::eShaderStage::PIXEL_SHADER, STRUCTURED_BUFFER_SLOT_NUMBER);
		mpStructuredBuffer->SetShaderResourceView(graphics::eShaderStage::GEOMETRY_SHADER, STRUCTURED_BUFFER_SLOT_NUMBER);
		//mpStructuredBuffer->BindBufferAtGPU();
		GetMeterial()->BindConstantBufferAndShaderAndSetTextureSRVAtShader();
		GetMesh()->RenderInstanced(mParticleCount);
	}
}