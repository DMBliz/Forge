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
	    retDrawable->GetMesh().GetBufferLayout()->Add<Vector3>("pos", 0, BufferElementType::Position);
        retDrawable->GetMesh().GetBufferLayout()->Add<Vector2>("textureCoords", 1, BufferElementType::UV);
        retDrawable->GetMesh().GetBufferLayout()->Add<Vector3>("normals", 2, BufferElementType::Normal);

        retDrawable->GetMaterial().SetShader(engine->GetResources()->GetResource<Shader>("Resources/Shaders/Model.glsl"));
        retDrawable->GetMaterial().Uniforms().AddUniform("projection", UniformDataType::MATRIX4);
        retDrawable->GetMaterial().Uniforms().AddUniform("view", UniformDataType::MATRIX4);
        retDrawable->GetMaterial().Uniforms().AddUniform("model", UniformDataType::MATRIX4);

		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			
			
            LoadMaterialTextures(material, retDrawable, aiTextureType_DIFFUSE, "TexAlbedo");
            LoadMaterialTextures(material, retDrawable, aiTextureType_SPECULAR, "TexMetallic");
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
