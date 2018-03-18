#pragma once
#include "Drawable.h"
#include "Resources/Resource.h"
#include "Texture2D.h"

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

namespace Forge
{
	
	class Model : public Resource
	{
	private:
        std::vector<Drawable*> _drawables;
		String directory;
        bool active = false;

		void ProcessNode(aiNode *node, const aiScene *scene);
		Drawable* ProcessMesh(aiMesh* mesh, const aiScene *scene);
        void LoadMaterialTextures(aiMaterial* mat, Drawable* drawable, aiTextureType type, const String& uniformName);
	public:
		Model();
		explicit Model(const String& path);
		~Model();

        void SetWorldPosition(const Matrix3x4& newPosition);

		void Load(const String& filename) override;
        void SetActive(bool state);
        void OnEnable();
        void OnDisable();
	};
}
