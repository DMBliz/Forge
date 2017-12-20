
vertex = {
    #version 330 core

    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec2 textureCoords;

    out vec2 texCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(pos, 1.0);
        texCoord = textureCoords;
    }
}

pixel = {
    #version 330 core

    out vec4 fragColor;

    in vec2 texCoord;
    
    uniform sampler2D modelTexture;
    uniform sampler2D modelTexture1;

    void main()
    {
        fragColor = mix(texture(modelTexture, texCoord),texture(modelTexture1, texCoord), 0.5f);
    }
}