vertex = {
    #version 330 core

    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec2 textureCoords;
    layout (location = 2) in vec3 normals;

    out vec2 texCoord;
    out vec3 normal;
    out vec3 FragPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(pos, 1.0);
        texCoord = textureCoords;
        normal = mat3(transpose(inverse(model))) * normals;

        FragPos = vec3(model * vec4(pos, 1.0));
    }
}

pixel = {
    #version 330 core

    out vec4 FragColor;

    const uint MAXDIR = 5;
    const uint MAXSPOT = 10;
    const uint MAXPOINT = 10;

    struct DirLight{
        vec3 direction;

        vec4 color;
    };
    
    struct PointLight{
        vec3 position;
        
        float linear;
        float quadratic;

        vec4 color;
    };

    struct SpotLight{
        vec3 position;
        vec3 direction;

        float cutOff;
        float outerCutOff;

        float linear;
        float quadratic;

        vec4 color;
    };

    struct Material{
        sampler2D diffuse;
        sampler2D specular;

        float shininess;
    };

    in vec2 texCoord;
    in vec3 normal;
    in vec3 FragPos;
    
    uniform DirLight dirLight[MAXDIR];
    uniform PointLight pointLight[MAXPOINT];
    uniform SpotLight spotLight[MAXSPOT];

    uniform uint numOfDirLight;
    uniform uint numOfPointLight;
    uniform uint numOfSpotLight;

    uniform Material material;
    
    uniform vec3 viewPos;

    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

    void main()
    {
        uint dirs = min(numOfDirLight, MAXDIR);
        uint points = min(numOfPointLight, MAXPOINT);
        uint spotss = min(numOfSpotLight, MAXSPOT);

        vec3 norm = normalize(normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        vec3 res = texture(material.diffuse, texCoord).xyz * 0.05;

        for(uint i = 0; i < dirs; i++)
            res += CalcDirLight(dirLight[i], norm, viewDir);

        for(uint i = 0; i < points; i++)
            res += CalcPointLight(pointLight[i], norm, FragPos, viewDir);

        for(uint i = 0; i < spotss; i++)
            res += CalcSpotLight(spotLight[i], norm, FragPos, viewDir);
        

        FragColor = vec4(res,1.0);

    }

    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
    {
        vec3 lightDir = normalize(-light.direction);

        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        vec3 ambient = 0.1 * light.color.xyz * texture(material.diffuse, texCoord).xyz;
        vec3 diffuse = light.color.xyz * diff * texture(material.diffuse, texCoord).xyz;
        vec3 specular = light.color.xyz * spec * texture(material.specular, texCoord).xyz;

        return ambient + diffuse + specular;
    }

    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
    {
        vec3 lightDir = normalize(light.position - fragPos);

        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

        vec3 ambient = 0.1 * light.color.xyz * texture(material.diffuse, texCoord).xyz;
        vec3 diffuse = light.color.xyz * diff * texture(material.diffuse, texCoord).xyz;
        vec3 specular = light.color.xyz * spec * texture(material.specular, texCoord).xyz;
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        return ambient + diffuse + specular;
    }

    vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
    {
        vec3 lightDir = normalize(light.position - fragPos);

        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));

        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 ambient = 0.1 * light.color.xyz * texture(material.diffuse, texCoord).xyz;
        vec3 diffuse = light.color.xyz * diff * texture(material.diffuse, texCoord).xyz;
        vec3 specular = light.color.xyz * spec * texture(material.specular, texCoord).xyz;

        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return ambient + diffuse + specular;
    }
}