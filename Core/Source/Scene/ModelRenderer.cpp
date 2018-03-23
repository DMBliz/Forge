#include "ModelRenderer.h"
#include "TransformComponent.h"
#include "Entity.h"

namespace Forge
{

	ModelRenderer::ModelRenderer()
	{
        model = new Model();
	}

	ModelRenderer::~ModelRenderer()
	{}

	void ModelRenderer::SetModel(Model* model)
	{
		this->model = model;
        model->SetActive(true);
        TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
        if (trn != nullptr)
        {
            model->SetWorldPosition(*trn->GetWorldTransform());
        }
	}

	Model* ModelRenderer::GetModel() const
	{
		return model;
	}

    void ModelRenderer::Update()
    {
        model->Draw();
    }

    void ModelRenderer::OnEnable()
    {
        if (model != nullptr)
        {
            model->SetActive(true);
            TransformComponent* trn = GetOwner()->GetComponent<TransformComponent>();
            if (trn != nullptr)
            {
                model->SetWorldPosition(*trn->GetWorldTransform());
            }
        }
    }

    void ModelRenderer::OnDisable()
    {
        if (model != nullptr)
        {
            model->SetActive(false);
        }
    }
}
