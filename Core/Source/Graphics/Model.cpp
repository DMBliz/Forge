#include "Model.h"
#include "Core/Engine.h"
#include "Math/Quaternion.h"
#include "OGL/GLIndexBuffer.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


namespace Forge
{
	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_drawables.push_back(ProcessMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Drawable* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Drawable* retDrawable = new Drawable();

		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			Vector3 vertex(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			Vector3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			Vector2 uv(0.0f, 0.0f);
			if(mesh->mTextureCoords[0])
			{
				uv.Set(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
            retDrawable->GetMesh().GetVertecies().push_back(vertex);
            retDrawable->GetMesh().GetNormals().push_back(normal);
            retDrawable->GetMesh().GetUV().push_back(uv);
		}

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j++)
                retDrawable->GetMesh().GetIndicies().push_back(face.mIndices[j]);
		}
        //setting buffer layout
	    retDrawable->GetMesh().GetBufferLayout()->Add<Vector3>("pos", 0, BufferElementType::Position);
        retDrawable->GetMesh().GetBufferLayout()->Add<Vector2>("textureCoords", 1, BufferElementType::UV);
        retDrawable->GetMesh().GetBufferLayout()->Add<Vector3>("normals", 2, BufferElementType::Normal);

        retDrawable->GetMaterial().SetShader(engine->getResources()->GetResource<Shader>("Resources/Shaders/Model.glsl"));

		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			
			//loading textures
            LoadMaterialTextures(material, retDrawable, aiTextureType_DIFFUSE, "material.diffuse");
            LoadMaterialTextures(material, retDrawable, aiTextureType_SPECULAR, "material.specular");
		}
        retDrawable->GetMesh().Initialize();
		return retDrawable;
	}

    void Model::LoadMaterialTextures(aiMaterial* mat, Drawable* drawable, aiTextureType type, const String& uniformName)
	{
        aiString name;
        mat->GetTexture(type, 0, &name);
        if (name.length <= 0)
            return;
        Texture2D* tex = engine->getResources()->LoadNowResource<Texture2D>(directory + name.C_Str());

        if (tex != nullptr)
            drawable->GetMaterial().GetUniform(uniformName)->SetTexture(*tex);
	}

	Model::Model()
	{
	}

	Model::Model(const String& path)
	{
		Load(path);
	}

	Model::~Model()
	{}

    void Model::SetWorldPosition(const Matrix3x4& newPosition)
    {
        for (int i = 0; i < _drawables.size(); i++)
        {
            _drawables[i]->SetWorldPosition(newPosition);
        }
    }

    void Model::Load(const String& filename)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.cString(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG(String("Assimp error") + importer.GetErrorString());
			return;
		}

		resourceName = filename;
		directory = filename.subString(0, filename.findLast('/', filename.length()) + 1);

		ProcessNode(scene->mRootNode, scene);
	}

    //setting values to uniform and queing for rendering
    void Model::Draw()
    {
        Renderer* renderer = engine->getRenderer();
        for (int i = 0; i < _drawables.size(); i++)
        {

            _drawables[i]->GetMaterial().GetUniform("projection")->SetValue<Matrix4>(renderer->GetFrustum().GetMatrix());
            _drawables[i]->GetMaterial().GetUniform("view")->SetValue<Matrix4>(renderer->GetCamera().GetViewMatrix());
            _drawables[i]->GetMaterial().GetUniform("model")->SetValue<Matrix4>(_drawables[i]->GetWorldPosition()->ToMatrix4());

            _drawables[i]->GetMaterial().GetUniform("viewPos")->SetValue<Vector3>(renderer->GetCamera().GetViewMatrix().GetTranslation());
            _drawables[i]->GetMaterial().GetUniform("material.shininess")->SetValue<float>(32.0f);


            auto pointLights = renderer->GetPointLights();

            _drawables[i]->GetMaterial().GetUniform("numOfPointLight")->SetValue<uint>(pointLights.size());

            for(uint j =0; j < pointLights.size(); j++)
            {
                _drawables[i]->GetMaterial().GetUniform("pointLight[" + String(j) + "].color")->SetValue<Color>(pointLights[j]->GetColor());
                _drawables[i]->GetMaterial().GetUniform("pointLight[" + String(j) + "].linear")->SetValue<float>(pointLights[j]->Linear());
                _drawables[i]->GetMaterial().GetUniform("pointLight[" + String(j) + "].quadratic")->SetValue<float>(pointLights[j]->Quadratic());
                _drawables[i]->GetMaterial().GetUniform("pointLight[" + String(j) + "].position")->SetValue<Vector3>(pointLights[j]->GetTransform()->Translation());
            }

            auto spotlights = renderer->GetSpotLights();
            _drawables[i]->GetMaterial().GetUniform("numOfSpotLight")->SetValue<uint>(spotlights.size());

            for (uint j = 0; j < spotlights.size(); j++)
            {
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].color")->SetValue<Color>(spotlights[j]->GetColor());
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].linear")->SetValue<float>(spotlights[j]->Linear());
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].quadratic")->SetValue<float>(spotlights[j]->Quadratic());
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].cutOff")->SetValue<float>(cosf(spotlights[j]->CutOff() * DEGTORAD));
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].outerCutOff")->SetValue<float>(cosf(spotlights[j]->OuterCutOff() * DEGTORAD));
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].position")->SetValue<Vector3>(spotlights[j]->Transform()->Translation());
                _drawables[i]->GetMaterial().GetUniform("spotLight[" + String(j) + "].direction")->SetValue<Vector3>(spotlights[j]->Transform()->Rotation() * Vector3::Forward);
            }

            auto dirLights = renderer->GetDirLights();
            _drawables[i]->GetMaterial().GetUniform("numOfDirLight")->SetValue<uint>(dirLights.size());

            for (uint j = 0; j < dirLights.size(); j++)
            {
                _drawables[i]->GetMaterial().GetUniform("dirLight[" + String(j) + "].color")->SetValue<Color>(dirLights[j]->GetColor());
                _drawables[i]->GetMaterial().GetUniform("dirLight[" + String(j) + "].direction")->SetValue<Vector3>(dirLights[j]->Direction());
            }

            _drawables[i]->Draw();
        }
    }

    void Model::SetActive(bool state)
    {
        if (state == active)
            return;

        active = state;

        if(state == true)
        {
            OnEnable();
        }else
        {
            OnDisable();
        }
    }

    void Model::OnEnable()
    {
        for(int i = 0; i < _drawables.size(); i++)
        {
            _drawables[i]->SetActive(true);
        }
    }

    void Model::OnDisable()
    {
        for (int i = 0; i < _drawables.size(); i++)
        {
            _drawables[i]->SetActive(false);
        }
    }
}
