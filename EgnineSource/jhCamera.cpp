#include "jhCamera.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhSceneManager.h"
#include "jhLayer.h"
#include "jhMaterial.h"
#include "jhRendererComponent.h"

namespace jh
{

	Matrix Camera::sViewMat = Matrix::Identity;
	Matrix Camera::sProjectionMat = Matrix::Identity;


	Camera::Camera()
		: Component(eComponentType::CAMERA)
		, meProjectionType(eProjectionType::PERSPECTIVE)
		, mAspectRatio(1.0f)
		, mNearPlain(1.0f)
		, mFarPlain(1000.0f)
		, mScale(1.0f)
		, mViewMat(Matrix::Identity)
		, mProjectionMat(Matrix::Identity)
	{
	}

	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		EnableAllLayerMasks();
	}
	void Camera::Update()
	{
	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
		registerCameraAtRenderer();
	}
	void Camera::Render()
	{
		sViewMat = mViewMat;
		sProjectionMat = mProjectionMat;
		sortGameObjects();
		renderOpaque();
		renderCutout();
		renderTransparent();
	}


	void Camera::CreateViewMatrix()
	{
		Transform* pTransform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);

		// translation info
		Vector3 pos = pTransform->GetPosition();

		// Create Translation View Matrix
		mViewMat = Matrix::Identity;
		mViewMat *= Matrix::CreateTranslation(-pos);


		// rotation info
		Vector3 upVector = pTransform->GetUp();
		Vector3 rightVector = pTransform->GetRight();
		Vector3 forwardVector = pTransform->GetForward();


		Matrix viewRotationMat;
		viewRotationMat._11 = rightVector.x;	viewRotationMat._12 = upVector.x;	viewRotationMat._13 = forwardVector.x;
		viewRotationMat._21 = rightVector.y;	viewRotationMat._22 = upVector.y;	viewRotationMat._23 = forwardVector.y;
		viewRotationMat._31 = rightVector.z;	viewRotationMat._32 = upVector.z;	viewRotationMat._33 = forwardVector.z;

		mViewMat *= viewRotationMat;

	}
	void Camera::CreateProjectionMatrix()
	{
		RECT windowRect;
		ZeroMemory(&windowRect, sizeof(RECT));

		GetClientRect(Application::GetInstance().GetHwnd(), &windowRect);

		float width = static_cast<float>(windowRect.right - windowRect.left);
		float height = static_cast<float>(windowRect.bottom - windowRect.top);

		mAspectRatio = width / height;

		switch (meProjectionType)
		{
		case eProjectionType::PERSPECTIVE:
			mProjectionMat = Matrix::CreatePerspectiveFieldOfViewLH(
				XM_2PI / 6.0f,								// 60µµ
				mAspectRatio,
				mNearPlain,
				mFarPlain
			);
			break;
		case eProjectionType::ORTHOGRAPHIC:
			mProjectionMat = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNearPlain, mFarPlain);
			break;
		default:
			assert(false);
			break;
		}
	}

	void Camera::registerCameraAtRenderer()
	{
		renderer::pCameras.push_back(this);
	}
	void Camera::TurnONLayerMasks(const eLayerType eLayer, const bool bEnable)
	{
		mLayerMasks.set(static_cast<UINT>(eLayer), bEnable);
	}

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutObjects.clear();
		mTransparentObjects.clear();

		Scene* pCurrScene = SceneManager::GetCurrentScene();

		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i) 
		{
			if (mLayerMasks[i]) 
			{
				Layer& layer = pCurrScene->GetLayer(static_cast<eLayerType>(i));
				const std::vector<GameObject*>& gameObjects = layer.GetGameObjects();

				if (gameObjects.size() == 0)
					{continue;}

				for (auto* pGameObject : gameObjects)
				{
					if (pGameObject == nullptr) 
						{continue;}
					RendererComponent* pRenderer;
					void* pCacheMeshRenerer = pGameObject->GetComponentOrNull(eComponentType::MESH_RENDERER);
					void* pCacheSpriteRenerer = pGameObject->GetComponentOrNull(eComponentType::SPRITE_RENDERER);
					if (pCacheMeshRenerer == nullptr && pCacheSpriteRenerer == nullptr)
						{continue;}

					if (pCacheMeshRenerer != nullptr)
						{ pRenderer = static_cast<RendererComponent*>(pCacheMeshRenerer); }
					else
						{ pRenderer = static_cast<RendererComponent*>(pCacheSpriteRenerer); }
					
					pushGameObjectByMaterialRenderingMode(pRenderer, pGameObject);

				}
			}
		}
	}
	void Camera::renderOpaque()
	{
		for (auto* pGameObject : mOpaqueGameObjects)
		{
			if (pGameObject == nullptr) 
				{continue;}
			pGameObject->Render();
		}
	}
	void Camera::renderCutout()
	{
		for (auto* pGameObject : mCutoutObjects)
		{
			if (pGameObject == nullptr)
				{continue;}
			pGameObject->Render();
		}
	}
	void Camera::renderTransparent()
	{
		for (auto* pGameObject : mTransparentObjects)
		{
			if (pGameObject == nullptr)
				{continue;}
			pGameObject->Render();
		}
	}

	void Camera::pushGameObjectByMaterialRenderingMode(RendererComponent* pRenderer, GameObject* pGameObject)
	{
		Material* pMaterial = pRenderer->GetMeterial();
		assert(pMaterial != nullptr);

		switch (pMaterial->GetRenderingMode())
		{
		case eRenderingMode::OPAQUEE:
			mOpaqueGameObjects.push_back(pGameObject);
			break;
		case eRenderingMode::CUTOUT:
			mCutoutObjects.push_back(pGameObject);
			break;
		case eRenderingMode::TRANSPARENTT:
			mTransparentObjects.push_back(pGameObject);
			break;
		default:
			assert(false);
			break;
		}
	}
}