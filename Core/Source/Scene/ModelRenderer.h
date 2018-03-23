#pragma once
#include "Graphics/Model.h"
#include "Scene/Component.h"

namespace Forge
{

	class ModelRenderer : public Component
	{
		Model* model = nullptr;

	public:
		ModelRenderer();
		~ModelRenderer();

		void SetModel(Model* model);
		Model* GetModel() const;

        void Update() override;

        void OnEnable() override;
        void OnDisable() override;
	};

}
