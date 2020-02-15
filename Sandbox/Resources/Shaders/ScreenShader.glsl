
vertex = {
    #version 330 core
	layout(location = 0) in vec2 pos;
	layout(location = 1) in vec2 TxtrCoord;
    
	out vec2 textrCoord;

	void main()
	{
		gl_Position = vec4(pos.x, pos.y, 0, 1.0);
		textrCoord = TxtrCoord;
	}
}

pixel = {
    #version 330 core
	out vec4 FragColor;

	in vec2 textrCoord;

	uniform sampler2D ScreenTexture;

	void main()
	{
		FragColor = texture(ScreenTexture, textrCoord);
		
	}
    
}