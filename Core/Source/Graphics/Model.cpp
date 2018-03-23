#include "Model.h"
#include "Core/Engine.h"
#include "OpenGL/GLIndexBuffer.h"
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
        //setting uniforms
        retDrawable->GetMaterial().SetShader(engine->GetResources()->GetResource<Shader>("Resources/Shaders/Model.glsl"));
        retDrawable->GetMaterial().Uniforms().AddUniform("projection", UniformDataType::MATRIX4);
        retDrawable->GetMaterial().Uniforms().AddUniform("view", UniformDataType::MATRIX4);
        retDrawable->GetMaterial().Uniforms().AddUniform("model", UniformDataType::MATRIX4);

        retDrawable->GetMaterial().Uniforms().AddUniform("viewPos", UniformDataType::VECTOR3);

        retDrawable->GetMaterial().Uniforms().AddUniform("pointLight.position", UniformDataType::VECTOR3);
        retDrawable->GetMaterial().Uniforms().AddUniform("pointLight.color", UniformDataType::COLOR);
        retDrawable->GetMaterial().Uniforms().AddUniform("pointLight.linear", UniformDataType::FLOAT);
        retDrawable->GetMaterial().Uniforms().AddUniform("pointLight.quadratic", UniformDataType::FLOAT);

        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.position", UniformDataType::VECTOR3);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.direction", UniformDataType::VECTOR3);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.color", UniformDataType::COLOR);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.linear", UniformDataType::FLOAT);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.quadratic", UniformDataType::FLOAT);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.cutOff", UniformDataType::FLOAT);
        retDrawable->GetMaterial().Uniforms().AddUniform("spotLight.outerCutOff", UniformDataType::FLOAT);

        retDrawable->GetMaterial().Uniforms().AddUniform("dirLight.direction", UniformDataType::VECTOR3); 
        retDrawable->GetMaterial().Uniforms().AddUniform("dirLight.color", UniformDataType::COLOR);

        retDrawable->GetMaterial().Uniforms().AddUniform("material.shininess", UniformDataType::FLOAT);

		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			
			//loading textures
            LoadMaterialTextures(material, retDrawable, aiTextureType_DIFFUSE, "material.ambient");
            LoadMaterialTextures(material, retDrawable, aiTextureType_SPECULAR, "material.specular");
			LoadMaterialTextures(material, retDrawable, aiTextureType_NORMALS, "TexNormal");
			LoadMaterialTextures(material, retDrawable, aiTextureType_SHININESS, "TexRoughness");
			LoadMaterialTextures(material, retDrawable, aiTextureType_AMBIENT, "TexAO");
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
        Texture2D* tex = engine->GetResources()->LoadNowResource<Texture2D>(directory + name.C_Str());
        drawable->GetMaterial().Uniforms().AddUniform(uniformName, UniformDataType::SAMPLER2D);
        if (tex != nullptr)
            drawable->GetMaterial().AddTexture(tex, uniformName);
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
		const aiScene* scene = importer.ReadFile(filename.CString(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG(String("Assimp error") + importer.GetErrorString());
			return;
		}

		resourceName = filename;
		directory = filename.SubString(0, filename.FindLast('/', filename.Length()) + 1);

		ProcessNode(scene->mRootNode, scene);
	}
    //TODO: multiple light support
    //setting values to uniform and queing for rendering
    void Model::Draw()
    {
        Renderer* renderer = engine->GetRenderer();
        for (int i = 0; i < _drawables.size(); i++)
        {
            _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("projection", renderer->GetFrustum().GetMatrix());
            _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("view", renderer->GetCamera().GetViewMatrix());
            _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Matrix4>("model", _drawables[i]->GetWorldPosition()->ToMatrix4());
            
            _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("viewPos", Matrix3x4(renderer->GetCamera().GetViewMatrix()).Translation());

            _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("material.shininess", 32.0f);


            auto pointLights = renderer->GetPointLights();
            if (pointLights.size() > 0)
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("pointLight.color", pointLights[0]->GetColor());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("pointLight.linear", pointLights[0]->Linear());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("pointLight.quadratic", pointLights[0]->Quadratic());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("pointLight.position", pointLights[0]->GetTransform()->Translation());
            }
            else
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("pointLight.color", Color(1.0f, 1.0f, 1.0f, 1.0f));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("pointLight.position", Vector3(0.0f, 0.0f, 0.0f));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("pointLight.linear", 0.22f);
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("pointLight.quadratic", 0.20f);
            }

            auto spotlights = renderer->GetSpotLights();
            if (spotlights.size() > 0)
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("spotLight.color", spotlights[0]->GetColor());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.linear", spotlights[0]->Linear());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.quadratic", spotlights[0]->Quadratic());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.cutOff", cosf(spotlights[0]->CutOff() * DEGTORAD));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.outerCutOff", cosf(spotlights[0]->OuterCutOff() * DEGTORAD));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("spotLight.position", spotlights[0]->Transform()->Translation());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("spotLight.direction", spotlights[0]->Transform()->Rotation() * Vector3::Forward);
            }
            else
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("spotLight.color", Color(1.0f, 1.0f, 1.0f, 1.0f));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.linear", 0.22f);
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.quadratic", 0.20f);
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.cutOff", cosf(30.0f * DEGTORAD));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<float>("spotLight.outerCutOff", cosf(25.0f * DEGTORAD));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("spotLight.position", Vector3(0.0f, 0.0f, 0.0f));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("spotLight.direction", Vector3(0.0, 0.0f, 0.0f));
            }

            auto dirLights = renderer->GetDirLights();
            if (dirLights.size() > 0)
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("dirLight.color", dirLights[0]->GetColor());
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("dirLight.direction", dirLights[0]->Direction());
            }
            else
            {
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Color>("dirLight.color", Color(1.0f, 1.0f, 1.0f, 1.0f));
                _drawables[i]->GetMaterial().Uniforms().SetValueToUniform<Vector3>("dirLight.direction", Vector3(-0.2f, -1.0f, -0.3f));
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
