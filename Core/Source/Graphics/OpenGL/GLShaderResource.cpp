#include "GLShaderResource.h"
#include "Core/Engine.h"
#include "glad/glad.h"
#include "Defines.h"
#include "GLCheck.h"

namespace Forge
{

	GLShaderResource::GLShaderResource()
	{}

	GLShaderResource::~GLShaderResource()
	{
		glDeleteShader(programID);
	}

	void GLShaderResource::LoadShader(const String& filename)
	{
		shaderSource = engine->GetFileSystem()->ReadFile(filename).GetString();

		vertexShader = GetBlock("vertex =");
		fragmentShader = GetBlock("pixel =");
	}

	String GLShaderResource::GetBlock(const String& blockName)
	{
		unsigned blockStart = shaderSource.Find(blockName);
		if (blockStart == String::NOTFOUND)
			return String();

		int openCount = 0;

		unsigned startInd = 0;
		unsigned endInd = 0;

		for (unsigned int i = blockStart; i < shaderSource.Length(); i++)
		{
			if(shaderSource.At(i) == '{')
			{
				if (openCount == 0)
					startInd = i + 1;
				openCount++;
			}

			if (shaderSource.At(i) == '}')
			{
				openCount--;
				if (openCount == 0)
				{
					endInd = i;
					break;
				}
			}
		}

		return shaderSource.SubString(startInd, endInd - startInd);
	}

	void GLShaderResource::Compile()
	{
		unsigned vs;
		glCheck(vs = glCreateShader(GL_VERTEX_SHADER));
		{
			const char* tmp = vertexShader.CString();
			glCheck(glShaderSource(vs, 1, &tmp, nullptr));
			glCheck(glCompileShader(vs));
		}

		{
			int success;
			char infoLog[512];

			glCheck(glGetShaderiv(vs, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				glCheck(glGetShaderInfoLog(vs, 512, nullptr, infoLog));
				LOG(("Shader compile error: " + String(infoLog)).CString());
				return;
			}

		}

		unsigned fs;
		glCheck(fs = glCreateShader(GL_FRAGMENT_SHADER));
		{
			const char* tmp = fragmentShader.CString();
			glCheck(glShaderSource(fs, 1, &tmp, nullptr));
			glCheck(glCompileShader(fs));
		}

		{
			int success;
			char infoLog[512];

			glCheck(glGetShaderiv(fs, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				glCheck(glGetShaderInfoLog(fs, 512, nullptr, infoLog));
				LOG(("Shader compile error: " + String(infoLog)).CString());
				return;
			}
		}

		glCheck(programID = glCreateProgram());

		glCheck(glAttachShader(programID, vs));
		glCheck(glAttachShader(programID, fs));

		glCheck(glLinkProgram(programID));

		{
			int success;
			char infoLog[512];

			glCheck(glGetProgramiv(programID, GL_LINK_STATUS, &success));
			if (!success)
			{
				glCheck(glGetProgramInfoLog(programID, 512, nullptr, infoLog));
				LOG(("Program link error: " + String(infoLog)).CString());
			}
		}

		glCheck(glDeleteShader(vs));
		glCheck(glDeleteShader(fs));
	}

	void GLShaderResource::Use()
	{
		glCheck(glUseProgram(programID));
	}

    int GLShaderResource::ResolveUniformLocation(const String& uniformName)
    {
        return glGetUniformLocation(programID, uniformName.CString());
    }

	void GLShaderResource::SetValueToUniform(const UniformDescription& desc)
	{
		switch (desc.type)
		{
			case UniformDataType::FLOAT:
			{
				float* data = reinterpret_cast<float*>(desc.data);
				
				if (desc._count == 1)
				{
					glCheck(glUniform1f(desc.location, data[0]));
				}
				else if (desc._count == 2)
				{
					glCheck(glUniform2f(desc.location, data[0], data[1]));
				}
				else if (desc._count == 3)
				{
					glCheck(glUniform3f(desc.location, data[0], data[1], data[2]));
				}
				else if (desc._count == 4)
				{
					glCheck(glUniform4f(desc.location, data[0], data[1], data[2], data[3]));
				}
				else if (desc._count > 4)
				{
					glCheck(glUniform1fv(desc.location, desc._count, data));
				}
				else
				{
					LOG("Wrong count");
				}
				break;
			}
			case UniformDataType::INTEGER:
			{
				int* data = reinterpret_cast<int*>(desc.data);
				if (desc._count == 1)
				{
					glCheck(glUniform1i(desc.location, data[0]));
				}
				else if (desc._count == 2)
				{
					glCheck(glUniform2i(desc.location, data[0], data[1]));
				}
				else if (desc._count == 3)
				{
					glCheck(glUniform3i(desc.location, data[0], data[1], data[2]));
				}
				else if (desc._count == 4)
				{
					glCheck(glUniform4i(desc.location, data[0], data[1], data[2], data[3]));
				}
				else if (desc._count  > 4)
				{
					glCheck(glUniform1iv(desc.location, desc._count, data));
				}
				else
				{
					LOG("Wrong count");
				}
				break;
			}
			case UniformDataType::UNSIGNED_INTEGER:
			{
				uint* data = reinterpret_cast<uint*>(desc.data);
				if (desc._count == 1)
				{
					glCheck(glUniform1ui(desc.location, data[0]));
				}
				else if (desc._count == 2)
				{
					glCheck(glUniform2ui(desc.location, data[0], data[1]));
				}
				else if (desc._count == 3)
				{
					glCheck(glUniform3ui(desc.location, data[0], data[1], data[2]));
				}
				else if (desc._count == 4)
				{
					glCheck(glUniform4ui(desc.location, data[0], data[1], data[2], data[3]));
				}
				else if (desc._count  > 4)
				{
					glCheck(glUniform1uiv(desc.location, desc._count, data));
				}
				else
				{
					LOG("Wrong count");
				}
				break;
			}
			case UniformDataType::VECTOR2I:
			{
				glCheck(glUniform2iv(desc.location, desc._count, reinterpret_cast<int*>(desc.data)));

				break;
			}
			case UniformDataType::VECTOR2:
			{
				glCheck(glUniform2fv(desc.location, desc._count, reinterpret_cast<float*>(desc.data)));

				break;
			}
			case UniformDataType::VECTOR3:
			{
				glCheck(glUniform3fv(desc.location, desc._count, reinterpret_cast<float*>(desc.data)));

				break;
			}
			case UniformDataType::VECTOR4:
			{
				glCheck(glUniform4fv(desc.location, desc._count, reinterpret_cast<float*>(desc.data)));

				break;
			}
			case UniformDataType::COLOR:
			{
				Color* cols = reinterpret_cast<Color*>(desc.data);
				Vector4* vecs = new Vector4[desc._count];

				for (unsigned int j = 0; j < desc._count; j++)
					vecs[j] = cols[j].GetNormalizedVector();

				glCheck(glUniform4fv(desc.location, desc._count, reinterpret_cast<float*>(vecs)));

				delete[] vecs;

				break;
			}
			case UniformDataType::MATRIX3:
			{
				glCheck(glUniformMatrix3fv(desc.location, desc._count, true, reinterpret_cast<float*>(desc.data)));

				break;
			}
			case UniformDataType::MATRIX4:
			{
				glCheck(glUniformMatrix4fv(desc.location, desc._count, true, reinterpret_cast<float*>(desc.data)));
				break;
			}
			case UniformDataType::SAMPLER2D:
			{
				uint* data = reinterpret_cast<uint*>(desc.data);

				glCheck(glUniform1i(desc.location, desc._count));

				glCheck(glActiveTexture(GL_TEXTURE0 + desc._count));
				glCheck(glBindTexture(GL_TEXTURE_2D, data[0]));

				break;
			}
		}
	}

	void GLShaderResource::SetSystemValueToUniform(UniformDescription& desc)
	{
		if(!desc.locationResolved)
		{
			glCheck(desc.location = glGetUniformLocation(programID, desc.name.CString()));
			desc.locationResolved = true;
		}
		SetValueToUniform(desc);
	}
}
